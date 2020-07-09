#include "Arduino_MKRIoTCarrier_Buzzer.h"


MKRIoTCarrier_Buzzer::MKRIoTCarrier_Buzzer(int pin){
    _pin = pin;
}

int MKRIoTCarrier_Buzzer::getPin(){
    return _pin;
}

void MKRIoTCarrier_Buzzer::sound(int freq){
    tone(_pin , freq);
}

void MKRIoTCarrier_Buzzer::noSound(){
    noTone(_pin);
}