#include <Arduino.h>
#include "WiFi.h"
#include "WiFiUdp.h"

// WiFi credentials.
const char* WIFI_SSID = "JuanNET";
const char* WIFI_PASS = "strandbeast";

unsigned int local_port = 2390;

char packetBuffer[255];
char ReplyBuffer[] = "ACK";

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

    Udp.begin(local_port);
}

void loop() {

    // if there's data available, read a packet
    int packetSize = Udp.parsePacket();
    if (packetSize) {
        Serial.print("Received packet of size ");
        Serial.println(packetSize);
        Serial.print("From ");
        IPAddress remoteIp = Udp.remoteIP();
        Serial.print(remoteIp);
        Serial.print(", port ");
        Serial.println(Udp.remotePort());

        // read the packet into packetBufffer
        int len = Udp.read(packetBuffer, 255);
        if (len > 0) {
            packetBuffer[len] = 0;
        }
    
        Serial.println("Contents:");
        Serial.println(packetBuffer);

        // send a reply, to the IP address and port that sent us the packet we received
        Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
        Udp.write(0x01);
        Udp.endPacket();
  }
}