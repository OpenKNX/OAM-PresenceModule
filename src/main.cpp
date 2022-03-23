#include <OpenKNX.h>
#include "PMmodul.h"
#include "HardwareDevices.h"

void appSetup(bool iSaveSupported);
void appLoop();

void setup()
{
#ifdef ARDUINO_ARCH_RP2040
    Serial1.setRX(KNX_UART_RX_PIN);
    Serial1.setTX(KNX_UART_TX_PIN);
    Serial2.setRX(HF_UART_RX_PIN);
    Serial2.setTX(HF_UART_TX_PIN);
#endif
    SERIAL_DEBUG.begin(115200);
    pinMode(PROG_LED_PIN, OUTPUT);
    digitalWrite(PROG_LED_PIN, HIGH);
    delay(DEBUG_DELAY);
    digitalWrite(PROG_LED_PIN, LOW);
    pinMode(PRESENCE_LED_PIN, OUTPUT);
    pinMode(MOVE_LED_PIN, OUTPUT);
    SERIAL_DEBUG.println("Startup called...");
    ArduinoPlatform::SerialDebug = &SERIAL_DEBUG;

#ifdef INFO_LED_PIN
  pinMode(INFO_LED_PIN, OUTPUT);
  ledInfo(true);
#endif

  // moved to checkBoard!!!
  // Wire.begin();
  // initialize knx-stack and check versions
  OpenKNX::knxRead(MAIN_OpenKnxId, MAIN_ApplicationNumber, MAIN_ApplicationVersion, 0);

  // pin or GPIO the programming led is connected to. Default is LED_BUILDIN
  knx.ledPin(PROG_LED_PIN);
  // is the led active on HIGH or low? Default is LOW
  knx.ledPinActiveOn(PROG_LED_PIN_ACTIVE_ON);
  // pin or GPIO programming button is connected to. Default is 0
  knx.buttonPin(PROG_BUTTON_PIN);
  // Is the interrup created in RISING or FALLING signal? Default is RISING
  knx.buttonPinInterruptOn(PROG_BUTTON_PIN_INTERRUPT_ON);

  appSetup(SAVE_INTERRUPT_PIN);

  // start the framework.
  knx.start();
  ledInfo(false);
}

void loop()
{
  // don't delay here to much. Otherwise you might lose packages or mess up the timing with ETS
  knx.loop();

  // only run the application code if the device was configured with ETS
  if (knx.configured())
    appLoop();
}