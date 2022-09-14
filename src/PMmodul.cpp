#ifdef PMMODULE
#include "Helper.h"

#include "IncludeManager.h"

#include "Presence.h"
#include "PresenceChannel.h"
#include "Logic.h"
#include "KnxHelper.h"

struct sRuntimeInfo
{
    uint32_t startupDelay;
    uint32_t heartbeatDelay;
};

sRuntimeInfo gRuntimeData;

Presence gPresence;
Logic gLogic;

void ProcessHeartbeat()
{
    // the first heartbeat is send directly after startup delay of the device
    if (gRuntimeData.heartbeatDelay == 0 || delayCheck(gRuntimeData.heartbeatDelay, getDelayPattern(LOG_HeartbeatDelayBase)))
    {
        // we waited enough, let's send a heartbeat signal
        knx.getGroupObject(LOG_KoHeartbeat).value(true, getDPT(VAL_DPT_1));
        gRuntimeData.heartbeatDelay = millis();
        // debug entry point
        // gPresence.debug();
        gLogic.debug();
    }
}

void ProcessReadRequests() {
    // this method is called after startup delay and executes read requests, which should just happen once after startup
    static bool sCalledProcessReadRequests = false;
    if (!sCalledProcessReadRequests)
    {
        gPresence.processReadRequests();
        gLogic.processReadRequests();
        sCalledProcessReadRequests = true;
    }
}

// true solgange der Start des gesamten Moduls verzögert werden soll
bool startupDelay()
{
    return !delayCheck(gRuntimeData.startupDelay, getDelayPattern(LOG_StartupDelayBase, true));
}

bool processDiagnoseCommand()
{
    char *lBuffer = gLogic.getDiagnoseBuffer();
    bool lOutput = false;
    if (lBuffer[0] == 'v')
    {
        // Command v: retrun fimware version, do not forward this to logic,
        // because it means firmware version of the outermost module
        // sprintf(lBuffer, "VER [%d] %d.%d", cFirmwareMajor, cFirmwareMinor, cFirmwareRevision);
        lOutput = true;
    }
    else
    {
        // let's check other modules for this command
        lOutput = gPresence.processDiagnoseCommand(lBuffer);
        if (!lOutput) lOutput = gLogic.processDiagnoseCommand();
    }
    return lOutput;
}

void ProcessDiagnoseCommand(GroupObject &iKo)
{
    // this method is called as soon as iKo is changed
    // an external change is expected
    // because this iKo also is changed within this method,
    // the method is called again. This might result in
    // an endless loop. This is prevented by the isCalled pattern.
    static bool sIsCalledProcessDiagnoseCommand = false;
    if (!sIsCalledProcessDiagnoseCommand)
    {
        sIsCalledProcessDiagnoseCommand = true;
        //diagnose is interactive and reacts on commands
        gLogic.initDiagnose(iKo);
        if (processDiagnoseCommand())
            gLogic.outputDiagnose(iKo);
        sIsCalledProcessDiagnoseCommand = false;
    }
};

void ProcessKoCallback(GroupObject &iKo)
{
    // check if we evaluate own KO
    if (iKo.asap() == LOG_KoDiagnose)
    {
        ProcessDiagnoseCommand(iKo);
    }
    else
    {
        gPresence.processInputKo(iKo);
        // else dispatch to logicmodule
        gLogic.processInputKo(iKo);
    }
}

void appLoop()
{
    if (!knx.configured())
        return;

    // handle KNX stuff
    if (startupDelay())
        return;

    // at this point startup-delay is done
    // we process heartbeat
    ProcessHeartbeat();
    ProcessReadRequests();
    gPresence.loop();
    gLogic.loop();
}

void appSetup(bool iSaveSupported)
{
    // try to get rid of occasional I2C lock...
    savePower();
    ledProg(true);
    ledInfo(true);
    delay(500);
    restorePower();
    // check hardware availability
    boardCheck();
    ledInfo(false);
    ledProg(false);

    if (knx.configured())
    {
        // 5 bit major, 5 bit minor, 6 bit revision
        // knx.bau().deviceObject().version(cFirmwareMajor << 11 | cFirmwareMinor << 6 | cFirmwareRevision);

        if (GroupObject::classCallback() == 0)
            GroupObject::classCallback(ProcessKoCallback);

        gRuntimeData.startupDelay = millis();
        gRuntimeData.heartbeatDelay = 0;
        gPresence.setup();  // presence has to be setup BEFORE logic
        gLogic.setup(iSaveSupported);
    }
}
#endif