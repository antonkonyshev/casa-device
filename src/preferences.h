#pragma once

#include <ESPAsyncWebServer.h>

#include "CasaLib/preferences.h"

#define NVS_JOURNAL_LENGTH_KEY "journal_length"
#define NVS_JOURNAL_LENGTH_DEFAULT 10

typedef struct preferences_s: base_preferences_t {
} preferences_t;

void saveSettings(preferences_t* prefs);
void saveSettings(AsyncWebServerRequest* request);
void setupPreferences();
void serializedSettings(char* buffer);
preferences_t* getPreferences();