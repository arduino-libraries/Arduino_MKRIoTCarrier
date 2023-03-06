/*
  BME688 - Air Quality Index (IAQ)
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
  float airQualityStatic = carrier.AirQuality.readStaticIAQ();
  float airQualityAccuracy = carrier.AirQuality.readIAQAccuracy();
  float airQualityIndex = carrier.AirQuality.readIAQ();

  // print each of the sensor values
  Serial.print("Static Air Quality Index Value = ");
  Serial.println(airQualityStatic);

  Serial.print("Air Quality Accuracy = ");
  Serial.println(airQualityAccuracy);

  Serial.print("Air Quality Index = ");
  Serial.println(airQualityIndex);

  // wait 1 second to print again
  delay(1000);
}
