#pragma once
#include "PresenceChannel.h"
#include "PMmodul.h"

class Presence
{
public:
    Presence();
    ~Presence();

    // static
    // instance
    bool getHardwarePresence();
    void processReadRequests();
    void processInputKo(GroupObject &iKo);
    bool processDiagnoseCommand(char *iBuffer);
    void debug();
    void setup();
    void loop();

private:
    // support presence hardware
    bool mPresence = false;
    uint32_t mPresenceDelay = 0;
    bool mPresenceLedOn = false;
    bool mInfoLedOn = false;
    bool mPresenceChanged = false;
    // brightness is missing

    // channel handling
    PresenceChannel *mChannel[PM_ChannelCount];
    uint8_t mNumChannels;
    PresenceChannel *getChannel(uint8_t iChannelId);
    uint8_t getChannelId(PresenceChannel *iChannel);

    void processHardwarePresence();
    // bool prepareChannels();
};
