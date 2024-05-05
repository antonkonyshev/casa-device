#pragma once

#ifdef ESP32_DEVICE

#include <nvs_flash.h>

#define PREFERENCES_STORAGE_NAME "storage"
#define NVS_WIFI_SSID_CREDENTIALS_KEY "wifi_ssid"
#define NVS_WIFI_PASSWORD_CREDENTIALS_KEY "wifi_password"

#endif
#ifdef ESP8266_DEVICE

#include <LittleFS.h>

#define PREFERENCES_STORAGE_FILE "preferences.bin"

#endif

typedef struct wifi_credentials_s {
    const char* ssid;
    const char* password;
    wifi_credentials_s* next;

    wifi_credentials_s() : ssid(nullptr), password(nullptr), next(nullptr) {}
} wifi_credentials_t;

typedef struct preferences_s {
    const char* wifi_ssid;
    const char* wifi_password;

    preferences_s() : wifi_ssid(nullptr), wifi_password(nullptr) {}
} preferences_t;

wifi_credentials_t* loadWiFiCredentials();
void cleanWiFiCredentials();
void saveSettings(preferences_t* prefs);
void setupPreferences();
preferences_t* getPreferences();