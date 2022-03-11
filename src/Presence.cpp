#include "Helper.h"
#include "Hardware.h"

#include "IncludeManager.h"

#include "PresenceChannel.h"
#include "Logic.h"
#include "KnxHelper.h"
#include "Presence.h"

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
        uint8_t lNibbleHigh = (mNumChannels - 1) / 10;
        uint8_t lNibbleLow = (mNumChannels - 1) % 10;
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
    if (iKo.asap() >= PM_KoOffset && iKo.asap() < PM_KoOffset + mNumChannels * PM_KoBlockSize) {
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

void Presence::processHardwarePresence()
{

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

    if (knx.paramByte(LOG_HardwarePM) && LOG_HardwarePMMask)
        processHardwarePresence();

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
        mNumChannels = knx.paramByte(LOG_PMChannels);
        if (COUNT_PM_CHANNEL < mNumChannels)
        {
            char lErrorText[80];
            sprintf(lErrorText, "FATAL: Firmware compiled for %d PresenceChannels, but knxprod needs %d!\n", COUNT_PM_CHANNEL, mNumChannels);
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
    }
}
