/*
  Arduino IoT Cloud Variables description
  The following variables are automatically generated and updated when changes are made to the Thing
  float test;
  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"
#include <Scheduler.h>
#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;

unsigned int WiFiTries = 0;
unsigned int CloudTries = 0;
//void connectionSuccessful();

int oldValue = 0;

void setup()
{
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial)
    ;
  carrier.begin();
  //carrier.display.init(240, 240);
  //carrier.leds.begin();
  carrier.display.fillScreen(ST77XX_BLACK);
  carrier.display.setRotation(0);
  carrier.leds.fill(uint32_t(random(0, 0xFFFFFF)), 0, 5);
  carrier.leds.setBrightness(100);
  carrier.leds.show();
  Serial.println("starting");
  delay(2000);
  Scheduler.startLoop(loop2);
  delay(1500);

  carrier.display.setTextSize(2);

  carrier.display.setCursor(0,60);
  carrier.display.setTextColor(ST77XX_WHITE);
  carrier.display.print("WiFi");
  printWiFiStatus("Trying", ST77XX_ORANGE);

  carrier.display.setCursor(0, 100);
  carrier.display.setTextColor(ST77XX_WHITE);
  carrier.display.print("Cloud");
  printCloudStatus("Not connected", ST77XX_RED);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  ArduinoCloud.addCallback(ArduinoIoTCloudEvent::CONNECT, CloudOnConnect);
  ArduinoCloud.addCallback(ArduinoIoTCloudEvent::SYNC, CloudOnSync);
  ArduinoCloud.addCallback(ArduinoIoTCloudEvent::DISCONNECT, CloudOnDisconnect);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
  */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  while (ArduinoCloud.connected() != 1)
  {

    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("WiFi OK, trying Cloud");

      printWiFiStatus("Connected", ST77XX_GREEN);

      printCloudStatus("Trying", ST77XX_ORANGE);

      CloudTries++;
      if (CloudTries > 5)
      {
        printCloudStatus("Taking too long", ST77XX_RED);
        if (CloudTries > 10)
        {
          printCloudStatus("Check your sketch and/or the Thing ID", ST77XX_RED);
        }
      }
    }
    else
    {
      Serial.println("Trying to connect to the WiFi");
      WiFiTries++;
      if (WiFiTries > 5)
      {
        printWiFiStatus("Taking too long", ST77XX_RED);
        if (WiFiTries > 10)
        {
          printWiFiStatus("Check SSID and Password, stopping", ST77XX_RED);
          carrier.leds.setPixelColor(2, 0xFF00);
          while (1)
            ;
        }
      }
    }
    Serial.println("Update started");
    ArduinoCloud.update();
    Serial.println("Update done");
    delay(500);
  }

  delay(1500);
  //carrier.begin();
  delay(1500);
  // connectionSuccessful();
}

void loop()
{
  ArduinoCloud.update();
  Serial.print("Cloud number: ");
  Serial.println(test);
  // Your code here
  carrier.Buttons.update();
  if (carrier.Buttons.onTouchDown(TOUCH2))
    test++;

  if (WiFi.status() == WL_CONNECTED)
  {
    carrier.leds.setPixelColor(2, 0xFF0000);
  }
  else
  {
    carrier.leds.setPixelColor(2, 0xFF00);
  }
  carrier.leds.show();

  if (test != oldValue)
  {
    oldValue = test;
    carrier.display.setCursor(80, 150);
    carrier.display.setTextColor(0xFFFFFF);
    carrier.display.fillRect(80, 145, 100, 100, 0x0);
    carrier.display.print(test);
  }
  delay(100);
}

void CloudOnConnect()
{
  Serial.println("Board successfully connected to Arduino IoT Cloud");
  Serial.println("FInish cloud.connected");
  printCloudStatus("Connected", ST77XX_GREEN);
}

void printCloudStatus(String message, uint16_t color)
{
  carrier.display.fillRect(65, 95, 180, 40, 0x0);
  carrier.display.setCursor(65, 100);
  carrier.display.setTextColor(color);
  carrier.display.print(message);
  //carrier.leds.setPixelColor(2, 0xFF0000);
  //carrier.leds.show();
}
void printWiFiStatus(String message, uint16_t color)
{
  carrier.display.fillRect(60, 55, 180, 40, 0x0);
  carrier.display.setCursor(60, 60);
  carrier.display.setTextColor(color);
  carrier.display.print(message);
}

void CloudOnDisconnect()
{
  Serial.println("Board disconnected from Arduino IoT Cloud");
  printCloudStatus("Disconnected, trying to connet again", ST77XX_ORANGE);
  carrier.leds.setPixelColor(2, 0xFF);
  carrier.leds.show();
}

void CloudOnSync()
{
  Serial.println("Thing Properties synchronised");
}

//Thing variables callbacks
void onTestChange()
{
  // Do something
}

void loop2()
{
  int brightness = 0;

  // ALL FADE
  // FADE IN
  // INDIVIDUAL FADE

  for (int brightness = 0; brightness < 101; brightness++)
  {
    carrier.leds.setBrightness(brightness);
    carrier.leds.show();
    Serial.println(brightness);
    delay(1);
  }

  // INDIVIDUAL FADE

  // FADE OUT
  for (int brightness = 100; brightness > -1; brightness--)
  {
    carrier.leds.setBrightness(brightness);
    carrier.leds.show();
    Serial.println(brightness);
    delay(1);
  }
  
}