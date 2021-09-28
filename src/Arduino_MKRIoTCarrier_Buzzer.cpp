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

void MKRIoTCarrier_Buzzer::beep(int freq, unsigned long duration) {
    this->sound(freq);
    delay(duration);
    this->noSound();
}
