#define CONFIG_ESP_INT_WDT_TIMEOUT_MS 5000    // milliseconds

#include <Arduino.h>
#include <time.h>
#ifdef ESP32_DEVICE
#include <Esp.h>
#endif

#include "pinout.h"
#include "network.h"
#include "server.h"
