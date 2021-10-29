/**
   ESP-NOW

   Sender
*/
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
int pin = 5;
unsigned long duration;
// Mac address of the slave
uint8_t peer1[] = {0x3C, 0x61, 0x05, 0x10, 0x96, 0x1C};
typedef struct message {
  int id;
  int distance;
  int distance_tx;
};
struct message myMessage;
void onSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.println("Status:");
  Serial.println(sendStatus);
}
void setup() {
  Serial.begin(115200);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pin, INPUT);
  delay(500);
  WiFi.mode(WIFI_STA);
  // Get Mac Add
  Serial.print("Mac Address: ");
  Serial.print(WiFi.macAddress());
  Serial.println("ESP-Now Sender");
  // Initializing the ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Problem during ESP-NOW init");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  // Register the peer
  Serial.println("Registering a peer");
  esp_now_add_peer(peer1, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
  Serial.println("Registering send callback function");
  esp_now_register_send_cb(onSent);
}
void loop() {
  //digitalWrite(LED_BUILTIN, HIGH);   // turn the LED
  // Set values to send
  uint16_t distance = 0;
  duration = pulseIn(pin, HIGH);
  distance = duration/10;
  //Serial.println(distance);
  //int distance2 = constrain(distance, 30, 2880);
  int distance_tx = map(distance, 30, 4880, 0, 255);
  myMessage.id = 3;  //Change the id number for each device
  myMessage.distance = distance;
  Serial.println(distance);
  
  Serial.println("Send a new message");
  esp_now_send(NULL, (uint8_t *) &myMessage, sizeof(myMessage));
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
}
