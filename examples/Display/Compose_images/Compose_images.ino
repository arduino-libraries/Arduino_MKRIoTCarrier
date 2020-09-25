/**************************************************************************
  This example orignillay from Adafruit ST7735 library, just converted for the carrier usage
 **************************************************************************/
#include "Images.h"
#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;

bool CARRIER_CASE = false;

uint32_t orange = carrier.leds.Color(50, 242, 0);

void setup() {

  Serial.begin(9600);
  carrier.begin();

  uint16_t time = millis();
  carrier.display.fillScreen(ST77XX_BLACK);
  time = millis() - time;

  carrier.leds.fill(orange, 0, 5);
  carrier.leds.setBrightness(15);
  carrier.leds.show();
}

int i = 0;
int ledC = 0;
int ledA = 0;
int count = 0;

void loop() {
  carrier.display.fillScreen(ST77XX_BLACK);
  drawArduino(0x04B3);
  fadeLoop();
  carrier.display.fillScreen(ST77XX_BLACK);
  drawEIoT();
  fadeLoop();
  
  carrier.display.fillScreen(ST77XX_WHITE);
  drawArduino(0x0000);
  fadeLoop();
  //carrier.display.fillScreen(ST77XX_WHITE);
  drawArduino(0xF324);
  fadeLoop();
  drawArduino(0x04B3);
  fadeLoop();

  carrier.display.fillScreen(ST77XX_WHITE);
  drawEIoT();
  fadeLoop();

  


}
void fadeLoop() {
  carrier.leds.fill(orange, ledA, ledC);
  for ( i = 0; i < 125; i++) {
    carrier.leds.setBrightness(i);
    carrier.leds.show();
    delay(10);
  }

  for ( i = 125; i > -1; i--) {
    carrier.leds.setBrightness(i);
    carrier.leds.show();
    delay(10);
  }
  carrier.leds.clear();
  delay(500);

}

void drawEIoT() {
  carrier.display.drawBitmap(44, 25, ArduinoLogo, 152, 72, 0x04B3);
  carrier.display.drawBitmap(48, 110, ArduinoText, 144, 23, 0x04B3);
  carrier.display.drawBitmap(0, 150, ExploreFrame, 240, 75, 0xF324);
  carrier.display.drawBitmap(0, 150, ExplreIoTKittext, 240, 75, 0x04B3);
  carrier.display.drawBitmap(0, 150, ExploreIoTtext, 240, 75, 0xFFFF);
}

void drawArduino(uint16_t color) {
  carrier.display.drawBitmap(44, 60, ArduinoLogo, 152, 72, color);
  carrier.display.drawBitmap(48, 145, ArduinoText, 144, 23, color);
}
