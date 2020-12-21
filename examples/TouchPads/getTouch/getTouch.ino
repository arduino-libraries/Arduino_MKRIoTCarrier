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
  CARRIER_CASE = false;
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
  if (carrier.Button0.getTouch()) {
    Serial.println("Touching Button 1");
  }
  if (carrier.Button1.getTouch()) {
    Serial.println("Touching Button 2");
  }
  if (carrier.Button2.getTouch()) {
    Serial.println("Touching Button 3");
  }
  if (carrier.Button3.getTouch()) {
    Serial.println("Touching Button 4");
  }
  if (carrier.Button4.getTouch()) {
    Serial.println("Touching Button 5");
  }

}
