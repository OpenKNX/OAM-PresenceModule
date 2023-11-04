#include "Logic.h"
#include "Presence.h"
#ifdef ARDUINO_ARCH_RP2040
    #include "FileTransferModule.h"
#endif
#include "OpenKNX.h"

#ifdef ARDUINO_ARCH_RP2040
    #pragma message "Pico Core Version: " ARDUINO_PICO_VERSION_STR
#endif
#include "hardware.h"

#include "Sensor.h"

uint8_t mSerial2Active = false;

void setup()
{
    const uint8_t firmwareRevision = 1;

#ifdef HF_POWER_PIN
    pinMode(HF_POWER_PIN, OUTPUT);
    // at startup, we turn HF-Sensor off
    digitalWrite(HF_POWER_PIN, LOW);
    Serial2.setRX(HF_UART_RX_PIN);
    Serial2.setTX(HF_UART_TX_PIN);
    Wire1.setSDA(I2C_SDA_PIN);
    Wire1.setSCL(I2C_SCL_PIN);
    Sensor::SetWire(Wire1);
    pinMode(PRESENCE_LED_PIN, OUTPUT);
    pinMode(MOVE_LED_PIN, OUTPUT);
    pinMode(HF_S1_PIN, INPUT);
    pinMode(HF_S2_PIN, INPUT);
#endif

    openknx.init(firmwareRevision);
    openknx.addModule(1, new Logic());
    openknx.addModule(2, new Presence());
#ifdef ARDUINO_ARCH_RP2040
    openknx.addModule(3, new FileTransferModule());
#endif
    openknx.setup();
}

void loop()
{

#ifdef HF_POWER_PIN
    // only run the application code if the device was configured with ETS
    if (knx.configured())
    {
        if (!mSerial2Active)
        {
            // we start HF communication as late as possible
            mSerial2Active = true;
            Serial2.begin(9600);
        }
    }
    else
    {
        if (mSerial2Active)
        {
            // during ETS programming, we stop HF communication
            mSerial2Active = false;
            Serial2.end();
        }
    }
#endif
    openknx.loop();
}
