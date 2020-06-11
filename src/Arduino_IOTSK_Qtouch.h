#ifndef ARDUINO_IOTSKcarrier_Qtouch
#define ARDUINO_IOTSKcarrier_Qtouch

#include "Arduino.h"

class IOTSKcarrier_Qtouch{
    public:
    IOTSKcarrier_Qtouch(int pin);
    int getPin();

    bool getTouch();
    
    private:
    int _pin;
};

#endif