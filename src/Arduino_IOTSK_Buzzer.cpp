#include "Arduino_IOTSK_Buzzer.h"


IOTSKcarrier_Buzzer::IOTSKcarrier_Buzzer(int pin){
    _pin = pin;
}

int IOTSKcarrier_Buzzer::getPin(){
    return _pin;
}

void IOTSKcarrier_Buzzer::sound(int freq){
    tone(_pin , freq);
}

void IOTSKcarrier_Buzzer::noSound(){
    noTone(_pin);
}