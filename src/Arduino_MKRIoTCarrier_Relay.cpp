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


#include "Arduino_MKRIoTCarrier_Relay.h"

MKRIoTCarrier_Relay::MKRIoTCarrier_Relay(int pin):_pin{pin}
{
}
void MKRIoTCarrier_Relay::begin(){
    pinMode(_pin ,OUTPUT);
    close();
}
int MKRIoTCarrier_Relay::getPin(){
    return _pin;
}
//NC state
void MKRIoTCarrier_Relay::close(){
    digitalWrite(_pin , LOW);
    _status = LOW;

}

//NO state
void MKRIoTCarrier_Relay::open(){
    digitalWrite(_pin , HIGH);
    _status = HIGH;
}

int MKRIoTCarrier_Relay::getStatus(){
    //Serial.println("status");
    //Serial.println(_status , BIN);
    return (int)_status;
}
