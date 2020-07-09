#ifndef ARDUINO_MKRIoTCarrier_Buzzer
#define ARDUINO_MKRIoTCarrier_Buzzer

#include "Arduino.h"

class MKRIoTCarrier_Buzzer{
    public:
    MKRIoTCarrier_Buzzer(int pin);
    int getPin();

    void sound(int freq);
   
    void noSound();
    
    private:
    int _pin;
};

#endif