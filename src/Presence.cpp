#include "Helper.h"

#include "IncludeManager.h"

#include "PresenceChannel.h"
#include "Logic.h"
#include "KnxHelper.h"
#include "Presence.h"
#include "Sensor.h"
#include "SensorMR24xxB1.h"

Presence::Presence()
{
}

Presence::~Presence() {}

void Presence::processReadRequests()
{
    // this method is called after startup delay and executes read requests, which should just happen once after startup
    static bool sCalledProcessReadRequests = false;
    if (!sCalledProcessReadRequests)
    {
        // we go through all IO devices defined as outputs and check for initial read requests
        // WireDevice::processReadRequests();
        sCalledProcessReadRequests = true;
    }
}

bool Presence::processDiagnoseCommand(char *iBuffer)
{
    bool lOutput = false;
    if (iBuffer[0] == 'p')
    {
        uint8_t lIndex = (iBuffer[1] - '0') * 10 + iBuffer[2] - '0' - 1;
        if (lIndex >= 0 && lIndex < mNumChannels) {
            // this is a channel request
            lOutput = mChannel[lIndex]->processDiagnoseCommand(iBuffer);
        } else { 
            // Command start with p are presence diagnose commands
            // there are no
            sprintf(iBuffer, "p: bad args");
            lOutput = true;
        }
    }
    return lOutput;
}

void Presence::processInputKo(GroupObject &iKo){
    if (iKo.asap() == PM_KoSensitivity) {
        mPresenceSensor->sendCommand(RadarCmd_WriteSensitivity, iKo.value(getDPT(VAL_DPT_5)));
    } else if (iKo.asap() == PM_KoScenario) {
        mPresenceSensor->sendCommand(RadarCmd_WriteScene, iKo.value(getDPT(VAL_DPT_5)));
    } else if (iKo.asap() == PM_KoHfReset) {
        // mPresenceSensor->sendCommand(RadarCmd_ResetSensor);
        startPowercycleHfSensor();
    } else if (iKo.asap() >= PM_KoOffset && iKo.asap() < PM_KoOffset + mNumChannels * PM_KoBlockSize) {
        // we are in the Range of presence KOs
        uint8_t lChannelIndex = (iKo.asap() - PM_KoOffset) / PM_KoBlockSize;
        PresenceChannel *lChannel = mChannel[lChannelIndex];
        lChannel->processInputKo(iKo);
    } 
}

bool Presence::getHardwarePresence()
{
    return mPresence;
}

// Starting all required sensors, this call may be blocking (with delay)
void Presence::startSensor()
{
    mPresenceSensor = (SensorMR24xxB1 *)Sensor::factory(SENS_MR24xxB1, MeasureType::Pres);
    mBrightnessSensor = Sensor::factory(SENS_VEML7700, Lux);
    // now start all sensors at the correct speed
    Sensor::beginSensors();
}

void Presence::startPowercycleHfSensor()
{
    digitalWrite(HF_POWER_PIN, LOW);
    mHfPowerCycleDelay = millis();
}

void Presence::processPowercycleHfSensor()
{
    if (delayCheck(mHfPowerCycleDelay, 5000))
    {
        digitalWrite(HF_POWER_PIN, HIGH);
        mHfPowerCycleDelay = 0;
    }
}

void Presence::processHardwarePresence()
{

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
                    digitalWrite(PRESENCE_LED_PIN, PRESENCE_LED_PIN_ACTIVE_ON == mPresence);
                    knx.getGroupObject(PM_KoPresenceOut).value(mPresence, getDPT(VAL_DPT_1));
                }
                if (lMove != mMove) 
                {
                    mMove = lMove;
                    digitalWrite(MOVE_LED_PIN, MOVE_LED_PIN_ACTIVE_ON == (mMove > 0));
                    knx.getGroupObject(PM_KoMoveOut).value(mMove, getDPT(VAL_DPT_5));
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
            if (mScenario != (uint8_t)lValue) {
                mScenario = (uint8_t)lValue;
                lKo.value(mScenario, getDPT(VAL_DPT_5));
            }
        }
        if (Sensor::measureValue(MeasureType::Sensitivity, lValue))
        {
            GroupObject &lKo = knx.getGroupObject(PM_KoSensitivity);
            if (mSensitivity != (uint8_t)lValue)
            {
                mSensitivity = (uint8_t)lValue;
                lKo.value(mSensitivity, getDPT(VAL_DPT_5));
            }
        }
    }

#ifdef PIR_PIN
    uint8_t lPresenceLed = ((knx.paramByte(LOG_LEDRot) & LOG_LEDRotMask) >> LOG_LEDRotShift);
    uint8_t lInfoLed = ((knx.paramByte(LOG_LEDOrange) & LOG_LEDOrangeMask) >> LOG_LEDOrangeShift);
    if (digitalRead(PIR_PIN))
    {
        if (!mPresence)
        {
            mPresenceDelay = millis();
            mPresence = true;
            mPresenceChanged = true;
        }
    }
    else
    {
        if (mPresence && delayCheck(mPresenceDelay, 500))
        {
            mPresence = false;
            mPresenceChanged = true;
        }
    }
    if (mPresenceChanged)
    {
        mPresenceChanged = false;
        if (lPresenceLed == VAL_LedOnPM || (lPresenceLed == VAL_LedOnChannelPM && mPresenceLedOn))
        {
            digitalWrite(PRESENCE_LED_PIN, mPresence);
        }
        if (lInfoLed == VAL_LedOnPM || (lInfoLed == VAL_LedOnChannelPM && mInfoLedOn))
        {
            digitalWrite(INFO_LED_PIN, mPresence);
        }
    }
    // add Trigger for any channel which registered for Hardware-PIR

#endif
}

void Presence::loop()
{
    if (!knx.configured())
        return;

    if (knx.paramByte(PM_HardwarePM) && PM_HardwarePMMask)
    {
        processHardwarePresence();
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
}

void Presence::setup()
{

    if (knx.configured())
    {
        // setup channels, not possible in constructor, because knx is not configured there
        // get number of channels from knxprod
        mNumChannels = knx.paramByte(PM_PMChannels);
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
        startSensor();
    }
}
