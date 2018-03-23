#include <Arduino.h>
#include "WiFi.h"
#include "WiFiUdp.h"

// WiFi credentials
const char* WIFI_SSID = "JuanNET";
const char* WIFI_PASS = "strandbeast";

unsigned int local_port = 2390;

char recv_buffer[255];
int packet_size = 0;

WiFiUDP Udp;

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
            Serial.println("Failed to connect to WIFI... Check credentials.");
        }

        delay(5000);
    }

    Serial.println("WiFi connected");
    Serial.println("Obtained IP address: ");
    Serial.println(WiFi.localIP());

    Serial.println("LOOK MA', I AM ON ZE INTERNETZ!");

    // Start UDP
    Udp.begin(local_port);
}

void loop() {

    // if there's data available, read a packet
    packet_size = Udp.parsePacket();
    if (packet_size) {
        
        Serial.print("CMD: ");
        Serial.print(Udp.remoteIP());
        Serial.print(":");
        Serial.print(Udp.remotePort());
        Serial.print(", SIZE: ");
        Serial.println(packet_size);

        // read the packet into packetBufffer
        int len = Udp.read(recv_buffer, 255);
        if (len > 0) {
            recv_buffer[len] = 0;
        }
        
        if (!strcmp(recv_buffer, "F")) {
            Serial.println("GO FORWARDS");
        } else if (!strcmp(recv_buffer, "B")) {
            Serial.println("GO BACKWARDS");
        } else if (!strcmp(recv_buffer, "R")) {
            Serial.println("GO RIGHT");
        } else if (!strcmp(recv_buffer, "L")) {
            Serial.println("GO LEFT");
        }

        // ACK
        Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
        Udp.write(0x01);
        Udp.endPacket();
    }
}