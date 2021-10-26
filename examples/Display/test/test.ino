#include "Arduino_MKRIoTCarrier.h"

MKRIoTCarrier  carrier;

void setup(){
    Serial.begin(9600);
    while(!Serial);
    carrier.begin();

    carrier.display.test();
    

}
void loop(){}