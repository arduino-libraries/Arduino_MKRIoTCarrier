#ifndef ARDUINO_MKRIoTCarrier_Relay
#define ARDUINO_MKRIoTCarrier_Relay

#include "Arduino.h"

class MKRIoTCarrier_Relay{
    public: 
    MKRIoTCarrier_Relay(int pin);
    
    void open();
    void close();

    int getStatus();

    private:
    int _pin;
    int _status;
};

#endif