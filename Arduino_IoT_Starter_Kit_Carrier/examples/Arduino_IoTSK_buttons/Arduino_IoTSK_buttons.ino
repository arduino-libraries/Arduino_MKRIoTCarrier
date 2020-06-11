#include <Arduino_IOTSKcarrier.h>
IOTSKcarrier carrier; //Constructor of the carrier maybe we can include it on the library itself

/*  --- Qtouch Sketch test v0.1 ---
 *  This sketch Shows up the easiest way to control the buttons
 *  Keep in mind that this can change in the future, use it to brainstorm
 *  
 *  Good Luck!
 *  
 *  
 *  Functions:
 *    getTouch() - Return true if the button is being touched
 *    
 */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial);
  carrier.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (carrier.Button1.getTouch()) {
    Serial.println("Button 1 got touch");
  }
  if (carrier.Button2.getTouch()) {
    Serial.println("Button 2 got touch");
  }
  if (carrier.Button3.getTouch()) {
    Serial.println("Button 3 got touch");
  }
  if (carrier.Button4.getTouch()) {
    Serial.println("Button 4 got touch");
  }
  if (carrier.Button5.getTouch()) {
    Serial.println("Button 5 got touch");
  }
}
