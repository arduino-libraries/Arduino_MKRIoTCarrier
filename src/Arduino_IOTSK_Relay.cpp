#include "Arduino_IOTSK_Relay.h"

IOTSKcarrier_Relay::IOTSKcarrier_Relay(int pin){
    _pin = pin;
    pinMode(_pin ,OUTPUT);
    open();
    
}

//NC state
void IOTSKcarrier_Relay::close(){
    digitalWrite(_pin , HIGH);
    _status = HIGH;

}

//NO state
void IOTSKcarrier_Relay::open(){
    digitalWrite(_pin , LOW);
    _status = LOW;
}

int IOTSKcarrier_Relay::getStatus(){
    Serial.println("status");
    Serial.println(_status , BIN);
    return (int)_status;
}