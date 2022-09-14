#include "Helper.h"

#include "IncludeManager.h"

#include "PresenceChannel.h"
// #include "Logic.h"
#include "KnxHelper.h"
#include "Presence.h"
#include "Sensor.h"
#include "SensorMR24xxB1.h"
#include "SensorOPT300x.h"
#include "SensorVEML7700.h"

Presence::Presence()
{
}

Presence::~Presence() {}

void Presence::addKoMap(uint16_t iKoNumber, uint8_t iChannelId, uint8_t iKoIndex)
{
    // first implementation, in future we use sorted insert
    mKoMap[mNumKoMap].koNumber = iKoNumber;
    mKoMap[mNumKoMap].channelIndex = iChannelId;
    mKoMap[mNumKoMap].koIndex = iKoIndex;
    if (mNumKoMap < cCountKoMap)
        mNumKoMap++;
}

// search for a given KO index for an other
// KO, which uses also this KO as an internal input
bool Presence::mapKO(uint16_t iKoNumber, sKoMap **iKoMap)
{
    sKoMap *lIterator = *iKoMap;
    if (*iKoMap == 0)
        lIterator = &mKoMap[0];
    else
        lIterator++;
    while (lIterator->koNumber > 0)
    {
        if (lIterator->koNumber == iKoNumber)
        {
            *iKoMap = lIterator;
            return true;
        }
        else
            lIterator++;
    }
    return false;
}

void Presence::processReadRequests()
{
    // this method is called after startup delay and executes read requests, which should just happen once after startup
    static bool sCalledProcessReadRequests = false;
    if (!sCalledProcessReadRequests)
    {
        // we go through all IO devices defined as outputs and check for initial read requests
        if (knx.paramByte(PM_ReadLed) & PM_ReadLedMask)
        {
            if ((knx.paramByte(PM_LEDPresence) & PM_LEDPresenceMask) >> PM_LEDPresenceShift == VAL_PM_LedKnx)
                knx.getGroupObject(PM_KoLEDPresence).requestObjectRead();
            if ((knx.paramByte(PM_LEDMove) & PM_LEDMoveMask) >> PM_LEDMoveShift == VAL_PM_LedKnx)
                knx.getGroupObject(PM_KoLEDMove).requestObjectRead();
        }
        sCalledProcessReadRequests = true;
    }
}

bool Presence::processDiagnoseCommand(char *iBuffer)
{
    bool lOutput = false;
    if (iBuffer[0] == 'p')
    {
        uint8_t lIndex = (iBuffer[1] - '0') * 10 + iBuffer[2] - '0' - 1;
        if (lIndex >= 0 && lIndex < mNumChannels) 
        {
            // this is a channel request
            lOutput = mChannel[lIndex]->processDiagnoseCommand(iBuffer);
        }
        else if (iBuffer[1] == 'l')
        {
            // output hardware move/presence state
            sprintf(iBuffer, "Move %d, Pres %d", mMove, mPresence);
            lOutput = true;
        }
        else
        {
            // Command start with p are presence diagnose commands
            // there are no
            sprintf(iBuffer, "p: bad args");
            lOutput = true;
        }
    }
    return lOutput;
}

void Presence::processInputKo(GroupObject &iKo)
{
    // we have to check first, if external KO are used
    sKoMap *lKoMap = nullptr;
    uint16_t lAsap = iKo.asap();
    while (mapKO(lAsap, &lKoMap))
    {
        uint16_t lKoIndex = lKoMap->koIndex;
        // here we check the range of internal KO per channel (KoIndex, not KoNumber)
        if ((lKoIndex >= PM_KoKOpLux && lKoIndex <= PM_KoKOpDayPhase) || lKoIndex == PM_KoKOpScene )
        {
            // we are in the Range of presence KOs
            uint8_t lChannelIndex = lKoMap->channelIndex;
            PresenceChannel *lChannel = mChannel[lChannelIndex];
            lChannel->processInputKo(iKo, lKoMap->koIndex);
        }
    }
    switch (lAsap)
    {
        case PM_KoSensitivity:
#ifdef HF_POWER_PIN
            mPresenceSensor->sendCommand(RadarCmd_WriteSensitivity, iKo.value(getDPT(VAL_DPT_5)));
#endif
            break;
        case PM_KoScenario:
#ifdef HF_POWER_PIN
            mPresenceSensor->sendCommand(RadarCmd_WriteScene, iKo.value(getDPT(VAL_DPT_5)));
#endif
            break;
        case PM_KoHfReset:
            // mPresenceSensor->sendCommand(RadarCmd_ResetSensor);
            startPowercycleHfSensor();
            break;
        case PM_KoLEDMove:
            processLED(iKo.value(getDPT(VAL_DPT_1)), CallerKnxMove);
            break;
        case PM_KoLEDPresence:
            processLED(iKo.value(getDPT(VAL_DPT_1)), CallerKnxPresence);
            break;
        default:
            if (lAsap >= PM_KoOffset && lAsap < PM_KoOffset + mNumChannels * PM_KoBlockSize)
            {
                // we are in the Range of presence KOs
                uint8_t lChannelIndex = (lAsap - PM_KoOffset) / PM_KoBlockSize;
                PresenceChannel *lChannel = mChannel[lChannelIndex];
                lChannel->processInputKo(iKo);
            }
            break;
    }
}

bool Presence::getHardwarePresence()
{
    return mPresence;
}

bool Presence::getHardwareMove()
{
    return mMove;
}

// Starting all required sensors, this call may be blocking (with delay)
void Presence::startSensors()
{
    uint8_t lHardwarePM = (knx.paramByte(PM_HWPresence) & PM_HWPresenceMask) >> PM_HWPresenceShift;
    uint8_t lHardwareLux = (knx.paramByte(PM_HWLux) & PM_HWLuxMask) >> PM_HWLuxShift;

    if (lHardwarePM == VAL_PM_PS_Hf)
    {
#ifdef HF_POWER_PIN
        mPresenceSensor = (SensorMR24xxB1 *)Sensor::factory(SENS_MR24xxB1, MeasureType::Pres);
        mPresenceSensor->defaultSensorParameters(((knx.paramByte(PM_HfScenario) & PM_HfScenarioMask) >> PM_HfScenarioShift) - 1, (knx.paramByte(PM_HfSensitivity) & PM_HfSensitivityMask) >> PM_HfSensitivityShift );
#endif
    }
    
    switch (lHardwareLux)
    {
        case VAL_PM_LUX_VEML:
            mBrightnessSensor = Sensor::factory(SENS_VEML7700, Lux);
            break;
        case VAL_PM_LUX_OPT:
            mBrightnessSensor = Sensor::factory(SENS_OPT300X, Lux);
            break;
        default:
            break;
    }
    // now start all sensors at the correct speed
    Sensor::beginSensors();
}

void Presence::startPowercycleHfSensor()
{
#ifdef HF_POWER_PIN
    digitalWrite(HF_POWER_PIN, LOW);
#endif
    mHfPowerCycleDelay = millis();
}

void Presence::processPowercycleHfSensor()
{
    if (delayCheck(mHfPowerCycleDelay, 5000))
    {
#ifdef HF_POWER_PIN
        digitalWrite(HF_POWER_PIN, HIGH);
#endif
        mHfPowerCycleDelay = 0;
    }
}

// handles the following situations for hardware LEDs (presence- and move-LED):
// - turn on and off by hardware if selected in settings
// - turn off on lock through day phase
// - be aware of multiple channels creating led locks
// - turn on and off by knx 
// - restore old led state on lock removal
void Presence::processLED(bool iOn, LedCaller iCaller)
{
    static int8_t sLedsLocked = false;
    static bool sLedMove = false;
    static bool sLedPresence = false;

    bool lLedMove = sLedMove;
    bool lLedPresence = sLedPresence;
    uint8_t lMoveLedParam = (knx.paramByte(PM_LEDMove) & PM_LEDMoveMask) >> PM_LEDMoveShift;
    uint8_t lPresenceLedParam = (knx.paramByte(PM_LEDPresence) & PM_LEDPresenceMask) >> PM_LEDPresenceShift;
    // we implement all led cases in one method
    switch (iCaller)
    {
        case CallerLock:
            sLedsLocked += (iOn) ? 1 : -1;
            // LEDs will keep the old values
            if (sLedsLocked <= 0) 
                sLedsLocked = 0;
            break;
        case CallerMove:
            if (lMoveLedParam == VAL_PM_LedMove)
                lLedMove = iOn;
            if (lPresenceLedParam == VAL_PM_LedMove)
                lLedPresence = iOn;
            break;
        case CallerPresence:
            if (lMoveLedParam == VAL_PM_LedPresence)
                lLedMove = iOn;
            if (lPresenceLedParam == VAL_PM_LedPresence)
                lLedPresence = iOn;
            break;
        case CallerKnxMove:
            if (lMoveLedParam == VAL_PM_LedKnx)
                lLedMove = iOn;
            break;
        case CallerKnxPresence:
            if (lMoveLedParam == VAL_PM_LedKnx)
                lLedPresence = iOn;
            break;
        default:
            // both LEDs are switched
            lLedMove = iOn;
            lLedPresence = iOn;
            break;
    }
#ifdef SERIAL_HF
    digitalWrite(MOVE_LED_PIN, MOVE_LED_PIN_ACTIVE_ON == (lLedMove && sLedsLocked == 0));
    digitalWrite(PRESENCE_LED_PIN, PRESENCE_LED_PIN_ACTIVE_ON == (lLedPresence && sLedsLocked == 0));
#endif
    // store the current values in memory
    sLedMove = lLedMove;
    sLedPresence = lLedPresence;
}

void Presence::processHardwarePresence()
{
#ifdef SERIAL_HF
    if (mPresenceSensor != 0) 
    {
        float lValue = 0;
        if (Sensor::measureValue(MeasureType::Pres, lValue) && lValue != mPresenceCombined)
        {
            mPresenceCombined = lValue;
            bool lPresence = false;
            uint8_t lMove;
            uint8_t lFall;
            uint8_t lAlarm;
            if (SensorMR24xxB1::decodePresenceResult((uint8_t)lValue, lPresence, lMove, lFall, lAlarm)) 
            {
                if (lPresence != mPresence)
                {
                    mPresence = lPresence;
                    // digitalWrite(PRESENCE_LED_PIN, PRESENCE_LED_PIN_ACTIVE_ON == mPresence);
                    processLED(mPresence, CallerPresence);
                    knx.getGroupObject(PM_KoPresenceOut).value(mPresence, getDPT(VAL_DPT_1));
                    if (mPresence)
                        PresenceTrigger = true;
                }
                if (lMove != mMove) 
                {
                    mMove = lMove;
                    // digitalWrite(MOVE_LED_PIN, MOVE_LED_PIN_ACTIVE_ON == (mMove > 0));
                    processLED(mMove > 0, CallerMove);
                    knx.getGroupObject(PM_KoMoveOut).value(mMove, getDPT(VAL_DPT_5));
                    if (mMove)
                        MoveTrigger = true;
                }
            }
        }
        if (Sensor::measureValue(MeasureType::Speed, lValue))
        {
            GroupObject &lKo = knx.getGroupObject(PM_KoMoveSpeedOut);
            if ((uint8_t)lKo.value(getDPT(VAL_DPT_5001)) != (uint8_t)lValue)
                lKo.value(lValue, getDPT(VAL_DPT_5001));
        }
        if (Sensor::measureValue(MeasureType::Scenario, lValue))
        {
            GroupObject &lKo = knx.getGroupObject(PM_KoScenario);
            if (mScenario != (int8_t)lValue) {
                mScenario = (int8_t)lValue;
                lKo.value(mScenario, getDPT(VAL_DPT_5));
            }
        }
        if (Sensor::measureValue(MeasureType::Sensitivity, lValue))
        {
            GroupObject &lKo = knx.getGroupObject(PM_KoSensitivity);
            if (mSensitivity != (int8_t)lValue)
            {
                mSensitivity = (int8_t)lValue;
                lKo.value(mSensitivity, getDPT(VAL_DPT_5));
            }
        }
    }
#endif
#ifdef PIR_PIN
    if (digitalRead(PIR_PIN))
    {
        if (mMove == 0)
        {
            mPresenceDelay = millis();
            mMove = 1;
            mPresenceChanged = true;
        }
    }
    else
    {
        if (mMove > 0 && delayCheck(mPresenceDelay, 500))
        {
            mMove = 0;
            mPresenceChanged = true;
        }
    }
    if (mPresenceChanged)
    {
        mPresenceChanged = false;
        processLED(mMove > 0, CallerMove);
    }
    // add Trigger for any channel which registered for Hardware-PIR
#endif
}

void Presence::processHardwareLux()
{
    if (mBrightnessSensor != 0)
    {
        float lValue = 0;
        // we check for brightness only every second
        if (delayCheck(mBrightnessProcess, 1000) && Sensor::measureValue(MeasureType::Lux, lValue))
        {
            mBrightnessProcess = delayTimerInit();
            bool lSend = false;
            mLux = lValue;
            knx.getGroupObject(PM_KoLuxOut).valueNoSend(getHardwareBrightness(), getDPT(VAL_DPT_9));
            uint32_t lTimeDelta = getDelayPattern(PM_LuxSendCycleDelayBase);
            bool lDeltaAbsRel = knx.paramByte(PM_LuxSendDeltaAbsRel) & PM_LuxSendDeltaAbsRelMask;
            lSend = lTimeDelta > 0 && delayCheck(mBrightnessDelay, lTimeDelta);
            uint16_t lDelta = knx.paramWord(PM_LuxSendDelta) & 0x7FFF; // just 15 bits
            if (lDelta > 0)
            {
                if (lDeltaAbsRel)
                {
                    // Rel
                    if (abs(mLux - mLuxLast) > 0.1)
                        lSend = lSend || (mLuxLast == 0) ? true : (abs((mLux - mLuxLast) / mLuxLast) * 100 >= lDelta); // Rel
                }
                else
                    lSend = lSend || abs(mLux - mLuxLast) >= lDelta; // Abs
            }
            if (lSend)
            {
                mLuxLast = mLux;
                mBrightnessDelay = delayTimerInit();
                knx.getGroupObject(PM_KoLuxOut).objectWritten();
            }
        }
    }
}

float Presence::getHardwareBrightness()
{
    return mLux + knx.paramByte(PM_LuxOffsetPM);
}

void Presence::loop()
{
    if (!knx.configured())
        return;

    if (mDoPresenceHardwareCycle)
    {
        processHardwarePresence();
        processHardwareLux();
        processPowercycleHfSensor();
        Sensor::sensorLoop();
    }

    // we loop on all channels and execute state logic
    for (uint8_t lIndex = 0; lIndex < mNumChannels; lIndex++)
    {
        PresenceChannel *lChannel = mChannel[lIndex];
        lChannel->loop();
        // loopSubmodules();
    }
    PresenceTrigger = false;
    MoveTrigger = false;
}

void Presence::setup()
{

    if (knx.configured())
    {
        // setup channels, not possible in constructor, because knx is not configured there
        // get number of channels from knxprod
        mNumChannels = PM_ChannelCount; // knx.paramByte(PM_PMChannels);
        if (PM_ChannelCount < mNumChannels)
        {
            char lErrorText[80];
            sprintf(lErrorText, "FATAL: Firmware compiled for %d PresenceChannels, but knxprod needs %d!\n", PM_ChannelCount, mNumChannels);
            fatalError(FATAL_LOG_WRONG_CHANNEL_COUNT, lErrorText);
        }
        // set back reference
        PresenceChannel::setPresence(this);
        // calculate parameter block size for day phase parameters
        PresenceChannel::setDayPhaseParameterSize(PM_pBBrightnessAuto - PM_pABrightnessAuto);
        for (uint8_t lIndex = 0; lIndex < mNumChannels; lIndex++)
        {
            mChannel[lIndex] = new PresenceChannel(lIndex);
            mChannel[lIndex]->setup();
        }
        mDoPresenceHardwareCycle = ((knx.paramByte(PM_HWPresence) & PM_HWPresenceMask) > 0) || ((knx.paramByte(PM_HWLux) & PM_HWLuxMask) > 0);
        startSensors();
    }
}
