#include "server.h"

AsyncWebServer server(API_PORT);

void serviceInfoResponsePayload(char* buffer) {
    sprintf(buffer, "{\"service\":\"device\",\"name\":\"Device\",\"id\":\"%s\",\"sensors\":[]}", DEVICE_ID);
}

void setupRouting() {
    server.on("/", [](AsyncWebServerRequest* request) {
        digitalWrite(LED_PIN, HIGH);
        request->send(200, "application/json", "{}");
        digitalWrite(LED_PIN, LOW);
    });

    server.on("/service", handleServiceInfoRequest);
    server.on("/settings", HTTP_POST, handleSettingsEditRequest);
    server.on("/settings", handleSettingsReadRequest);
    server.on("/journal", handleJournalRequest);

    server.begin();
}