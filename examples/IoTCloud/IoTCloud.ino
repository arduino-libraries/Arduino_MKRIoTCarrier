#include "arduino_secrets.h"
#include "thingProperties.h" 
#include "Arduino_MKRIoTCarrier.h"


MKRIoTCarrier carrier;

void setup(){
    Serial.begin(9600);

    // Defined in thingProperties.h
    initProperties();

    // Connect to Arduino IoT Cloud
    ArduinoCloud.begin(ArduinoIoTPreferredConnection);

    //Get Cloud Info/errors , 0 (only errors) up to 4
    setDebugMessageLevel(2);
    ArduinoCloud.printDebugInfo();

    carrier.begin();
}

void loop(){
    ArduinoCloud.update();
}