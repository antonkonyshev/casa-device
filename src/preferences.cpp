#include "preferences.h"

wifi_credentials_t* credentials;
preferences_t* preferences;

void addToCredentials(const char* ssid, const char* password) {
    wifi_credentials_t* additional = new wifi_credentials_t;
    additional->ssid = ssid;
    additional->password = password;
    if (credentials) {
    additional->next = credentials;
    } else {
        credentials = additional;
    }
}

wifi_credentials_t* loadWiFiCredentials() {
    if (credentials) {
        return credentials;
    }

    #ifdef DEFAULT_WIFI_SSID_3
    addToCredentials(DEFAULT_WIFI_SSID_3, DEFAULT_WIFI_PASSWORD_3);
    #endif
    #ifdef DEFAULT_WIFI_SSID_2
    addToCredentials(DEFAULT_WIFI_SSID_2, DEFAULT_WIFI_PASSWORD_2);
    #endif
    #ifdef DEFAULT_WIFI_SSID_1
    addToCredentials(DEFAULT_WIFI_SSID_1, DEFAULT_WIFI_PASSWORD_1);
    #endif

    #ifdef ESP32_DEVICE

    nvs_handle_t storage;
    size_t value_size;
    nvs_open(PREFERENCES_STORAGE_NAME, NVS_READWRITE, &storage);

    nvs_get_str(storage, NVS_WIFI_SSID_CREDENTIALS_KEY, NULL, &value_size);
    if (value_size && value_size < 512) {
        char ssid[value_size] = {0};
        nvs_get_str(storage, NVS_WIFI_SSID_CREDENTIALS_KEY, ssid, &value_size);
        nvs_get_str(storage, NVS_WIFI_PASSWORD_CREDENTIALS_KEY, NULL, &value_size);
        if (value_size && value_size < 512) {
            char pwd[value_size] = {0};
            nvs_get_str(storage, NVS_WIFI_PASSWORD_CREDENTIALS_KEY, pwd, &value_size);
            addToCredentials(ssid, pwd);
        } else {
            addToCredentials(ssid, "");
        }
    }

    nvs_close(storage);

    #endif
    #ifdef ESP8266_DEVICE

    if (preferences && preferences->wifi_ssid) {
        addToCredentials(preferences->wifi_ssid, preferences->wifi_password);
    }

    #endif

    return credentials;
}

void cleanWiFiCredentials() {
    while(credentials) {
        wifi_credentials_t* current = credentials;
        credentials = credentials->next;
        delete current;
    }
}

#ifdef ESP32_DEVICE
void saveSettings(preferences_t* prefs) {
    nvs_handle_t storage;
    nvs_open(PREFERENCES_STORAGE_NAME, NVS_READWRITE, &storage);

    if (prefs->wifi_ssid) {
        nvs_set_str(storage, NVS_WIFI_SSID_CREDENTIALS_KEY, prefs->wifi_ssid);
    }

    if (prefs->wifi_password > 0) {
        nvs_set_str(storage, NVS_WIFI_PASSWORD_CREDENTIALS_KEY, prefs->wifi_password);
    }

    nvs_close(storage);
}
#endif

#ifdef ESP8266_DEVICE
void saveSettings(preferences_t* prefs) {
    File storage = LittleFS.open(PREFERENCES_STORAGE_FILE, "wb");
    if (!storage) {
        Serial.println("Cannot open preferences file for writting.");
        return;
    }

    int writtenBytes = storage.write((byte*) &prefs, sizeof(prefs));
    if (writtenBytes == 0) {
        Serial.println("Preferences weren't dumped to a file.");
    }
    storage.close();
}
#endif

#ifdef ESP32_DEVICE
void setupPreferences() {
    preferences = new preferences_t;
    nvs_handle_t storage;
    nvs_open(PREFERENCES_STORAGE_NAME, NVS_READWRITE, &storage);
    // Load preferences
    nvs_close(storage);
}
#endif

#ifdef ESP8266_DEVICE
void setupPreferences() {
    preferences = new preferences_t;
    File storage = LittleFS.open(PREFERENCES_STORAGE_FILE, "rb");
    if (!storage) {
        Serial.println("Preferences file is not available for reading.");
        return;
    }

    int redBytes = storage.read((byte *) &preferences, sizeof(preferences));
    if (redBytes == 0) {
        Serial.println("Preferences weren't loaded from a file.");
    }
    storage.close();
}
#endif

preferences_t* getPreferences() {
    return preferences;
}
