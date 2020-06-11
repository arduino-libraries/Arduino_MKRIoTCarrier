#ifndef ARDUINO_IOTSKcarrier_Relay
#define ARDUINO_IOTSKcarrier_Relay

#include "Arduino.h"

class IOTSKcarrier_Relay{
    public: 
    IOTSKcarrier_Relay(int pin);
    
    void open();
    void close();

    int getStatus();

    private:
    int _pin;
    int _status;
};

#endif