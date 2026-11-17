#include <WiFi.h>
#include <esp_now.h>

// Callback signature for core 3.x
void onDataRecv(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
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
}