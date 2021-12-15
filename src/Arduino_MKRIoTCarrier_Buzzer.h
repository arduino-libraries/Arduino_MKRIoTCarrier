/*
  This file is part of the Arduino_MKRIoTCarrier library.
  Copyright (c) 2020 Arduino SA.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#ifndef ARDUINO_MKRIoTCarrier_Buzzer
#define ARDUINO_MKRIoTCarrier_Buzzer

#include "Arduino.h"

class MKRIoTCarrier_Buzzer{
    public:
    MKRIoTCarrier_Buzzer(int pin);
    int getPin();

    void sound(int freq);
   
    void noSound();

    void beep(int freq = 800, unsigned long duration = 20);
    
    private:
    int _pin;
};

#endif
