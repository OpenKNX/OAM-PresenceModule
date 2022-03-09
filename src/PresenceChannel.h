#pragma once
#include "knx.h"
#include "Hardware.h"

// State marker (BITFIELD !!!)
#define STATE_STARTUP 1 // startup delay for each channel
#define STATE_RUNNING 2 // this channel is running
#define STATE_MANUAL 4 // manual mode on
#define STATE_PRESENCE 8 // there is presence
#define STATE_PRESENCE_SHORT 16 // short presence evaluation
#define STATE_LOCK 32 // lock state
#define STATE_DAY_PHASE_CHANGE 64 // change day phase at desired point of time

// Value marker (BITFIELD)
#define PM_BIT_OUTPUT_SET 1             // output value to send
#define PM_BIT_OUTPUT_WRITTEN 2         // output value sent
#define PM_BIT_OUTPUT_FORCE 4           // output value sent
#define PM_BIT_DISABLE_BRIGHTNESS_OFF 8 // Brightness off temporarily disabled

#define PM_VAL_OUTPUT_MASK (PM_BIT_OUTPUT_SET | PM_BIT_OUTPUT_WRITTEN)

// and we also define all enum values for PM
#define VAL_LedOffPM 0
#define VAL_LedOnPM 1
#define VAL_LedOnChannelPM 2
#define VAL_LedKnxPM 3

// presence type
#define VAL_PM_PresenceTypeOff 0
#define VAL_PM_PresenceTypeSwitch 1
#define VAL_PM_PresenceTypeTrigger 2

// output index, there are 2 outputs
#define VAL_PM_Output1Index 0
#define VAL_PM_Output2Index 1

// output types
#define VAL_PM_Switch 0
#define VAL_PM_Value 1
#define VAL_PM_Scene 2
#define VAL_PM_Dim 3

// lock type
#define VAL_PM_LockTypeNone 0
#define VAL_PM_LockTypePriority 1
#define VAL_PM_LockTypeLock 2

// lock ouptut
#define VAL_PM_LockOutputNone 0
#define VAL_PM_LockOutputOff 1
#define VAL_PM_LockOutputOn 2
#define VAL_PM_LockOutputCurrent 3

// forward declaration
class Presence;

class PresenceChannel
{
  private:
    uint8_t mChannelId = 0; // zero based
    uint8_t mCurrentDayPhase = 0; // zero based

    uint32_t calcParamIndex(uint16_t iParamIndex, bool iWithPhase);
    uint16_t calcKoNumber(uint8_t iKoIndex);
    GroupObject *getKo(uint8_t iKoIndex);

    bool paramBit(uint16_t iParamIndex, uint8_t iParamMask, bool iWithPhase = false);
    uint8_t paramByte(uint16_t iParamIndex, uint8_t iParamMask, uint8_t iParamShift, bool iWithPhase = false);
    uint8_t paramByte(uint16_t iParamIndex, bool iWithPhase = false);
    uint16_t paramWord(uint16_t iParamIndex, bool iWithPhase = false);
    uint32_t paramInt(uint16_t iParamIndex, bool iWithPhase = false);

    uint32_t paramTimeDelay(uint16_t iParamIndex, bool iWithPhase = false, bool iAsSeconds = false);

    void startStartup();
    void processStartup();

    bool getRawPresence();
    void startPresenceTrigger();
    void startPresence(uint8_t iPresenceType, GroupObject &iKo);
    void startPresence(bool iForce = false);
    void processPresence();
    void endPresence(bool iSend = true);
    void startPresenceShort();
    void processPresenceShort();
    void onPresenceBrightnessChange(bool iOn);
    void onPresenceChange(bool iOn);

    void startAuto(bool iOn);
    void processAuto();
    void startManual(bool iOn);
    void processManual();
    void onManualChange(bool iOn);
    void startLock();
    void processLock();
    void onLock(bool iLockOn, uint8_t iLockOnSend, uint8_t iLockOffSend);
    void startReset();
    
    void startActorState(GroupObject &iKo);
    void processActorState();

    void startBrightness(GroupObject &iKo);
    void processBrightness();

    int8_t getDayPhaseFromKO();
    void startDayPhase();
    void processDayPhase();
    void onDayPhase(uint8_t iPhase);

    void startOutput(bool iOn);
    void forceOutput(bool iOn);
    void syncOutput();
    void processOutput();
    void onOutput(bool iOutputIndex, bool iOn);

  protected:
    static Presence *sPresence;
    static uint8_t sDayPhaseParameterSize; // memory block size of day phase parameters, calculated in setup

    uint32_t pCurrentState;
    uint32_t pCurrentValue;
    uint32_t pOnDelay;
    uint32_t pPresenceDelayTime = 0;  // Nachlaufzeit
    uint32_t pPresenceShortDelayTime = 0; // Kurze Anwesenheit Nachlaufzeit
    uint32_t pManualFallbackTime = 0; // Rückfallzeit aus Manuellmodus
    uint32_t pOutput1CyclicTime = 0;  // Zyklisch senden Ausgang 1
    uint32_t pOutput2CyclicTime = 0;  // Zyklisch senden Ausgang 2
    uint32_t pLockDelayTime = 0;  // Rückfallzeit Sperre/Zwangsführung

  public:
    PresenceChannel(uint8_t iChannelNumber);
    ~PresenceChannel();

    static void setPresence(Presence *iPresence);
    static void setDayPhaseParameterSize(uint8_t iSize);

    uint8_t getIndex();

    bool processReadRequest();
    void processInputKo(GroupObject &iKo);
    bool processDiagnoseCommand(char *iBuffer);
    void setup();
    void loop();
};
