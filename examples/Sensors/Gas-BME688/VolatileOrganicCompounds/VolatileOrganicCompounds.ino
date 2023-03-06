/*
  BME688 - Volatile Organic Compounds (VOC)
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
  float gasResistor = carrier.AirQuality.readGasResistor();
  float volatileOrganicCompounds = carrier.AirQuality.readVOC();

  // print each of the sensor values
  Serial.print("Gas Resistor Value = ");
  Serial.println(gasResistor);

  Serial.print("Volatile Organic Compounds (VOC) = ");
  Serial.print(volatileOrganicCompounds);
  Serial.println(" ppm");

  // wait 1 second to print again
  delay(1000);
}
