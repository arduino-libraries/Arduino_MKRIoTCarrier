
#include <Arduino_IOTSK_Qtouch.h>

IOTSKcarrier_Qtouch::IOTSKcarrier_Qtouch(int pin){
    _pin = pin;
}

bool IOTSKcarrier_Qtouch::getTouch(){
    if(analogRead(_pin) == 0){
        return true;
    }
    return false;
}