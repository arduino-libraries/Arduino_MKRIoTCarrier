/*
  BME688 - CO2
*/

#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  carrier.noCase();
  carrier.begin();
}

void loop() {
  // read all the sensor values
  float co2 = carrier.AirQuality.readCO2();

  // print each of the sensor values
  Serial.print("CO2 Value = ");
  Serial.println(co2);

  // wait 1 second to print again
  delay(1000);
}
