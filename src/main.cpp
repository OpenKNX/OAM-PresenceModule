#include "Logic.h"
#include "Presence.h"
#include "SensorDevices.h"
#ifdef ARDUINO_ARCH_RP2040
    #include "FileTransferModule.h"
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
    // #ifdef HF_POWER_PIN
    //     pinMode(HF_POWER_PIN, OUTPUT);
    //     // at startup, we turn HF-Sensor off
    //     digitalWrite(HF_POWER_PIN, LOW);
    //     Serial2.setRX(HF_UART_RX_PIN);
    //     Serial2.setTX(HF_UART_TX_PIN);
    //     Wire1.setSDA(I2C_SDA_PIN);
    //     Wire1.setSCL(I2C_SCL_PIN);
    //     Sensor::SetWire(Wire1);
    //     pinMode(PRESENCE_LED_PIN, OUTPUT);
    //     pinMode(MOVE_LED_PIN, OUTPUT);
    //     pinMode(HF_S1_PIN, INPUT);
    //     pinMode(HF_S2_PIN, INPUT);
    // #endif

    openknx.init(firmwareRevision);
    openknx.addModule(1, openknxLogic);
    openknx.addModule(2, openknxPresenceModule);
    openknx.addModule(4, openknxSensorDevicesModule);
#ifdef ARDUINO_ARCH_RP2040
    openknx.addModule(3, openknxFileTransferModule);
#endif
    openknx.setup();
}

void loop()
{
    openknx.loop();
}
