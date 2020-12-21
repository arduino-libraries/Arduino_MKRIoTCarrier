#include "Arduino_MKRIoTCarrier.h"
MKRIoTCarrier carrier;

// When CARRIER_CASE is false it's set to 100 (closer)
// When CARRIER_CASE is true it's set to 4  (further)
// But if you use Buttons.updateConfig(value) It will not set the above values

unsigned int threshold = 100;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial);

  //CARRIER_CASE = false;
  //Now we can set our custom touch threshold
  carrier.Buttons.updateConfig(threshold);
  carrier.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  carrier.Buttons.update();
  //Lets test 1 button, they should all react in the same way
  if (carrier.Button0.getTouch()) {
    Serial.println("touching");
  }
}
