#pragma once

#include "CasaLib/preferences.h"

typedef struct preferences_s {
    const char* wifi_ssid;
    const char* wifi_password;

    preferences_s() : wifi_ssid(nullptr), wifi_password(nullptr) {}
} preferences_t;

void saveSettings(preferences_t* prefs);
void setupPreferences();
preferences_t* getPreferences();