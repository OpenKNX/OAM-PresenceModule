#pragma once
#include "PresenceChannel.h"
#include "PMmodul.h"
#include "Sensor.h"
#include "SensorMR24xxB1.h"

class Presence
{
public:
  enum LedCaller
  {
      CallerNone,
      CallerMove,
      CallerPresence,
      CallerLock,
      CallerKnxMove,
      CallerKnxPresence
  };

  Presence();
  ~Presence();

  // static
  // instance
  bool PresenceTrigger = false;
  bool MoveTrigger = false;
  bool getHardwarePresence();
  bool getHardwareMove();
  void processLED(bool iOn, LedCaller iCaller);
  void processReadRequests();
  void processInputKo(GroupObject &iKo);
  bool processDiagnoseCommand(char *iBuffer);
  void debug();
  void setup();
  void loop();

private:
  // support presence hardware
  float mPresenceCombined = 0;
  bool mPresence = false;
  uint8_t mMove = 0;
  float mMoveSpeed = 0;
  uint32_t mPresenceDelay = 0;
  bool mPresenceLedOn = false;
  bool mInfoLedOn = false;
  bool mPresenceChanged = false;
  uint8_t mScenario = 0;
  uint8_t mSensitivity = 0;
  // brightness is missing
  #ifdef HF_POWER_PIN
  SensorMR24xxB1 *mPresenceSensor;
  #endif
  Sensor *mBrightnessSensor;
  uint32_t mHfPowerCycleDelay = 0;
  bool mDoPresenceHardwareCycle = 0;
  
  void startSensor();

  // channel handling
  PresenceChannel *mChannel[PM_ChannelCount];
  uint8_t mNumChannels;
  PresenceChannel *getChannel(uint8_t iChannelId);
  uint8_t getChannelId(PresenceChannel *iChannel);

  void processHardwarePresence();
  void startPowercycleHfSensor();
  void processPowercycleHfSensor();
  // bool prepareChannels();
};
