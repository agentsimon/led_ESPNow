/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-many-to-one-esp32/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

#include <esp_now.h>
#include <WiFi.h>
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN 33
#define N_LEDS 142

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);


// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
  int id;
  int x;
} struct_message;
int dataRed = 0;
int dataGreen = 0;
int dataBlue = 0;
// Create a struct_message called myData
struct_message myData;

// Create a structure to hold the readings from each board
struct_message board1;
struct_message board2;
struct_message board3;

// Create an array with all the structures
struct_message boardsStruct[3] = {board1, board2, board3};

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
  char macStr[18];
  memcpy(&myData, incomingData, sizeof(myData));
  boardsStruct[myData.id - 1].x = myData.x;
}

void setup() {
  //Initialize Serial Monitor
  Serial.begin(115200);
  strip.begin();
  //Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  //Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t ) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    //strip.show();
  }
}

void loop() {
  int dataRed = boardsStruct[0].x;
  int dataGreen = boardsStruct[1].x ;
  int dataBlue = boardsStruct[2].x;
  int  dataRed2 = map(dataRed, 0, 4481, 0, 255);
  int  dataGreen2 = map(dataGreen, 0, 4481, 0, 255);
  int  dataBlue2 = map(dataBlue, 0, 4481, 0, 255);
  Serial.println( (String)"Id 1 value Red = " + dataRed2 + (String)"  Id 2 Value Green = " + dataGreen2 + (String)"  Id 3 Value Blue = " + dataBlue2);
  // Write the colors to the strip
  colorWipe(strip.Color(dataRed2, dataGreen2, dataBlue2), 50);
  strip.show();
  //Wait
  delay(250);
}
