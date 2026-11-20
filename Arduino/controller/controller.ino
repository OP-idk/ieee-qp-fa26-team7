#include <WiFi.h>
#include <esp_now.h>

uint8_t peerMac[] = {0x90, 0x70, 0x69, 0xE0, 0x2A, 0x48};
// Dark board MAC: 10:20:BA:0D:FB:88
// Light board MAC: 90:70:69:E0:2A:48
const uint8_t on[] = {4};
const uint8_t off[] = {5};
const uint8_t hold[] = {6};
bool sendStat = false;

void setup() {
    Serial.begin(115200);
    pinMode(13, INPUT);
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    
    delay(100);

    WiFi.mode(WIFI_STA);
    esp_now_init();
    esp_now_peer_info_t peer = {};
    memcpy(peer.peer_addr, peerMac, 6);
    peer.channel = 0;
    peer.encrypt = false;
    esp_now_add_peer(&peer);
}

void loop() {
    int y = analogRead(4);
    int x = analogRead(5);
    Serial.printf("x: %d\t\ty: %d\n", x, y);

    int pinStat = digitalRead(13);

    if (pinStat == HIGH) {
        Serial.println("hi");
        if (sendStat) {
          Serial.println("on");
          esp_now_send(peerMac, on, 1);
        } else {
          Serial.println("off");
           esp_now_send(peerMac, off, 1);
        }
        sendStat = !sendStat;
    } else {
        esp_now_send(peerMac, hold, 1);
    }
    delay(250);
    //const char *msg = ":3";

    //esp_now_send(peerMac, (uint8_t *)msg, strlen(msg));
    

}

void printMacToSerial() {
    //Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    delay(500);
    Serial.print("MAC address: ");
    Serial.println(WiFi.macAddress());
}
