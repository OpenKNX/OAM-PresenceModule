#include "Logic.h"
#include "Presence.h"
#include "SensorDevices.h"
#ifdef ARDUINO_ARCH_RP2040
    #include "FileTransferModule.h"
    #include "UsbExchangeModule.h"
    #include "VirtualButtonModule.h"
    #if defined(KNX_IP_W5500) || defined(KNX_IP_GENERIC) || defined(KNX_IP_WIFI)
        #include "NetworkModule.h"
    #endif
#endif
#include "OpenKNX.h"

#ifdef ARDUINO_ARCH_RP2040
    #pragma message "Pico Core Version: " ARDUINO_PICO_VERSION_STR
#endif
#include "hardware.h"

#include "Sensor.h"

void setup()
{
    const uint8_t firmwareRevision = 0;

#ifdef ARDUINO_ARCH_RP2040
    #ifdef I2C_WIRE
    I2C_WIRE.setSDA(I2C_SDA_PIN);
    I2C_WIRE.setSCL(I2C_SCL_PIN);
    openknxSensorDevicesModule.defaultWire(I2C_WIRE);
    #endif
#endif
    openknx.init(firmwareRevision);
    openknx.addModule(1, openknxLogic);
    openknx.addModule(2, openknxPresenceModule);
    openknx.addModule(4, openknxSensorDevicesModule);
#ifdef ARDUINO_ARCH_RP2040
    openknx.addModule(5, openknxVirtualButtonModule);
    openknx.addModule(3, openknxFileTransferModule);
    openknx.addModule(8, openknxUsbExchangeModule);
    #if defined(KNX_IP_W5500) || defined(KNX_IP_GENERIC) || defined(KNX_IP_WIFI)
    openknx.addModule(7, openknxNetwork);
    #endif
#endif
    openknx.setup();
}

void loop()
{
    openknx.loop();
}
