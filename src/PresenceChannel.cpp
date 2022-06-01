#include "PresenceChannel.h"
#include "Presence.h"
#include "Helper.h"
#include "KnxHelper.h"
#include "IncludeManager.h"

Presence *PresenceChannel::sPresence = nullptr;
uint8_t PresenceChannel::sDayPhaseParameterSize = 0;

PresenceChannel::PresenceChannel(uint8_t iChannelNumber)
{
    mChannelId = iChannelNumber; // Zero based
    pCurrentState = 0;
    pCurrentValue = 0;
}

PresenceChannel::~PresenceChannel(){}

void PresenceChannel::setPresence(Presence *iPresence)
{
    sPresence = iPresence;
}

void PresenceChannel::setDayPhaseParameterSize(uint8_t iSize)
{
    sDayPhaseParameterSize = iSize;
}

/******************************
 * Parameter helper
 * ***************************/
uint32_t PresenceChannel::calcParamIndex(uint16_t iParamIndex, bool iWithPhase)
{
    uint16_t lParamIndex = iParamIndex + (iWithPhase ? sDayPhaseParameterSize * mCurrentDayPhase : 0);
    uint32_t lResult = lParamIndex + mChannelId * PM_ParamBlockSize + PM_ParamBlockOffset;
    return lResult;
}

uint16_t PresenceChannel::calcKoNumber(uint8_t iKoIndex) {
    uint16_t lResult = iKoIndex + mChannelId * PM_KoBlockSize + PM_KoOffset;
    return lResult;
}

// calculates correct KoIndex for this channel, returns -1 for invalid !!!
int8_t PresenceChannel::calcKoIndex(uint16_t iKoNumber)
{
    int16_t lResult = (iKoNumber - PM_KoOffset);
    // check if channel is valid
    if ((int8_t)(lResult / PM_KoBlockSize) == mChannelId)
        lResult = lResult % PM_KoBlockSize;
    else
        lResult = -1;
    return (int8_t)lResult;
}

// this function also respects internal KO, even though they are addressed with external KO addresses
GroupObject *PresenceChannel::getKo(uint8_t iKoIndex)
{
    uint8_t lParamIndex;
    uint16_t lKoNumber;
    // internal objects have to be enumerated here explicitly
    switch (iKoIndex)
    {
        case PM_KoKOpLux:
        case PM_KoKOpPresence1:
        case PM_KoKOpPresence2:
        case PM_KoKOpSetAuto:
        case PM_KoKOpSetManual:
        case PM_KoKOpAktorState:
        case PM_KoKOpLock:
        case PM_KoKOpReset:
        case PM_KoKOpDayPhase:
            lParamIndex = PM_pNumLux + iKoIndex * 2;
            break;
        case PM_KoKOpScene:
            lParamIndex = PM_pNumScene;
            break;
        default:
            lParamIndex = 0;
            break;
    }
    if (lParamIndex)
        lKoNumber = paramWord(lParamIndex) & 0x7FFF;
    else
        lKoNumber = calcKoNumber(iKoIndex);
    return &knx.getGroupObject(lKoNumber);
}

bool PresenceChannel::paramBit(uint16_t iParamIndex, uint8_t iParamMask, bool iWithPhase /* = false */)
{
    return (knx.paramByte(calcParamIndex(iParamIndex, iWithPhase)) & iParamMask);
}

uint8_t PresenceChannel::paramByte(uint16_t iParamIndex, uint8_t iParamMask, uint8_t iParamShift, bool iWithPhase /* = false */)
{
    return (knx.paramByte(calcParamIndex(iParamIndex, iWithPhase)) & iParamMask) >> iParamShift;
}

uint8_t PresenceChannel::paramByte(uint16_t iParamIndex, bool iWithPhase /* = false */)
{
    return knx.paramByte(calcParamIndex(iParamIndex, iWithPhase));
}

uint16_t PresenceChannel::paramWord(uint16_t iParamIndex, bool iWithPhase /* = false */)
{
    return knx.paramWord(calcParamIndex(iParamIndex, iWithPhase));
}

uint32_t PresenceChannel::paramInt(uint16_t iParamIndex, bool iWithPhase /* = false */)
{
    return knx.paramInt(calcParamIndex(iParamIndex, iWithPhase));
}

uint32_t PresenceChannel::paramTimeDelay(uint16_t iParamIndex, bool iWithPhase /* = false */, bool iAsSeconds /* = false */)
{
    return getDelayPattern(calcParamIndex(iParamIndex, iWithPhase), iAsSeconds);
}

bool PresenceChannel::processDiagnoseCommand(char *iBuffer)
{
    bool lResult = false;
    // at this point we know, that the we have p<nn> in buffer, so we look at the next letter
    if (iBuffer[3] == 't') {
        // output remaining presence time
        int16_t lPresence = 0;
        if (pCurrentState & STATE_PRESENCE) {
            // we present both, long and short presence
            lPresence = getKo(PM_KoKOpPresenceDelay)->value(getDPT(VAL_DPT_7));
            if (pPresenceDelayTime > 0) {
                lPresence = lPresence - (uint16_t)((millis() - pPresenceDelayTime) / 1000);
            }
            // Long presence output is "L mm:ss "
            snprintf(iBuffer, 14, "L %02d:%02d ", (lPresence / 60) % 60, lPresence % 60);
            if (pCurrentState & STATE_PRESENCE_SHORT) {
                lPresence = paramTimeDelay(PM_pAPresenceShortDurationBase, true, true);
                lPresence = lPresence - (uint16_t)((millis() - pPresenceShortDelayTime) / 1000);
                if (lPresence >= 0) {
                    // Short presence duration output is "L mm:ss S m:ss"
                    snprintf(iBuffer + 8, 7, "S %01d:%02d", (lPresence / 60) % 60, lPresence % 60);
                } else {
                    // Short presence evaluation output is "L mm:ss D m:ss"
                    snprintf(iBuffer + 8, 7, "D %01d:%02d", (-lPresence / 60) % 60, -lPresence % 60);
                }
            }
        }
        else if (pCurrentState & STATE_RUNNING)
        {
            sprintf(iBuffer, "no presence");
        } 
        else 
        {
            sprintf(iBuffer, "inactive");
        }
        lResult = true;
    }
    return lResult;
}

void PresenceChannel::processInputKo(GroupObject &iKo, int8_t iKoIndex)
{
    // we process KO only if we are running
    if (pCurrentState & STATE_RUNNING) {
        // search for correct KO
        uint8_t lPresenceType;
        uint8_t lKoIndex = (iKoIndex >= 0) ? iKoIndex : calcKoIndex(iKo.asap());
        bool lValue = iKo.value(getDPT(VAL_DPT_1));
        switch (lKoIndex)
        {
            case PM_KoKOpLuxOn:
                calculateBrightnessOff();
                // a start brightness is triggered by a new value to KO(LuxOff)
                break;
            case PM_KoKOpLux:
            case PM_KoKOpLuxOff:
                // measured external brightness or changed brightness level
                startBrightness();
                break;
            case PM_KoKOpPresence1:
                // which kind of presence information do we get
                lPresenceType = paramByte(PM_pPresence1Type, PM_pPresence1TypeMask, PM_pPresence1TypeShift);
                startPresence(lPresenceType, iKo);
                break;
            case PM_KoKOpPresence2:
                // change of presence information
                lPresenceType = paramByte(PM_pPresence2Type, PM_pPresence2TypeMask, PM_pPresence2TypeShift);
                startPresence(lPresenceType, iKo);
                break;
            case PM_KoKOpSetAuto:
                // Automatic mode
                startAuto(lValue);
                break;
            case PM_KoKOpSetManual:
                // check for tow button mode
                if (paramBit(PM_pManualModeKeyCount, PM_pManualModeKeyCountMask))
                    startManual(lValue);
                else // use single button mode
                    if (lValue)
                        startManual(pCurrentValue & PM_BIT_OUTPUT_SET);
                    else
                        startAuto(pCurrentValue & PM_BIT_OUTPUT_SET);
                break;
            case PM_KoKOpAktorState:
                // Actor state changed
                startActorState(iKo);
                break;
            case PM_KoKOpLock:
                // lock mode
                startLock();
                break;
            case PM_KoKOpReset:
                // reset PM, we just react on ON-telegrams
                if (lValue)
                    startReset();
                break;
            case PM_KoKOpDayPhase:
                startDayPhase();
                break;
            case PM_KoKOpScene:
                startSceneCommand(iKo);
                break;
            case PM_KoKOpChangeDimAbs:
            case PM_KoKOpChangeDimRel:
            case PM_KoKOpChangeSwitch:
                startAdaptiveBrightness();
                break;
            default:
                // do nothing
                break;
        }
    }
}

void PresenceChannel::startSceneCommand(GroupObject &iKo) 
{
    // get scene number
    uint8_t lSceneFromKo = (uint8_t)iKo.value(getDPT(VAL_DPT_17)) + 1;
    // check if scene is used
    for (uint8_t lIndex = 0; lIndex < 10; lIndex++)
    {
        uint8_t lSceneFromParam = paramByte(PM_pScene0 + lIndex);
        if (lSceneFromParam == lSceneFromKo) 
        {
            uint8_t lAction = paramByte(PM_pSceneAction0 + lIndex / 2);
            // get high/low nibble as action code
            lAction = (lIndex % 2) ? (lAction & PM_pSceneAction1Mask) : (lAction & PM_pSceneAction0Mask) >> PM_pSceneAction0Shift;
            switch (lAction)
            {
                case VAL_PM_SA_ChangeBrightness:
                    startAdaptiveBrightness();
                    break;
                case VAL_PM_SA_AutoOff:
                    startAuto(false);
                    break;
                case VAL_PM_SA_AutoOn:
                    startAuto(true);
                    break;
                case VAL_PM_SA_ManualOff:
                    startManual(false);
                    break;
                case VAL_PM_SA_ManualOn:
                    startManual(true);
                    break;
                case VAL_PM_SA_LockOff:
                    onLock(true, VAL_PM_LockOutputOff, 0);
                    break;
                case VAL_PM_SA_LockOn:
                    onLock(true, VAL_PM_LockOutputOn, 0);
                    break;
                case VAL_PM_SA_Lock:
                    onLock(true, 0, 0);
                    break;
                case VAL_PM_SA_UnlockWithState:
                    onLock(false, 0, VAL_PM_LockOutputCurrent);
                    break;
                case VAL_PM_SA_Unlock:
                    onLock(false, 0, 0);
                    break;
                case VAL_PM_SA_LeaveRoom:
                    /* not implemented yet */
                    break;
                case VAL_PM_SA_Reset:
                    startReset();
                    break;
                default:
                    break;
            }
        }
    }
}

// channel startup delay
void PresenceChannel::startStartup()
{
    pOnDelay = delayTimerInit();
    pCurrentState |= STATE_STARTUP;
}

void PresenceChannel::processStartup()
{
    if (delayCheck(pOnDelay, paramTimeDelay(PM_pChannelDelayBase)))
    {
        // we waited enough, remove State marker
        pCurrentState &= ~STATE_STARTUP;
        // set running state if the channel is active
        if (paramByte(PM_pChannelActive, PM_pChannelActiveMask, PM_pChannelActiveShift) == PM_VAL_ActiveYes)
            pCurrentState |= STATE_RUNNING;
        pOnDelay = 0;
    }
}

int8_t PresenceChannel::getDayPhaseFromKO()
{
    // derive day phase from scene number
    int8_t lPhaseCount = paramByte(PM_pPhaseCount, PM_pPhaseCountMask, PM_pPhaseCountShift);
    if (lPhaseCount == 1 && paramBit(PM_pPhaseBool, PM_pPhaseBoolMask)) // PhaseCount is zero based (0 = 1 Phase)
    {
        lPhaseCount = (uint8_t)getKo(PM_KoKOpDayPhase)->value(getDPT(VAL_DPT_1));
    }
    else 
    {
    uint8_t lScene = (uint8_t)getKo(PM_KoKOpDayPhase)->value(getDPT(VAL_DPT_17));
    for (; lPhaseCount >= 0; lPhaseCount--)
        if (paramByte(PM_pPhase1Scene + lPhaseCount) == lScene)
            break;
    }
    return lPhaseCount;
}

void PresenceChannel::startDayPhase() {

    // derive day phase from scene number
    int8_t lPhase = getDayPhaseFromKO();

    // first check, if day phase is valid and if it really changed
    if (lPhase < 0 || mCurrentDayPhase == lPhase)
        return;

    // check if delayed day phase execution is requested
    if (paramBit(PM_pPhaseChange, PM_pPhaseChangeMask)) {
        // we change immediately
        onDayPhase(lPhase);
    }
    else {
        // we change on next (internal) off at output
        pCurrentState |= STATE_DAY_PHASE_CHANGE;
    }
}

void PresenceChannel::processDayPhase()
{
    if (!(pCurrentValue & PM_BIT_OUTPUT_SET)) {
        // output is OFF, we can safely change day phase
        pCurrentState &= ~STATE_DAY_PHASE_CHANGE;
        int8_t lPhase = getDayPhaseFromKO();

        // first check, if day phase is valid and if it really changed
        if (lPhase < 0 || mCurrentDayPhase == lPhase)
            return;
        onDayPhase(lPhase);
    }
}

void PresenceChannel::onDayPhase(uint8_t iPhase)
{
    // cleanup old day phase, here we are still in old day phase
    // remove hardware LED lock
    if (paramBit(PM_pALockHardwareLEDs, PM_pALockHardwareLEDsMask, true))
        sPresence->processLED(false, Presence::CallerLock);

    // set the new day phase
    mCurrentDayPhase = iPhase; 

    // process hardware led lock
    if (paramBit(PM_pALockHardwareLEDs, PM_pALockHardwareLEDsMask, true))
        sPresence->processLED(true, Presence::CallerLock);

    // Here we preset KO values, which directly influence PM processing
    // with according parameters from day phase.
    // presence delay
    uint32_t lPresenceDelay = paramTimeDelay(PM_pAPresenceDelayBase, true, true);
    getKo(PM_KoKOpPresenceDelay)->value(lPresenceDelay, getDPT(VAL_DPT_7));
    // brightness to turn on light
    uint32_t lBrightness = paramWord(PM_pABrightnessOn, true);
    getKo(PM_KoKOpLuxOn)->value(lBrightness, getDPT(VAL_DPT_9));
    // brightness to turn off light
    calculateBrightnessOff();
}

bool PresenceChannel::getRawPresence()
{
    bool lPresence = getKo(PM_KoKOpPresence1)->value(getDPT(VAL_DPT_1)) || getKo(PM_KoKOpPresence2)->value(getDPT(VAL_DPT_1));
    // if hardware presence sensor is available, we evaluate its value
    if (!lPresence)
        lPresence = getHardwarePresence();
    return lPresence;
}

bool PresenceChannel::getHardwarePresence()
{
    // if hardware presence sensor is available, we evaluate its value
    bool lPresence = false;
    if (paramByte(PM_pPresenceUsage, PM_pPresenceUsageMask, PM_pPresenceUsageShift) == VAL_PM_PresenceUsageMove)
        lPresence = sPresence->getHardwareMove();
    if (!lPresence && paramByte(PM_pPresenceUsage, PM_pPresenceUsageMask, PM_pPresenceUsageShift) == VAL_PM_PresenceUsagePresence)
        lPresence = sPresence->getHardwarePresence();
    return lPresence;
}

// entry point for presence trigger (means start or restart presence delay)
void PresenceChannel::startPresenceTrigger()
{
    startPresence(true);
    // startPresence(false);
    pPresenceDelayTime = delayTimerInit();
}

void PresenceChannel::startHardwarePresence() 
{
    if (sPresence->PresenceTrigger || sPresence->MoveTrigger)
        if (getHardwarePresence()) 
            startPresenceTrigger();
}

// helper entry point for presence calculation initiated by a KO
void PresenceChannel::startPresence(uint8_t iPresenceType, GroupObject &iKo)
{
    // sanity check
    if (iPresenceType == VAL_PM_PresenceTypeOff)
        return;

    bool lPresenceValue = iKo.value(getDPT(VAL_DPT_1));
    // we ignore explicitly OFF telegrams of triggered input
    if (iPresenceType == VAL_PM_PresenceTypeTrigger && !lPresenceValue)
        return;
    startPresence();
    if (iPresenceType == VAL_PM_PresenceTypeTrigger && lPresenceValue)
    {
        // triggered input sent a 1, we immediately set it to 0
        iKo.value(false, getDPT(VAL_DPT_1));
        // afterwards we call ourself to evaluate 0 action
        startPresence();
    }
}

// main entry point for presence calculation (KO independent), implemented as switching presence channel 
void PresenceChannel::startPresence(bool iForce /* = false */)
{
    // this method handles both presence inputs. We handle both combined by an OR.
    if (iForce || getRawPresence()) {
        // do according actions if presence changes
        if (!(pCurrentState & STATE_PRESENCE)) {
            startPresenceShort();
            onPresenceBrightnessChange(true);
        }
        // presence is turned on, we set the state and delete delay timer
        pCurrentState |= STATE_PRESENCE;
        pPresenceDelayTime = 0; // there is no action because of this, the delay time is just "off"
    } else if (pCurrentState & STATE_PRESENCE) {
        // presence is turned off, we start delay timer, but just if we are in presence mode
        // Why check for presence state here? Because multiple off would restart presence delay even if there is no presence
        pPresenceDelayTime = delayTimerInit();
    }
}

void PresenceChannel::processPresence()
{
    // we just do something if timer is really running
    if (pPresenceDelayTime > 0) {
        uint32_t lPresenceDelay = (uint32_t)getKo(PM_KoKOpPresenceDelay)->value(getDPT(VAL_DPT_7)) * 1000;
        if (delayCheck(pPresenceDelayTime, lPresenceDelay))
        {
            // time is over, we turn everything off
            endPresence();
        }
    }
}

void PresenceChannel::endPresence(bool iSend /* = true */)
{
    // presence and short presence determination are stopped
    pCurrentState &= ~(STATE_PRESENCE | STATE_PRESENCE_SHORT | STATE_AUTO);
    pCurrentValue &= ~PM_BIT_DISABLE_BRIGHTNESS_OFF;
    pPresenceDelayTime = 0;
    pPresenceShortDelayTime = 0;
    if (iSend) onPresenceChange(false);
}

void PresenceChannel::startPresenceShort()
{
    if (paramBit(PM_pAPresenceShort, PM_pAPresenceShortMask, true))
    {
        // set the mark for short presence mode
        pCurrentState |= STATE_PRESENCE_SHORT;
        pPresenceShortDelayTime = delayTimerInit();
    }
}

void PresenceChannel::processPresenceShort()
{
    // short presence is measured immediately
    if (delayCheck(pPresenceShortDelayTime, paramTimeDelay(PM_pAPresenceShortDurationBase, true))) 
    {
        // now short presence duration passed, check of also short presence delay passed
        if (delayCheck(pPresenceShortDelayTime, (paramTimeDelay(PM_pAPresenceShortDurationBase, true) + paramTimeDelay(PM_pAPresenceShortDelayBase, true) + 300)))
        {
            // there was no new presence evaluation during short presence delay, so we know, short presence is valid here
            endPresence();
        } 
        else 
        {
            // if we get any further presence information, we stop short presence without ending normal presence
            bool lPresence = getRawPresence();
            if (lPresence) 
            {
                pCurrentState &= ~STATE_PRESENCE_SHORT;
                pPresenceShortDelayTime = 0;
            }
        }
    }
}

void PresenceChannel::onPresenceBrightnessChange(bool iOn)
{
    // calculate output dependent on brightness and auto mode
    if (iOn && !paramBit(PM_pBrightnessIndependent, PM_pBrightnessIndependentMask)) 
    {
        // check brightness in case of turning on
        if ((uint32_t)getKo(PM_KoKOpLux)->value(getDPT(VAL_DPT_9)) <= (uint32_t)getKo(PM_KoKOpLuxOn)->value(getDPT(VAL_DPT_9)))
            onPresenceChange(iOn);
    }
    else // turn off if brightness independent
        onPresenceChange(iOn);
}

void PresenceChannel::onPresenceChange(bool iOn)
{
    // Output is only influenced in auto mode
    if (!(pCurrentState & STATE_MANUAL))
        startOutput(iOn);
}

// downtime after switch off
void PresenceChannel::startDowntime()
{
    // ensure auto mode
    onManualChange(false);
    // set state
    pCurrentState |= STATE_DOWNTIME;
    // set downtime timer
    pDowntimeDelayTime = delayTimerInit();
    // set output according to input value
    startOutput(false);
}

void PresenceChannel::processDowntime()
{
    if (pDowntimeDelayTime > 0 && delayCheck(pDowntimeDelayTime, getDelayPattern(PM_pDowntimeOffBase, false))) 
    {
        pDowntimeDelayTime = 0;
        pCurrentState &= ~STATE_DOWNTIME;
    }
}

void PresenceChannel::startAuto(bool iOn)
{
    // ensure auto mode
    onManualChange(false);
    // we start presence delay
    startPresenceTrigger();
    // and we also start/reset short presence here
    startPresenceShort();
    // set state
    pCurrentState |= STATE_AUTO;
    // set output according to input value
    startOutput(iOn);
}

void PresenceChannel::processAuto()
{
}

void PresenceChannel::startManual(bool iOn)
{
    // ensure manual mode
    onManualChange(true);
    // we stop presence delay
    endPresence();
    // set output according to input value
    startOutput(iOn);
}

void PresenceChannel::processManual()
{
    // we just do something if timer is really running
    if (pManualFallbackTime > 0)
    {
        // in case manual mode is presence dependent, any presence resets manual fallback time
        if (paramBit(PM_pAManualWithPresence, PM_pAManualWithPresenceMask, true) && getRawPresence())
        {
            pManualFallbackTime = delayTimerInit();
        }
        else if (delayCheck(pManualFallbackTime, paramTimeDelay(PM_pAManualFallbackDelayBase, true)))
        {
            // time is over, we turn everything off
            onManualChange(false);
            onPresenceChange(false);
        }
    }
}

void PresenceChannel::onManualChange(bool iOn)
{
    if (iOn) {
        pCurrentState |= STATE_MANUAL; // we set manual state
        pCurrentState &= ~STATE_AUTO;  // and end auto state
        if (paramTimeDelay(PM_pAManualFallbackDelayBase, true) > 0)
            pManualFallbackTime = delayTimerInit();
    }
    else
    {
        pCurrentState &= ~STATE_MANUAL;
        pManualFallbackTime = 0;
    }
    // set StateKO
    if ((bool)(getKo(PM_KoKOpIsManual)->value(getDPT(VAL_DPT_1))) != iOn)
        getKo(PM_KoKOpIsManual)->value(iOn, getDPT(VAL_DPT_1));
}

void PresenceChannel::startLock()
{
    // check lock mode (simple lock or priority control)
    uint8_t lLockType = paramByte(PM_pLockType, PM_pLockTypeMask, PM_pLockTypeShift);
    if (lLockType == VAL_PM_LockTypePriority) {
        uint8_t lPriority = getKo(PM_KoKOpLock)->value(getDPT(VAL_DPT_5));
        bool lValue = (lPriority & 2);
        uint8_t lLockSend = (lPriority & 1) + 1;
        onLock(lValue, lLockSend, lLockSend);
    } else if (lLockType == VAL_PM_LockTypeLock) {
        // simple lock
        bool lValue = getKo(PM_KoKOpLock)->value(getDPT(VAL_DPT_1));
        uint8_t lLockOnSend = paramByte(PM_pLockOn, PM_pLockOnMask, PM_pLockOnShift);
        uint8_t lLockOffSend = paramByte(PM_pLockOff, PM_pLockOffMask, PM_pLockOffShift);
        onLock(lValue, lLockOnSend, lLockOffSend);
    }
}

void PresenceChannel::processLock()
{
    // check if there is a time given to reset lock
    if ((pCurrentState & STATE_LOCK) && paramBit(PM_pLockFallback, PM_pLockFallbackMask)) {
        if (delayCheck(pLockDelayTime, paramTimeDelay(PM_pLockFallbackBase))) {
            // end lock
            uint8_t lLockType = paramByte(PM_pLockType, PM_pLockTypeMask, PM_pLockTypeShift);
            if (lLockType == VAL_PM_LockTypePriority)
            {
                // priority
                onLock(false, VAL_PM_LockOutputOff, VAL_PM_LockOutputOff);
            }
            else if (lLockType == VAL_PM_LockTypeLock)
            {
                // simple lock
                uint8_t lLockOffSend = paramByte(PM_pLockOff, PM_pLockOffMask, PM_pLockOffShift);
                onLock(false, lLockOffSend, lLockOffSend);
            }
        }
    }
}

void PresenceChannel::onLock(bool iLockOn, uint8_t iLockOnSend, uint8_t iLockOffSend) {

    if (iLockOn)
    {
        pCurrentState |= STATE_LOCK;
        // should we send something?
        if (iLockOnSend)
        {
            startOutput(iLockOnSend == VAL_PM_LockOutputOn);
            forceOutput(true);
        }
    }
    else if (pCurrentState & STATE_LOCK)
    {
        pCurrentState &= ~STATE_LOCK;
        // should we send something?
        // bool lOn = false;
        uint32_t lPresenceDelayTime;
        switch (iLockOffSend)
        {
        case VAL_PM_LockOutputNone:
            // nothing should be send, so we set the output state to current state
            syncOutput();
            // we start auto mode with current value
            // lOn = pCurrentValue & PM_BIT_OUTPUT_SET;
            // endPresence(false);
            break;
        case VAL_PM_LockOutputOff:
            startAuto(false);
            forceOutput(true);
            break;
        case VAL_PM_LockOutputOn:
            startAuto(true);
            forceOutput(true);
            break;
        case VAL_PM_LockOutputCurrent:
            // we send current state by reevaluation
            lPresenceDelayTime = pPresenceDelayTime;
            startPresence();
            pPresenceDelayTime = lPresenceDelayTime;
            forceOutput(true);
            break;
        default:
            break;
        }
    }
}

void PresenceChannel::startReset()
{
    // We reset PM so that next (or an existing) presence signal immediately turns output on
    onManualChange(false);
    endPresence(true);

    // Unclear: how to handle lock?
    // Unclear: how to handle slave PMs
    // Unclear: do we restore here also day phase settings?

    // finally we look if current presence signal is there
    startPresence();
    forceOutput(true);
}

void PresenceChannel::startActorState(GroupObject &iKo)
{
    // change of actor state always influences the PM behaviour,
    // if the actor state is different to current PM state
    bool lValue = iKo.value(getDPT(VAL_DPT_1));

    // we leave immediately, if actor state and PM state are equal
    if (((bool)(pCurrentValue & PM_BIT_OUTPUT_SET)) == lValue)
        return;

    // in case of actor change we behave like Auto-On (light should go out after delay time)
    // if (lValue) {         
    startAuto(lValue);
    // } else {
    // startReset();  // Bernhard: actor state off during run-on time ends run-on time
    // }
    // but we do not send anything to the knx bus
    syncOutput();
}

void PresenceChannel::processActorState()
{
    // currently nothing to do
}

void PresenceChannel::calculateBrightnessOff()
{
    // calculate brightness to turn off light
    // we have to differ between absolute and adaptive turn off light
    uint8_t lLuxAutoOff = paramByte(PM_pABrightnessAuto, PM_pABrightnessAutoMask, PM_pABrightnessAutoShift, true);
    switch (lLuxAutoOff)
    {
        case VAL_PM_LuxAdaptiveOff:
            // for adaptive off the calculation is async
            startAdaptiveBrightness();
            break;
        case VAL_PM_LuxAbsoluteOff:
            // for absolute off we simply add the offset to current on limit
            uint32_t lBrightness = getKo(PM_KoKOpLuxOn)->value(getDPT(VAL_DPT_9));
            lBrightness += paramWord(PM_pABrightnessDelta, true);
            getKo(PM_KoKOpLuxOff)->value(lBrightness, getDPT(VAL_DPT_9));
            break;
        default:
            // do nothing
            break;
    }
}

void PresenceChannel::startBrightness()
{
    // should we suppress brightness evaluation?
    bool lEvalBrightness = !(pCurrentValue & PM_BIT_DISABLE_BRIGHTNESS_OFF);
    // or are we working brightness independent?
    lEvalBrightness = lEvalBrightness && (!paramBit(PM_pBrightnessIndependent, PM_pBrightnessIndependentMask));
    // or are we in manual mode?
    lEvalBrightness = lEvalBrightness && ((pCurrentState & (STATE_MANUAL | STATE_LOCK)) == 0);
    if (lEvalBrightness) 
    {
        // first check for upper value, if higher, then switch off
        uint32_t lBrightness = getKo(PM_KoKOpLux)->value(getDPT(VAL_DPT_9));
        if (lBrightness > (uint32_t)getKo(PM_KoKOpLuxOff)->value(getDPT(VAL_DPT_9)))
        {
            // we start timer off delay
            if (pBrightnessOffDelayTime == 0 && paramByte(PM_pABrightnessAuto, PM_pABrightnessAutoMask, PM_pABrightnessAutoShift, true) > 0)
                pBrightnessOffDelayTime = delayTimerInit();
        }
        else 
        {
            // deactivate brightness off
            pBrightnessOffDelayTime = 0;
        }
        // now check lower value, if below, turn light on
        if (lBrightness <= (uint32_t)getKo(PM_KoKOpLuxOn)->value(getDPT(VAL_DPT_9)))
        {
            // its getting dark, if we are in presence state, we turn light on
            if ((pCurrentState & STATE_PRESENCE) && (pCurrentState & STATE_AUTO)) {
                onPresenceChange(true);
            }
        }
    }
}

void PresenceChannel::processBrightness()
{
    if (pBrightnessOffDelayTime > 0) 
    {
        if (delayCheck(pBrightnessOffDelayTime, paramTimeDelay(PM_pABrightnessOffDelayBase, true)))
        {
            pBrightnessOffDelayTime = 0;
            // we have to turn off light but not presence
            onPresenceChange(false);
        }
    }
}

void PresenceChannel::startAdaptiveBrightness()
{
    // Adaptive brightness calculation is done each time the intended light situation changes
    // This usually happens by turning other lights on or off or dimming them
    if (paramByte(PM_pABrightnessAuto, PM_pABrightnessAutoMask, PM_pABrightnessAutoShift, true) == VAL_PM_LuxAdaptiveOff)
    {
        pCurrentState |= STATE_ADAPTIVE;
        pCurrentState &= ~STATE_ADAPTIVE_READ;
        pAdaptiveDelayTime = delayTimerInit();
    }
}

void PresenceChannel::processAdaptiveBrightness()
{
    // should we calculate adaptive brightness
    if (pCurrentState & STATE_ADAPTIVE) 
    {
        if (!(pCurrentState & STATE_ADAPTIVE_READ) && pAdaptiveDelayTime > 0 && delayCheck(pAdaptiveDelayTime, paramTimeDelay(PM_pAdaptiveDelayBase, false)))
        {
            // we waited the whole adaptive delay time for an according brightness update
            pAdaptiveDelayTime = 0;
            // should we send now a read request?
            if (paramBit(PM_pBrightnessRead, PM_pBrightnessReadMask, false))
            {
                // send a read request
                getKo(PM_KoKOpLux)->requestObjectRead();
                // and wait for an other second
                pCurrentState |= STATE_ADAPTIVE_READ;
                pAdaptiveDelayTime = delayTimerInit();
            }
        }
        else if (pCurrentState & STATE_ADAPTIVE_READ && delayCheck(pAdaptiveDelayTime, 1500))
        {
            // we waited one second for the read and continue processing with current lux value
            pCurrentState &= ~STATE_ADAPTIVE_READ;
            pAdaptiveDelayTime = 0;
        }
        else if (pAdaptiveDelayTime == 0)
        {
            // take current lux value, but not less that turn on limit
            uint32_t lBrightnessOff = MAX((uint32_t)getKo(PM_KoKOpLux)->value(getDPT(VAL_DPT_9)), (uint32_t)(paramWord(PM_pABrightnessOn, true)));
            // add adaptive offset and set it as new off limit
            lBrightnessOff += paramWord(PM_pABrightnessDelta, true);
            getKo(PM_KoKOpLuxOff)->value(lBrightnessOff, getDPT(VAL_DPT_9));
            // and we stop adaptive calculation
            pCurrentState &= ~(STATE_ADAPTIVE | STATE_ADAPTIVE_READ);
        }
    }
}

void PresenceChannel::startOutput(bool iOn)
{
    if (iOn)
        pCurrentValue |= PM_BIT_OUTPUT_SET;
    else
        pCurrentValue &= ~PM_BIT_OUTPUT_SET;
}

void PresenceChannel::forceOutput(bool iOn)
{
    if (iOn)
        pCurrentValue |= PM_BIT_OUTPUT_FORCE;
    else
        pCurrentValue &= ~PM_BIT_OUTPUT_FORCE;
}

void PresenceChannel::syncOutput()
{
    bool lOn = pCurrentValue & PM_BIT_OUTPUT_SET;
    if (lOn)
        pCurrentValue |= PM_BIT_OUTPUT_WRITTEN;
    else
        pCurrentValue &= ~PM_BIT_OUTPUT_WRITTEN;
}

void PresenceChannel::processOutput()
{
    uint8_t lOutput = 0;
    if (!(pCurrentState & STATE_LOCK)) {
        // check for cyclic send of output 1
        if (paramBit(PM_pOutput1Cyclic, PM_pOutput1CyclicMask) && delayCheck(pOutput1CyclicTime, paramTimeDelay(PM_pOutput1CyclicBase)))
            lOutput = 1;
        // check for cyclic send of output 2
        if (paramBit(PM_pOutput2Cyclic, PM_pOutput2CyclicMask) && delayCheck(pOutput2CyclicTime, paramTimeDelay(PM_pOutput2CyclicBase)))
            lOutput |= 2;
        // check for send because of output state change
        uint8_t lValue = pCurrentValue & (PM_BIT_OUTPUT_SET | PM_BIT_OUTPUT_WRITTEN);
        if (lValue > 0 && lValue < (PM_BIT_OUTPUT_SET | PM_BIT_OUTPUT_WRITTEN))
            lOutput = 3;
    }
    if (pCurrentValue & PM_BIT_OUTPUT_FORCE) {
        lOutput = 3;
    }
    if (lOutput)
    {
        // we have to send something
        bool lOn = (pCurrentValue & PM_BIT_OUTPUT_SET);
        if (lOutput & 1) {
            onOutput(VAL_PM_Output1Index, lOn);
            pOutput1CyclicTime = delayTimerInit();
        }
        if (lOutput & 2) {
            onOutput(VAL_PM_Output2Index, lOn);
            pOutput2CyclicTime = delayTimerInit();
        }
        syncOutput();
        forceOutput(false);
    }
}

void PresenceChannel::onOutput(bool iOutputIndex, bool iOn)
{
    static uint8_t sTypeToDpt[5] = {0, VAL_DPT_1, VAL_DPT_5, VAL_DPT_17, VAL_DPT_5001};

    // first check, if output is active
    // get output DPT
    uint8_t lType = iOutputIndex ? paramByte(PM_pOutput2Type, PM_pOutput2TypeMask, PM_pOutput2TypeShift) : paramByte(PM_pOutput1Type, PM_pOutput1TypeMask, PM_pOutput1TypeShift);
    if (lType == 0)
        return;
    uint8_t lFilter = iOutputIndex ? paramByte(PM_pAOutput2Filter, PM_pAOutput2FilterMask, PM_pAOutput2FilterShift, true) : paramByte(PM_pAOutput1Filter, PM_pAOutput1FilterMask, PM_pAOutput1FilterShift, true);
    // get correct value to send
    uint8_t lValue;
    if (iOn && (lFilter & 1)) {
        // send on value if allowed
        lValue = iOutputIndex ? paramByte(PM_pAOutput2On, true) : paramByte(PM_pAOutput1On, true);
        if (sTypeToDpt[lType] == VAL_DPT_17)
            lValue--;
        getKo(iOutputIndex ? PM_KoKOpOutput2 : PM_KoKOpOutput)->value(lValue, getDPT(sTypeToDpt[lType]));
    } else if (!iOn && (lFilter & 2)) {
        // send off value if allowed
        lValue = iOutputIndex ? paramByte(PM_pAOutput2Off, true) : paramByte(PM_pAOutput1Off, true);
        if (sTypeToDpt[lType] == VAL_DPT_17)
            lValue--;
        getKo(iOutputIndex ? PM_KoKOpOutput2 : PM_KoKOpOutput)->value(lValue, getDPT(sTypeToDpt[lType]));
    }
}

void PresenceChannel::loop()
{
    if (!knx.configured())
        return;

    if (paramByte(PM_pChannelActive, PM_pChannelActiveMask, PM_pChannelActiveShift) != PM_VAL_ActiveYes)
        return;

    // here we do the things after setup, but only once in the loop()
    if ((pCurrentState & (STATE_STARTUP | STATE_RUNNING)) == 0) {
        // currently nothing else to do
        // last but not least...
        startStartup();
    }

    if (pCurrentState & STATE_STARTUP)
        processStartup();

    // do no further processing until channel passed its startup time
    if (pCurrentState & STATE_RUNNING)
    {
        // first we handle presence hardware
        startHardwarePresence();

        // we revert the processing order for pipeline events
        // this reduces the chance to have a long running
        // sequence of functions because of according pipeline settings
        // On/Off repeat pipeline
        if (pCurrentState & (STATE_PRESENCE))
            processPresence();
        if (pCurrentState & (STATE_PRESENCE_SHORT))
            processPresenceShort();
        if (pCurrentState & (STATE_MANUAL))
            processManual();
        if (pCurrentState & (STATE_DAY_PHASE_CHANGE))
            processDayPhase();
        if (pCurrentState & (STATE_ADAPTIVE))
            processAdaptiveBrightness();
        // brightness is always evaluated
        processBrightness();
        // output is always evaluated
        processOutput();
    }
}

void PresenceChannel::prepareInternalKo()
{
    // we know the indexes of internal KO
    for (uint8_t lIndex = PM_pNumLux; lIndex <= PM_pNumScene; lIndex = lIndex + 2)
    {
        uint16_t lInternalKo = paramWord(lIndex);
        if (lInternalKo & 0x8000) 
        {
            uint8_t lKoIndex = (lIndex < PM_pNumScene) ? (lIndex - PM_pNumLux) / 2 + PM_KoKOpLux : PM_KoKOpScene;
            sPresence->addKoMap(lInternalKo & 0x7FFF, mChannelId, lKoIndex);
        }
    }
}

void PresenceChannel::setup() 
{
    prepareInternalKo();
    // at the beginning we are on day phase 1
    onDayPhase(0);
    // init auto state
    getKo(PM_KoKOpIsManual)->valueNoSend(false, getDPT(VAL_DPT_1));
    // init lock state
    switch (paramByte(PM_pLockType, PM_pLockTypeMask, PM_pLockTypeShift))
    {
        case VAL_PM_LockTypePriority:
            getKo(PM_KoKOpLock)->valueNoSend((uint8_t)0, getDPT(VAL_DPT_2));
            break;
        case VAL_PM_LockTypeLock:
            getKo(PM_KoKOpLock)->valueNoSend((uint8_t)0, getDPT(VAL_DPT_1));
            break;
        default:
            // do nothing
            break;
    }
}
