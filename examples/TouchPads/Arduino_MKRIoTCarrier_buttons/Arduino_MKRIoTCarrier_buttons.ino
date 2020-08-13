#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier; //Constructor of the carrier maybe we can include it on the library itself

//Auto configure the sense distance for the touch pads
bool CARRIER_CASE = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial);

  //Init all the components from the board
  carrier.begin(); 
}

void loop() {
  // put your main code here, to run repeatedly:

  //Each time you want to update the reads from the pads use this
  //It will update all the pads at the same time
  carrier.Buttons.update();

  //Different types of touches
  //When you first touch it
  if (carrier.Button1.onTouchDown()) {
    Serial.println("Button 1 : TOUCH DOWN");
  }

  //When you release it
  if (carrier.Button2.onTouchUp()) {
    Serial.println("Button 2 : TOUCH UP");
  }

  //When it detects a change, down or up
  if (carrier.Button3.onTouchChange()) {
    Serial.println("Button 3 : TOUCH CHANGE");
  }

  //Normal, if it is being pressed
  if (carrier.Button4.getTouch()) {
    Serial.println("Button 4 : GETTING TOUCH");
  }
  if (carrier.Button5.getTouch()) {
    Serial.println("Button 5 : GETTING TOUCH");
  }
  
  //Serial.println();
  delay(20);
  
}