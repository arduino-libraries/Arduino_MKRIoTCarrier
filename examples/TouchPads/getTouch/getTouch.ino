/*
  Arduino_Qtouch - Sensor data read Example
  This example shows how to configure and read data
  from touch sensors bottons on MKR IoT Carrier and
  prints updates to the Serial Monitor.

  The circuit:
  - Arduino MKR baord;
  - MKR IoT carrier.

  This example code is in the public domain.
*/
#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;


void setup() {
  Serial.begin(9600);
  while (!Serial);
  // Qtouch initialization
  if (!carrier.begin()) {
    Serial.println("Error in sensors initialization!");
    while (1);
  }
  Serial.println("Touch initialization Done!");
}

void loop() {
  // polling the sensor for new measure
  carrier.Buttons.update();

  // Checks if new data are available
  if (carrier.Buttons.getTouch(TOUCH0)) {
    Serial.println("Touching Button 0");
  }
  if (carrier.Buttons.getTouch(TOUCH1)) {
    Serial.println("Touching Button 1");
  }
  if (carrier.Buttons.getTouch(TOUCH2)) {
    Serial.println("Touching Button 2");
  }
  if (carrier.Buttons.getTouch(TOUCH3)) {
    Serial.println("Touching Button 3");
  }
  if (carrier.Buttons.getTouch(TOUCH4)) {
    Serial.println("Touching Button 4");
  }

}
