#include <Arduino.h>
#include "WiFi.h"

// WiFi credentials.
const char* WIFI_SSID = "AAU-1-DAY";
const char* WIFI_PASS = "";

void setup() {
    Serial.begin(115200);
    delay(2000);

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.println("Connecting...");

    while (WiFi.status() != WL_CONNECTED) {
        // Check to see if connecting failed.
        // This is due to incorrect credentials
        if (WiFi.status() == WL_CONNECT_FAILED) {
            Serial.println("Failed to connect to WIFI. Please verify credentials: ");
            Serial.println();
            Serial.print("SSID: ");
            Serial.println(WIFI_SSID);
            Serial.print("Password: ");
            Serial.println(WIFI_PASS);
            Serial.println();
        }

        delay(5000);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    Serial.println("Hello World, I'm connected to the internets!!");
}

void loop() {
    delay(2000);
    Serial.println("JUAN!");
}