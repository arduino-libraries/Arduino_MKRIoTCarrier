#include "Arduino_MKRIoTCarrier.h"
MKRIoTCarrier carrier;

// When CARRIER_CASE is false it's set to 100 (closer)
// When CARRIER_CASE is true it's set to 4  (further)
// But if you use Buttons.updateConfig(value) It will not set the above values

unsigned int threshold = 98;
unsigned int threshold_btn_0 = 95;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial);

  //CARRIER_CASE = false;
  //Now we can set our custom touch threshold
  // First we update all the buttons with the new threshold
  // Then we overwrite individually one of them (they can be all set individually too)
  carrier.Buttons.updateConfig(threshold);
  carrier.Button0.updateConfig(threshold_btn_0);
  carrier.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  carrier.Buttons.update();
  
  // Verify your thresholds
  if (carrier.Button0.getTouch()) {
    Serial.println("touching 0");
  }
  
  if (carrier.Button1.getTouch()) {
    Serial.println("touching 1");
  }
  
  if (carrier.Button2.getTouch()) {
    Serial.println("touching 2");
  }
  
  if (carrier.Button3.getTouch()) {
    Serial.println("touching 3");
  }
  
  if (carrier.Button4.getTouch()) {
    Serial.println("touching 4");
  }
}
