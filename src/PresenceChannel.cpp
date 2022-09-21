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
    if (iBuffer[3] == 't')
    {
        // output remaining presence time
        int16_t lPresence = 0;
        if (pCurrentState & STATE_PRESENCE)
        {
            // we present both, long and short presence
            lPresence = getKo(PM_KoKOpPresenceDelay)->value(getDPT(VAL_DPT_7));
            if (pPresenceDelayTime > 0)
            {
                lPresence = lPresence - (uint16_t)((millis() - pPresenceDelayTime) / 1000);
            }
            // Long presence output is "L mm:ss "
            snprintf(iBuffer, 14, "L %02d:%02d ", (lPresence / 60) % 60, lPresence % 60);
            if (pCurrentState & STATE_PRESENCE_SHORT)
            {
                lPresence = paramTimeDelay(PM_pAPresenceShortDurationBase, true, true);
                lPresence = lPresence - (uint16_t)((millis() - pPresenceShortDelayTime) / 1000);
                if (lPresence >= 0)
                {
                    // Short presence duration output is "L mm:ss S m:ss"
                    snprintf(iBuffer + 8, 7, "S %01d:%02d", (lPresence / 60) % 60, lPresence % 60);
                }
                else
                {
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
    else if (iBuffer[3] == 'l')
    {
        // output leave room modes
        // p<nn>l
        // L (OFF|TOT|T+R|B+T|BTR) T mm:ss
        if (isLeaveRoom())
        {
            uint8_t lIndex = 0;
            int16_t lTime = 0;
            const char *lModes = "OFFTOTT+RB+TBTR";
            // we present leave room mode
            iBuffer[lIndex++] = 'L';
            iBuffer[lIndex++] = ' ';
            for (uint8_t lCount = 0; lCount < 3; lCount++)
                iBuffer[lIndex++] = lModes[(pLeaveRoomMode * 3 + lCount)];
            iBuffer[lIndex++] = ' ';
            iBuffer[lIndex] = 0; // do not increment lIndex here
            if (pDowntimeDelayTime > 0)
            {
                lTime = paramTimeDelay(PM_pDowntimeOffBase, false, true);
                lTime = lTime - (uint16_t)((millis() - pDowntimeDelayTime) / 1000);
                // Downtime output is "T mm:ss "
                if (lTime >= 0)
                    snprintf(iBuffer + lIndex, 8, "T %02d:%02d ", (lTime / 60) % 60, lTime % 60);
                else
                    snprintf(iBuffer + lIndex, 8, "T-%02d:%02d ", (-lTime / 60) % 60, -lTime % 60);
            }
        }
        else if (pCurrentState & STATE_RUNNING)
        {
            sprintf(iBuffer, "no leave room");
        }
        else
        {
            sprintf(iBuffer, "inactive");
        }
        lResult = true;
    }
    else if (iBuffer[3] == 's')
    {
        if (iBuffer[4] == '1')
        {
            // long version
            // "aut0 day13 lck"
            if (pCurrentState & STATE_MANUAL)
                sprintf(iBuffer, "man");
            else if (pCurrentState & STATE_AUTO)
                sprintf(iBuffer, "aut");
            else
                sprintf(iBuffer, "nor");
            iBuffer[3] = (pCurrentValue & PM_BIT_OUTPUT_SET) ? '1' : '0';
            iBuffer[4] = ' ';
        }
        else
        {
            // short version
            // "[NAM][01] D[1-4][1-4] [L-][H-][X-][R-][T-]"
            // N=normal, A=auto, M=manual
            // 0=off, 1=on
            // D=day phase
            // 1-4=current phase
            // 1-4=next phase
            // L=is lock, -=unlock
            // H=in helligkeitsberechnung, -=normal
            // X=disable brightness handling, -=normal
            // R=leave Room is active, -=not active
            // T=in totzeit, -=normal
            uint8_t lIndex = 0;
            if (pCurrentState & STATE_MANUAL)
                iBuffer[lIndex++] = 'M';
            else if (pCurrentState & STATE_AUTO)
                iBuffer[lIndex++] = 'A';
            else
                iBuffer[lIndex++] = 'N';

            iBuffer[lIndex++] = (pCurrentValue & PM_BIT_OUTPUT_SET) ? '1' : '0';
            iBuffer[lIndex++] = ' ';
            iBuffer[lIndex++] = 'D';
            iBuffer[lIndex++] = mCurrentDayPhase + 49;
            iBuffer[lIndex++] = getDayPhaseFromKO() + 49;
            iBuffer[lIndex++] = ' ';
            iBuffer[lIndex++] = (pCurrentState & STATE_LOCK) ? 'L' : '-';
            iBuffer[lIndex++] = (pCurrentState & STATE_ADAPTIVE) ? 'H' : '-';
            iBuffer[lIndex++] = (pCurrentValue & PM_BIT_DISABLE_BRIGHTNESS) ? 'X' : '-';
            iBuffer[lIndex++] = (isLeaveRoom()) ? 'R' : '-';
            iBuffer[lIndex++] = (pCurrentState & STATE_DOWNTIME) ? 'T' : '-';
            // 3 char free
            iBuffer[lIndex++] = 0;
            lResult = true;
        }
    }
    return lResult;
}

void PresenceChannel::processInputKo(GroupObject &iKo, int8_t iKoIndex)
{
    // we process KO only if we are running
    if (pCurrentState & STATE_RUNNING) {
        // search for correct KO
        bool lIsTrigger;
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
                lIsTrigger = paramBit(PM_pPresenceType, PM_pPresenceTypeMask);
                startPresence(lIsTrigger, iKo);
                break;
            case PM_KoKOpPresence2:
                // change of presence information
                lIsTrigger = paramBit(PM_pMoveType, PM_pMoveTypeMask);
                startPresence(lIsTrigger, iKo);
                break;
            case PM_KoKOpSetAuto:
                // Automatic mode
                startAuto(lValue, false);
                break;
            case PM_KoKOpSetManual:
                // check for two button mode
                if (paramBit(PM_pManualModeKeyCount, PM_pManualModeKeyCountMask))
                    startManual(lValue, false);
                else // use single button mode
                    if (lValue)
                        startManual(pCurrentValue & PM_BIT_OUTPUT_SET, true);
                    else
                        startAuto(pCurrentValue & PM_BIT_OUTPUT_SET, true);
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
                    startAuto(false, false);
                    break;
                case VAL_PM_SA_AutoOn:
                    startAuto(true, false);
                    break;
                case VAL_PM_SA_ManualOff:
                    startManual(false, false);
                    break;
                case VAL_PM_SA_ManualOn:
                    startManual(true, false);
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
                    startLeaveRoom(false);
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

void PresenceChannel::processReadRequests()
{
    // this method is called after startup delay and executes read requests, which should just happen once after startup
    if (pReadRequestCounter < 255 && delayCheck(pReadRequestDelay, 500))
    {
        pReadRequestCounter += 1;
        pReadRequestDelay = delayTimerInit();
        switch (pReadRequestCounter)
        {
            case 1:
                if (paramBit(PM_pStartReadLux, PM_pStartReadLuxMask))
                    getKo(PM_KoKOpLux)->requestObjectRead();
                break;
            case 2:
                if (paramBit(PM_pStartReadPresence1, PM_pStartReadPresence1Mask))
                    getKo(PM_KoKOpPresence1)->requestObjectRead();
                break;
            case 3:
                if (paramBit(PM_pStartReadPresence2, PM_pStartReadPresence2Mask))
                    getKo(PM_KoKOpPresence2)->requestObjectRead();
                break;
            case 4:
                if (paramBit(PM_pStartReadAktorState, PM_pStartReadAktorStateMask))
                    getKo(PM_KoKOpAktorState)->requestObjectRead();
                break;
            case 5:
                if (paramBit(PM_pStartReadLock, PM_pStartReadLockMask))
                    getKo(PM_KoKOpLock)->requestObjectRead();
                break;
            case 6:
                if (paramBit(PM_pStartReadDayPhase, PM_pStartReadDayPhaseMask))
                    getKo(PM_KoKOpDayPhase)->requestObjectRead();
                break;
            case 7:
                if (paramBit(PM_pStartReadScene, PM_pStartReadSceneMask))
                    getKo(PM_KoKOpScene)->requestObjectRead();
                break;

            default:
                pReadRequestCounter = 255; // all read requests processed
                break;
        }
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
        uint8_t lScene = (uint8_t)getKo(PM_KoKOpDayPhase)->value(getDPT(VAL_DPT_17)) + 1;
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

void PresenceChannel::onDayPhase(uint8_t iPhase, bool iIsStartup /* = false */)
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
    // if short presence is off, we stop a potential running short presence from other phase
    if (!paramBit(PM_pAPresenceShort, PM_pAPresenceShortMask, true))
        endPresenceShort();

    // day phase change should resend except on startup
    if (!iIsStartup)
        forceOutput(true);
}

bool PresenceChannel::getRawPresence(bool iJustMove /* false */)
{
    // iJustMove is ignored, if there is only presence available
    bool lJustMove = false;
    // are external inputs offering presence and move?
    if (paramByte(PM_pPresenceInputs, PM_pPresenceInputsMask, PM_pPresenceInputsShift) == VAL_PM_PI_PresenceMove)
        lJustMove = iJustMove;
    bool lPresence = getKo(PM_KoKOpPresence2)->value(getDPT(VAL_DPT_1));
    if (!lPresence && !lJustMove)
        lPresence = getKo(PM_KoKOpPresence1)->value(getDPT(VAL_DPT_1));
    // if hardware presence sensor is available, we evaluate its value
    if (!lPresence)
        lPresence = getHardwarePresence(iJustMove); // for internal sensors, we use iJustMove !!!
    return lPresence;
}

float PresenceChannel::getRawBrightness()
{
    float lResult = NO_NUM;
    if (paramBit(PM_pBrightnessIntern, PM_pBrightnessInternMask))
        lResult = sPresence->getHardwareBrightness();
    else
        lResult = getKo(PM_KoKOpLux)->value(getDPT(VAL_DPT_9));
    return lResult;
}

bool PresenceChannel::getHardwarePresence(bool iJustMove /* false */)
{
    // if hardware presence sensor is available, we evaluate its value
    bool lPresence = false;
    if (paramByte(PM_pPresenceUsage, PM_pPresenceUsageMask, PM_pPresenceUsageShift) == VAL_PM_PresenceUsageMove)
        lPresence = sPresence->getHardwareMove();
    if (!iJustMove && !lPresence && paramByte(PM_pPresenceUsage, PM_pPresenceUsageMask, PM_pPresenceUsageShift) == VAL_PM_PresenceUsagePresence)
        lPresence = sPresence->getHardwarePresence();
    return lPresence;
}

// entry point for presence trigger (means start or restart presence delay)
void PresenceChannel::startPresenceTrigger(bool iManual)
{
    startPresence(true, iManual);
    startPresence(false, iManual);
    // pPresenceDelayTime = delayTimerInit(); // diese Variante führt zu Issue #12
}

void PresenceChannel::startHardwarePresence()
{
    // we derive here a presence trigger from hardware sensor by polling
    // we have to eval Hardware move if required
    bool lValue = false;
    bool lTrigger = false;
    if (paramByte(PM_pPresenceUsage, PM_pPresenceUsageMask, PM_pPresenceUsageShift) == VAL_PM_PresenceUsageMove)
    {
        lValue = sPresence->getHardwareMove();
        if (mHardwareMove != lValue)
        {
            mHardwareMove = lValue;
            lTrigger = true;
        }
    }
    // and we eval hardware presence if required
    if (!lValue && paramByte(PM_pPresenceUsage, PM_pPresenceUsageMask, PM_pPresenceUsageShift) == VAL_PM_PresenceUsagePresence)
    {
        lValue = sPresence->getHardwarePresence();
        if (mHardwarePresence != lValue)
        {
            mHardwarePresence = lValue;
            lTrigger = true;
        }
    }
    // but we trigger just once
    if (lTrigger)
        startPresence(lValue, false);
}

void PresenceChannel::startHardwareBrightness() 
{
    // if hardware brightness is handled, no external brightness is available
    if (paramByte(PM_HWLux, PM_HWLuxMask, PM_HWLuxShift) > 0 && !paramBit(PM_pBrightnessIndependent, PM_pBrightnessIndependentMask))
    {
        // we have to poll here
        if (delayCheck(mBrightnessPollDelay, 1500))
        {
            mBrightnessPollDelay = delayTimerInit();
            startBrightness();
        }
    }
}

// helper entry point for presence calculation initiated by a KO
void PresenceChannel::startPresence(bool iIsTrigger, GroupObject &iKo)
{
    bool lPresenceValue = iKo.value(getDPT(VAL_DPT_1));
    // we ignore explicitly OFF telegrams of triggered input
    if (iIsTrigger && !lPresenceValue)
        return;
    startPresence(false, false);
    if (iIsTrigger && lPresenceValue)
    {
        // triggered input sent a 1, we immediately set it to 0
        iKo.value(false, getDPT(VAL_DPT_1));
        // afterwards we call ourself to evaluate 0 action
        startPresence(false, false);
    }
}

// main entry point for presence calculation (KO independent), implemented as switching presence channel 
void PresenceChannel::startPresence(bool iForce, bool iManual)
{
    // during leave room we ignore any presence processing
    if (isLeaveRoom())
        return;

    // this method handles both presence inputs. We handle both combined by an OR.
    if (iForce || getRawPresence()) {
        // do according actions if presence changes
        if (!(pCurrentState & STATE_PRESENCE)) {
            // the following is just allowed for full automatic on (Vollautomat)
            // or if manual on is requested an manual on is done.
            uint8_t lDayPhaseFunction = paramByte(PM_pADayPhaseFunction, PM_pADayPhaseFunctionMask, PM_pADayPhaseFunctionShift, true);
            bool lTurnOn = (lDayPhaseFunction == VAL_PM_PHASE_FULL || lDayPhaseFunction == VAL_PM_PHASE_HALF_OFF);
            if (!lTurnOn) lTurnOn = (lDayPhaseFunction == VAL_PM_PHASE_HALF_ON && iManual);
            if (lTurnOn)
            {
                if (!iManual) startPresenceShort();
                onPresenceBrightnessChange(true);
                // presence is turned on, we set the state and delete delay timer
                pCurrentState |= STATE_PRESENCE;
            }
        } else if (pCurrentState & STATE_PRESENCE_SHORT) {
            processPresenceShort();
        }
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
    endPresenceShort();
    pCurrentState &= ~(STATE_PRESENCE | STATE_AUTO);
    pCurrentValue &= ~PM_BIT_DISABLE_BRIGHTNESS;
    pPresenceDelayTime = 0;
    if (iSend) onPresenceChange(false);
}

void PresenceChannel::startPresenceShort()
{
    // during leave room we ignore any presence processing
    if (isLeaveRoom())
        return;

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
        uint32_t lEndTime = paramTimeDelay(PM_pAPresenceShortDurationBase, true) + paramTimeDelay(PM_pAPresenceShortDelayBase, true);
        if (delayCheck(pPresenceShortDelayTime, lEndTime + 300))
        {
            // there was no new presence evaluation during short presence delay, so we know, short presence is valid here
            endPresence();
        } 
        else 
        {
            // if we get any further presence information, we stop short presence without ending normal presence
            // in addition, we check if move or move+presence is used for presence evaluation
            bool lUsePresence = paramBit(PM_pAPresenceShortCalculation, PM_pAPresenceShortCalculationMask, true);
            bool lPresence = getRawPresence(!lUsePresence);
            if (lPresence) 
            {
                endPresenceShort();
                // in case of passageway we turn on ouput after short presence
                bool lPassageway = paramBit(PM_pAPresenceShortNoSwitch, PM_pAPresenceShortNoSwitchMask, true);
                if (lPassageway)
                    onPresenceChange(true);
            }
        }
    }
}

void PresenceChannel::endPresenceShort()
{
    // end short presence without ending presence
    pCurrentState &= ~STATE_PRESENCE_SHORT;
    pPresenceShortDelayTime = 0;
}

void PresenceChannel::onPresenceBrightnessChange(bool iOn)
{
    // during leave room we ignore any presence processing
    if (isLeaveRoom())
        return;

    // calculate output dependent on brightness and auto mode
    if (iOn && !paramBit(PM_pBrightnessIndependent, PM_pBrightnessIndependentMask)) 
    {
        // check brightness in case of turning on
        if ((uint32_t)getRawBrightness() <= (uint32_t)getKo(PM_KoKOpLuxOn)->value(getDPT(VAL_DPT_9)))
            onPresenceChange(iOn);
    }
    else // turn off if brightness independent
        onPresenceChange(iOn);
}

void PresenceChannel::onPresenceChange(bool iOn)
{
    
    // Output is only influenced in auto mode
    if (!(pCurrentState & STATE_MANUAL))
    {
        // We turn on or off, but only if automatic off is not forbidden
        uint8_t lDayPhaseFunction = paramByte(PM_pADayPhaseFunction, PM_pADayPhaseFunctionMask, PM_pADayPhaseFunctionShift, true);
        bool lTurnOff = (lDayPhaseFunction == VAL_PM_PHASE_FULL || lDayPhaseFunction == VAL_PM_PHASE_HALF_ON);
        lTurnOff = lTurnOff || iOn; // turn on is always allowed
        if (lTurnOff)
        {
            bool lPassageway = paramBit(PM_pAPresenceShortNoSwitch, PM_pAPresenceShortNoSwitchMask, true);
            // in a passageway we do not turn on during short presence
            if (!(iOn && lPassageway && (pCurrentState & STATE_PRESENCE_SHORT)))
                startOutput(iOn);
        }
    }
}

void PresenceChannel::startLeaveRoom(bool iSuppressOutput)
{
    pLeaveRoomMode = paramByte(PM_pLeaveRoomModeAll, PM_pLeaveRoomModeAllMask, PM_pLeaveRoomModeAllShift);
    switch (pLeaveRoomMode)
    {
        case VAL_PM_LRM_Downtime:
        case VAL_PM_LRM_DowntimeReset:
            // in this case we just wait until downtime passed and afterwards we wait for the first Move
            startDowntime(); // has to be first to set correct state
            onManualChange(false);
            endPresence(!iSuppressOutput);
            break;
        case VAL_PM_LRM_MoveDowntime:
        case VAL_PM_LRM_MoveDowntimeReset:
            // dispatch to process handler
            pCurrentState |= STATE_LEAVE_ROOM;
            onManualChange(false);
            endPresence(!iSuppressOutput);
            break;

        default:
            // if there is no leave room configured, we process auto off
            startAuto(false, iSuppressOutput);
            break;
    }
}

void PresenceChannel::processLeaveRoom()
{
    switch (pLeaveRoomMode)
    {
        case VAL_PM_LRM_Downtime:
            // we wait for the next move, which also starts new presence cycle
            if (getRawPresence(true))
            {
                endLeaveRoom();
                startPresence(false, false);
            }
            // if somewhen presence vanishes, we also continue in normal mode
            if (!getRawPresence())
                endLeaveRoom();
            break;
        case VAL_PM_LRM_DowntimeReset:
            // we send a reset to external PM and go to normal mode
            getKo(PM_KoKOpResetExternalPM)->value(true, getDPT(VAL_DPT_1));
            // TODO: reset internal PIR, as soon as implemented
            endLeaveRoom();
            break;
        case VAL_PM_LRM_MoveDowntime:
        case VAL_PM_LRM_MoveDowntimeReset:
            // we wait until current move gets inactive
            if (!getRawPresence(true))
            {
                // from now on it is the same like downtime processing
                pLeaveRoomMode = (pLeaveRoomMode == VAL_PM_LRM_MoveDowntime) ? VAL_PM_LRM_Downtime : VAL_PM_LRM_DowntimeReset;
                pCurrentState &= ~STATE_LEAVE_ROOM;
                startDowntime();
            }
            break;

        default:
            break;
    }
}

void PresenceChannel::endLeaveRoom()
{
    pCurrentState &= ~(STATE_DOWNTIME | STATE_LEAVE_ROOM);
    pDowntimeDelayTime = 0;
}

bool PresenceChannel::isLeaveRoom()
{
    return (pCurrentState & (STATE_DOWNTIME | STATE_LEAVE_ROOM));
}

// downtime during leave room
void PresenceChannel::startDowntime()
{
    // set state
    pCurrentState |= STATE_DOWNTIME;
    // set downtime timer
    pDowntimeDelayTime = delayTimerInit();
}

void PresenceChannel::processDowntime()
{
    if (pDowntimeDelayTime > 0 && delayCheck(pDowntimeDelayTime, paramTimeDelay(PM_pDowntimeOffBase, false))) 
    {
        pDowntimeDelayTime = 0;
        // we end downtime handling
        pCurrentState &= ~STATE_DOWNTIME;
        // and wait for next move
        pCurrentState |= STATE_LEAVE_ROOM;
    }
}

void PresenceChannel::startAuto(bool iOn, bool iSuppressOutput)
{
    // end any leave room processing
    endLeaveRoom();
    // ensure auto mode
    onManualChange(false);
    // check if we have to go to leave room
    uint8_t lLeaveRoomMode = paramByte(PM_pLeaveRoomModeAll, PM_pLeaveRoomModeAllMask, PM_pLeaveRoomModeAllShift);
    if (!iOn && lLeaveRoomMode > VAL_PM_LRM_None)
        startLeaveRoom(iSuppressOutput);
    else
    {
        // we start presence delay
        startPresenceTrigger(true);
        // and we also start/reset short presence here
        // new: for manual usage we don't want short presence
        // startPresenceShort();
        // disable brightness handling according to current brightness
        disableBrightness(iOn);
        // set state
        pCurrentState |= STATE_AUTO;
        // set output according to input value
        startOutput(iOn);
        if (iSuppressOutput)
            syncOutput();
        else
            forceOutput(true);
    }
}

void PresenceChannel::processAuto()
{
}

void PresenceChannel::startManual(bool iOn, bool iSuppressOutput)
{
    // end any leave room processing
    endLeaveRoom();
    // ensure manual mode
    onManualChange(true);
    // we stop presence delay
    endPresence();
    // set output according to input value
    startOutput(iOn);
    if (iSuppressOutput)
        syncOutput();
    else
        forceOutput(true);
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
        uint32_t lPresenceDelayTime;
        switch (iLockOffSend)
        {
        case VAL_PM_LockOutputNone:
            // nothing should be send, so we set the output state to current state
            syncOutput();
            break;
        case VAL_PM_LockOutputOff:
            startAuto(false, false);
            forceOutput(true);
            break;
        case VAL_PM_LockOutputOn:
            startAuto(true, false);
            forceOutput(true);
            break;
        case VAL_PM_LockOutputCurrent:
            // we send current state by reevaluation
            lPresenceDelayTime = pPresenceDelayTime;
            startPresence(false, false);
            pPresenceDelayTime = lPresenceDelayTime;
            forceOutput(true);
            break;
        default:
            break;
        }
    }
    // we have to sync KO according to lock state
    uint8_t lLockType = paramByte(PM_pLockType, PM_pLockTypeMask, PM_pLockTypeShift);
    uint8_t lLockValue = (iLockOn << 1);
    uint8_t lLockSend = lLockValue ? iLockOnSend : iLockOffSend;
    switch (lLockType)
    {
        case VAL_PM_LockTypePriority:
            if (lLockSend == VAL_PM_LockOutputNone || lLockSend == VAL_PM_LockOutputCurrent)
                lLockValue |= ((pCurrentValue & PM_BIT_OUTPUT_SET) > 0);
            else
                lLockValue |= (lLockSend == VAL_PM_LockOutputOn);
            getKo(PM_KoKOpLock)->valueNoSend(lLockValue, getDPT(VAL_DPT_5));
            break;
        case VAL_PM_LockTypeLock:
            getKo(PM_KoKOpLock)->valueNoSend(iLockOn, getDPT(VAL_DPT_1));
            break;
        default:
            // do nothing
            break;
    }
}

void PresenceChannel::startReset()
{
    // We reset PM so that next (or an existing) presence signal immediately turns output on
    endLeaveRoom();
    onManualChange(false);
    endPresence(true);

    // Unclear: how to handle lock?
    // Unclear: how to handle slave PMs
    // Unclear: do we restore here also day phase settings?

    // finally we look if current presence signal is there
    startPresence(false, false);
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
    if (lValue)
        startAuto(lValue, true);
    else
        startLeaveRoom(true);
    // but we do not send anything to the knx bus
    // syncOutput();
    // but we do not enter Auto state
    pCurrentState &= ~STATE_AUTO;
    // and we do not disable brightness handling
    pCurrentValue &= ~PM_BIT_DISABLE_BRIGHTNESS;
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
    uint32_t lBrightness;
    switch (lLuxAutoOff)
    {
        case VAL_PM_LuxAdaptiveOff:
            // for adaptive off the calculation is async
            startAdaptiveBrightness();
            break;
        case VAL_PM_LuxAbsoluteOff:
            // for absolute off we simply add the offset to current on limit
            lBrightness = getKo(PM_KoKOpLuxOn)->value(getDPT(VAL_DPT_9));
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
    // during leave room we ignore any brightness processing
    if (isLeaveRoom())
        return;

    // should we suppress brightness evaluation?
    bool lEvalBrightness = !(pCurrentValue & PM_BIT_DISABLE_BRIGHTNESS);
    // or are we working brightness independent?
    lEvalBrightness = lEvalBrightness && (!paramBit(PM_pBrightnessIndependent, PM_pBrightnessIndependentMask));
    // or are we in manual mode?
    lEvalBrightness = lEvalBrightness && ((pCurrentState & (STATE_MANUAL | STATE_LOCK)) == 0);
    if (lEvalBrightness) 
    {
        // first check for upper value, if higher, then switch off
        uint32_t lBrightness = getRawBrightness();
        // but only, if we are not calculating a new off value
        if (!(pCurrentState & STATE_ADAPTIVE) && lBrightness > (uint32_t)getKo(PM_KoKOpLuxOff)->value(getDPT(VAL_DPT_9)))
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
            // except we are in auto state (technically here it is Auto-Off), we should not turn on
            if ((pCurrentState & STATE_PRESENCE) && (pCurrentState & STATE_AUTO) == 0) 
                onPresenceChange(true);
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
            // if brightness handling is allowed, we have to disable auto mode
            pCurrentState &= ~STATE_AUTO;
        }
    }
}

void PresenceChannel::disableBrightness(bool iOn)
{
    // are we brightness dependant
    if (!paramBit(PM_pBrightnessIndependent, PM_pBrightnessIndependentMask))
    {
        // get current brightness
        uint32_t lBrightness = getRawBrightness();
        // we disable brightness handling according to current brightness and current output state
        // turn on even though there is enough light
        bool lDisable1 = iOn && (lBrightness > (uint32_t)getKo(PM_KoKOpLuxOff)->value(getDPT(VAL_DPT_9)));
        // turn off even though it is too dark 
        bool lDisable2 = !iOn && (lBrightness < (uint32_t)getKo(PM_KoKOpLuxOff)->value(getDPT(VAL_DPT_9)));
        if (lDisable1 || lDisable2)
            pCurrentValue |= PM_BIT_DISABLE_BRIGHTNESS;
        else
            pCurrentValue &= ~PM_BIT_DISABLE_BRIGHTNESS;
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
            uint32_t lBrightnessOff = MAX((uint32_t)getRawBrightness(), (uint32_t)(paramWord(PM_pABrightnessOn, true)));
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
        // // check for cyclic send of output 1
        // if (paramBit(PM_pOutput1Cyclic, PM_pOutput1CyclicMask) && delayCheck(pOutput1CyclicTime, paramTimeDelay(PM_pOutput1CyclicBase)))
        //     lOutput = 1;
        // // check for cyclic send of output 2
        // if (paramBit(PM_pOutput2Cyclic, PM_pOutput2CyclicMask) && delayCheck(pOutput2CyclicTime, paramTimeDelay(PM_pOutput2CyclicBase)))
        //     lOutput |= 2;
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
            // pOutput1CyclicTime = delayTimerInit();
        }
        if (lOutput & 2) {
            onOutput(VAL_PM_Output2Index, lOn);
            // pOutput2CyclicTime = delayTimerInit();
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
        // handle read requests
        processReadRequests();
        // handle presence hardware
        startHardwarePresence();
        // handle brightness hardware
        startHardwareBrightness();

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
        if (pCurrentState & (STATE_LEAVE_ROOM))
            processLeaveRoom();
        if (pCurrentState & (STATE_DOWNTIME))
            processDowntime();
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
    onDayPhase(0, true);
    // init output
    startOutput(false);
    forceOutput(false);
    syncOutput();
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
