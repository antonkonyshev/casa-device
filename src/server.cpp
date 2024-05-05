#include "server.h"

AsyncWebServer server(API_PORT);

void setupRouting() {
    server.on("/", [](AsyncWebServerRequest* request) {
        digitalWrite(LED_PIN, HIGH);
        request->send(200, "application/json", "{}");
        digitalWrite(LED_PIN, LOW);
    });

    server.on("/service", [](AsyncWebServerRequest* request) {
        digitalWrite(LED_PIN, HIGH);
        request->send(200, "application/json", "{\"service\":\"device\",\"name\":\"Device\",\"id\":\"" + String(DEVICE_ID) + "\",\"sensors\":[]}");
        digitalWrite(LED_PIN, LOW);
    });

    server.on("/settings", HTTP_POST, [](AsyncWebServerRequest* request) {
        digitalWrite(LED_PIN, HIGH);
        preferences_t* preferences = getPreferences();

        size_t params = request->params();
        for (int i = 0; i < params; i++) {
            AsyncWebParameter* param = request->getParam(i);
            if (param->name() == "wifi_ssid") {
                preferences->wifi_ssid = param->value().c_str();
            } else if (param->name() == "wifi_password") {
                preferences->wifi_password = param->value().c_str();
            }
        }

        saveSettings(preferences);
        request->send(200);
        digitalWrite(LED_PIN, LOW);
    });

    server.on("/settings", [](AsyncWebServerRequest* request) {
        digitalWrite(LED_PIN, HIGH);
        preferences_t* preferences = getPreferences();
        char buffer[512] = {0};
        snprintf(buffer, 512, "{}");
        request->send(200, "application/json", buffer);
        digitalWrite(LED_PIN, LOW);
    });

    server.begin();
}