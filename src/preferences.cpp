#include "preferences.h"

preferences_t* preferences;

void saveSettings(preferences_t* prefs) {
    #ifdef ESP32_DEVICE

    openPreferencesStorage();
    if (prefs->wifi_ssid) {
        savePreference(NVS_WIFI_SSID_CREDENTIALS_KEY, prefs->wifi_ssid);
        savePreference(NVS_WIFI_PASSWORD_CREDENTIALS_KEY, prefs->wifi_password);
    }
    // Save other preferences
    closePreferencesStorage();

    #endif
    #ifdef ESP8266_DEVICE

    if (prefs->wifi_ssid) {
        saveWifiCredentials(prefs->wifi_ssid, prefs->wifi_password);
    }
    savePreference(prefs);

    #endif
}

void setupPreferences() {
    preferences = new preferences_t;
    #ifdef ESP32_DEVICE

    openPreferencesStorage();
    // Load preferences
    closePreferencesStorage();

    #endif
    #ifdef ESP8266_DEVICE

    loadPreference(preferences);

    #endif
}

preferences_t* getPreferences() {
    return preferences;
}
