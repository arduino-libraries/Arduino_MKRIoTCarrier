#include "Arduino_MKRIoTCarrier_Relay.h"

MKRIoTCarrier_Relay::MKRIoTCarrier_Relay(int pin){
    _pin = pin;
    pinMode(_pin ,OUTPUT);
    open();
    
}

//NC state
void MKRIoTCarrier_Relay::close(){
    digitalWrite(_pin , LOW);
    _status = LOW;

}

//NO state
void MKRIoTCarrier_Relay::open(){
    digitalWrite(_pin , HIGH);
    _status = HIGH;
}

int MKRIoTCarrier_Relay::getStatus(){
    //Serial.println("status");
    //Serial.println(_status , BIN);
    return (int)_status;
}