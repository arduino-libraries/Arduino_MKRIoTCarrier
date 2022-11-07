/**************************************************************************
  This example orignillay from Adafruit ST7735 library, just converted for the carrier usage
 **************************************************************************/

#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;

float p = 3.1415926;

void setup(void) {
  
  Serial.begin(9600);
  Serial.print(F("Hello! ST77xx TFT Test"));
  carrier.noCase();
  carrier.begin();

  uint16_t time = millis();
  carrier.display.fillScreen(ST77XX_BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);

  // large block of text
  carrier.display.fillScreen(ST77XX_BLACK);
  testdrawtext("Lorem ipsum dolor sit amet...", ST77XX_WHITE);
  delay(1000);

  // tft print function!
  tftPrintTest();
  delay(500);

  // a single pixel
  carrier.display.drawPixel(carrier.display.width() / 2, carrier.display.height() / 2, ST77XX_GREEN);
  delay(500);

  // line draw test
  testlines(ST77XX_YELLOW);
  delay(500);

  // optimized lines
  testfastlines(ST77XX_RED, ST77XX_BLUE);
  delay(500);

  testdrawrects(ST77XX_GREEN);
  delay(500);

  carrier.display.fillScreen(ST77XX_BLACK);
  testfillcircles(10, ST77XX_BLUE);
  testdrawcircles(10, ST77XX_WHITE);
  delay(500);

  mediabuttons();
  delay(500);

  Serial.println("done");
  delay(1000);
}

void loop() {
  testtriangles();
  delay(2000);
}

void testlines(uint16_t color) {
  carrier.display.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < carrier.display.width(); x += 6) {
    carrier.display.drawLine(0, 0, x, carrier.display.height() - 1, color);
    delay(0);
  }
  for (int16_t y = 0; y < carrier.display.height(); y += 6) {
    carrier.display.drawLine(0, 0, carrier.display.width() - 1, y, color);
    delay(0);
  }

  carrier.display.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < carrier.display.width(); x += 6) {
    carrier.display.drawLine(carrier.display.width() - 1, 0, x, carrier.display.height() - 1, color);
    delay(0);
  }
  for (int16_t y = 0; y < carrier.display.height(); y += 6) {
    carrier.display.drawLine(carrier.display.width() - 1, 0, 0, y, color);
    delay(0);
  }

  carrier.display.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < carrier.display.width(); x += 6) {
    carrier.display.drawLine(0, carrier.display.height() - 1, x, 0, color);
    delay(0);
  }
  for (int16_t y = 0; y < carrier.display.height(); y += 6) {
    carrier.display.drawLine(0, carrier.display.height() - 1, carrier.display.width() - 1, y, color);
    delay(0);
  }

  carrier.display.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < carrier.display.width(); x += 6) {
    carrier.display.drawLine(carrier.display.width() - 1, carrier.display.height() - 1, x, 0, color);
    delay(0);
  }
  for (int16_t y = 0; y < carrier.display.height(); y += 6) {
    carrier.display.drawLine(carrier.display.width() - 1, carrier.display.height() - 1, 0, y, color);
    delay(0);
  }
}

void testdrawtext(char *text, uint16_t color) {
  carrier.display.setCursor(40, 100);
  carrier.display.setTextColor(color);
  carrier.display.setTextWrap(true);
  carrier.display.print(text);
}

void testfastlines(uint16_t color1, uint16_t color2) {
  carrier.display.fillScreen(ST77XX_BLACK);
  for (int16_t y = 0; y < carrier.display.height(); y += 5) {
    carrier.display.drawFastHLine(0, y, carrier.display.width(), color1);
  }
  for (int16_t x = 0; x < carrier.display.width(); x += 5) {
    carrier.display.drawFastVLine(x, 0, carrier.display.height(), color2);
  }
}

void testdrawrects(uint16_t color) {
  carrier.display.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < carrier.display.width(); x += 6) {
    carrier.display.drawRect(carrier.display.width() / 2 - x / 2, carrier.display.height() / 2 - x / 2 , x, x, color);
  }
}

void testfillcircles(uint8_t radius, uint16_t color) {
  for (int16_t x = radius; x < carrier.display.width(); x += radius * 2) {
    for (int16_t y = radius; y < carrier.display.height(); y += radius * 2) {
      carrier.display.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x = 0; x < carrier.display.width() + radius; x += radius * 2) {
    for (int16_t y = 0; y < carrier.display.height() + radius; y += radius * 2) {
      carrier.display.drawCircle(x, y, radius, color);
    }
  }
}

void testtriangles() {
  carrier.display.fillScreen(ST77XX_BLACK);
  uint16_t color = 0xF800;
  int t;
  int w = 120;
  int x = 200;
  int y = 0;
  int h = 40;
  int z = 200;
  for (t = 0 ; t <= 15; t++) {
    carrier.display.drawTriangle(w, y, h, x, z, x, color);
    x -= 4;
    y += 4;
    z -= 4;
    h += 4;
    color += 100;
  }
}

void tftPrintTest() {
  carrier.display.setTextWrap(false);
  carrier.display.fillScreen(ST77XX_BLACK);
  carrier.display.setCursor(20, 80);
  carrier.display.setTextColor(ST77XX_RED);
  carrier.display.setTextSize(1);
  carrier.display.println("Hello World!");
  carrier.display.setCursor(20, 90);
  carrier.display.setTextColor(ST77XX_YELLOW);
  carrier.display.setTextSize(2);
  carrier.display.println("Hello World!");
  carrier.display.setCursor(20, 110);
  carrier.display.setTextColor(ST77XX_GREEN);
  carrier.display.setTextSize(3);
  carrier.display.println("Hello World!");
  carrier.display.setCursor(20, 140);
  carrier.display.setTextColor(ST77XX_BLUE);
  carrier.display.setTextSize(4);
  carrier.display.print(1234.567);
  delay(1500);
  carrier.display.setCursor(20, 80);
  carrier.display.fillScreen(ST77XX_BLACK);
  carrier.display.setTextColor(ST77XX_WHITE);
  carrier.display.setTextSize(0);
  carrier.display.println("Hello World!");
  carrier.display.setCursor(20, 90);
  carrier.display.setTextSize(1);
  carrier.display.setTextColor(ST77XX_GREEN);
  carrier.display.print(p, 6);
  carrier.display.println(" Want pi?");
  carrier.display.println(" ");
  carrier.display.setCursor(20, 100);
  carrier.display.print(8675309, HEX); // print 8,675,309 out in HEX!
  carrier.display.println(" Print HEX!");
  carrier.display.println(" ");
  carrier.display.setTextColor(ST77XX_WHITE);
  carrier.display.setCursor(20, 110);
  carrier.display.println("Sketch has been");
  carrier.display.setCursor(20, 120);
  carrier.display.println("running for: ");
  carrier.display.setCursor(20, 130);
  carrier.display.setTextColor(ST77XX_MAGENTA);
  carrier.display.print(millis() / 1000);
  carrier.display.setTextColor(ST77XX_WHITE);
  carrier.display.print(" seconds.");
}

void mediabuttons() {
  // play
  carrier.display.fillScreen(ST77XX_BLACK);
  carrier.display.fillRoundRect(75, 60, 78, 60, 8, ST77XX_WHITE);
  carrier.display.fillTriangle(92, 70, 92, 110, 140, 90, ST77XX_RED);
  delay(500);
  // pause
  carrier.display.fillRoundRect(75, 140, 78, 60, 8, ST77XX_WHITE);
  carrier.display.fillRoundRect(89, 148, 20, 45, 5, ST77XX_GREEN);
  carrier.display.fillRoundRect(119, 148, 20, 45, 5, ST77XX_GREEN);
  delay(500);
  // play color
  carrier.display.fillTriangle(92, 70, 92, 110, 140, 90, ST77XX_BLUE);
  delay(50);
  // pause color
  carrier.display.fillRoundRect(89, 148, 20, 45, 5, ST77XX_RED);
  carrier.display.fillRoundRect(119, 148, 20, 45, 5, ST77XX_RED);
  // play color
  carrier.display.fillTriangle(92, 70, 92, 110, 140, 90, ST77XX_GREEN);
}