#include <WiFi.h>
#include <esp_now.h>

int noConnectionTimer = 0;
bool disconnectWarningStatus = 0;

// Callback signature for core 3.x
void onDataRecv(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
    noConnectionTimer = 0;
    uint8_t command;
    for (int i = 0; i < len; i++) {
        command = data[i];
    }

    if (command == 4){
        digitalWrite(17, HIGH);
    }
    else if (command == 5){
        digitalWrite(17, LOW);
    }
}

void setup() {
    Serial.begin(115200);

    WiFi.mode(WIFI_STA);
    pinMode(17, OUTPUT);
    pinMode(18, OUTPUT);

    delay(1000);

    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP-NOW init failed");
        return;
    }
    esp_now_register_recv_cb(onDataRecv);
    Serial.println("Receiver ready");
}

void loop() {
    // Nothing needed, the callback handles incoming packets
    delay(1);
    noConnectionTimer += 1;
    if (noConnectionTimer > 500) {
        noConnectionTimer = 500;
        if (disconnectWarningStatus) {
            digitalWrite(18, HIGH);
            delay(99);
            disconnectWarningStatus = false;
        } else {
            digitalWrite(18, LOW);
            disconnectWarningStatus = true;
        }
    } else {
        digitalWrite(18, LOW);
        disconnectWarningStatus = false;
    }
}