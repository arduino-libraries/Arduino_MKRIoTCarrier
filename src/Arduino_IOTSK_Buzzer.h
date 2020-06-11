#ifndef ARDUINO_IOTSKcarrier_Buzzer
#define ARDUINO_IOTSKcarrier_Buzzer

#include "Arduino.h"

class IOTSKcarrier_Buzzer{
    public:
    IOTSKcarrier_Buzzer(int pin);
    int getPin();

    void sound(int freq);
   
    void noSound();
    
    private:
    int _pin;
};

#endif