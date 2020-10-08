#include "Arduino_MKRIoTCarrier.h"
MKRIoTCarrier carrier;
bool CARRIER_CASE = false;

// When CARRIER_CASE is false it's set to 100 (closer)
// When CARRIER_CASE is true it's set to 4  (further)
// But if you use Buttons.updateConfig(value) It will not set the above values

unsigned int trheshold = 100;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial);

  //Now we can set our custom touch trheshold
  carrier.Buttons.updateConfig(trheshold);
  carrier.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  carrier.Buttons.update();
  //Lets test 1 button, they should all react in the same way
  if (carrier.Button1.getTouch()) {
    Serial.println("touching");
  }
}
