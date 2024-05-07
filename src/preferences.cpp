#include "preferences.h"

preferences_t* preferences;

void saveSettings(preferences_t* prefs) {
    #ifdef ESP32_DEVICE

    openPreferencesStorage();
    if (prefs->wifi_ssid) {
        savePreference(NVS_WIFI_SSID_CREDENTIALS_KEY, prefs->wifi_ssid);
        savePreference(NVS_WIFI_PASSWORD_CREDENTIALS_KEY, prefs->wifi_password);
    }
    savePreference(NVS_JOURNAL_LENGTH_KEY, prefs->journal_length);
    closePreferencesStorage();

    #endif
    #ifdef ESP8266_DEVICE

    if (prefs->wifi_ssid) {
        saveWifiCredentials(prefs->wifi_ssid, prefs->wifi_password);
    }
    savePreference(prefs);

    #endif
}

void saveSettings(AsyncWebServerRequest* request) {
    size_t params = request->params();
    for (size_t idx = 0; idx < params; idx++) {
        AsyncWebParameter* param = request->getParam(idx);

        if (param->name() == NVS_JOURNAL_LENGTH_KEY) {
            preferences->journal_length = param->value().toInt();
        } else if (param->name() == NVS_WIFI_SSID_CREDENTIALS_KEY) {
            preferences->wifi_ssid = param->value().c_str();
        } else if (param->name() == NVS_WIFI_PASSWORD_CREDENTIALS_KEY) {
            preferences->wifi_password = param->value().c_str();
        }
    }
    saveSettings(preferences);
}

void setupPreferences() {
    preferences = new preferences_t;
    #ifdef ESP32_DEVICE

    openPreferencesStorage();
    loadPreference(NVS_JOURNAL_LENGTH_KEY, &preferences->journal_length, NVS_JOURNAL_LENGTH_DEFAULT);
    closePreferencesStorage();

    #endif
    #ifdef ESP8266_DEVICE

    if (!loadPreference(preferences)) {
        preferences->journal_length = NVS_JOURNAL_LENGTH_DEFAULT;
    }

    #endif
}

void serializeSettings(char* buffer) {
    sprintf(buffer, "{\"journal_length\":%d}", preferences->journal_length);
}

preferences_t* getPreferences() {
    return preferences;
}
