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
#include "MKRIoTCarrierDefines.h"

MKRIoTCarrier_Relay::MKRIoTCarrier_Relay(int index, getRev_t getRev):_index{index}
{
    board_revision = getRev;
}
void MKRIoTCarrier_Relay::begin(){
    
    _revision = board_revision();
    
    if(_revision == BOARD_REVISION_1) 
    {
        if(_index == 1) {
            _pin = mkr_iot_carrier_rev1::RELAY1;
        }
        else if(_index == 2) {
            _pin = mkr_iot_carrier_rev1::RELAY2;
        }
    }
    else {
        /*carrier's revision 2 with pull down on AREF */
        if(_index == 1) {
            _pin = mkr_iot_carrier_rev2::RELAY1;
        }
        else if(_index == 2) {
            _pin = mkr_iot_carrier_rev2::RELAY2;
        }
    }
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
    
    return (int)_status;
}
