#include "main.h"

void setup() {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);

    setupSerial();
    printHardwareInfo();

    #ifdef ESP32_DEVICE
    btStop();
    #endif

    setupPreferences();
    setupWifi();
    setupRouting();

    printMemoryInfo();

    digitalWrite(LED_PIN, LOW);
}

void loop() {
}