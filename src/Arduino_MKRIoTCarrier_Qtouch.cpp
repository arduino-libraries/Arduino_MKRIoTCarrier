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


#include <Arduino_MKRIoTCarrier_Qtouch.h>
#include "Arduino_MCHPTouch.h"

//Individual pad
MKRIoTCarrier_Qtouch::MKRIoTCarrier_Qtouch(int padIndex, MKRIoTCarrier_Qtouch_Manager * pManager){
    _padIndex = padIndex;
    _pManager = pManager;
}

bool MKRIoTCarrier_Qtouch::getTouch(){
    bool getState = _pManager->t_state[_padIndex];
    _saveToHistory(getState);
    return(getState);
}

void MKRIoTCarrier_Qtouch::_saveToHistory(bool newEntry){
    //Serial.println(_padIndex);
    for (int i = 10; i>0; i--){
        _touches[i]  = _touches[i -1];
       /* Serial.print(i);
        Serial.print(" = ");
        Serial.println( _touches[i]);*/
    }
    _touches[0] = newEntry;
    /*
    Serial.print(0);
    Serial.print(" = ");
    Serial.println( _touches[0]);*/
}

bool MKRIoTCarrier_Qtouch::onTouchDown(){
    getTouch();
    //Serial.print(_touches[0]);
    //Serial.print(_touches[1]);
    //Serial.println();
    if(_touches[0] && !_touches[1]){
        return true;
    }else{
        return false;
    }
}
bool MKRIoTCarrier_Qtouch::onTouchUp(){
    getTouch();
    //Serial.print(_touches[0]);
    //Serial.print(_touches[1]);
    //Serial.println();
    if(!_touches[0] && _touches[1]){
        return true;
    }else{
        return false;
    }
}
bool MKRIoTCarrier_Qtouch::onTouchChange(){
    getTouch();
    //Serial.print(_touches[0]);
    //Serial.print(_touches[1]);
    //Serial.println();
    if(_touches[0] != _touches[1]){
        return true;
    }else{
        return false;
    }
}

//Manager
bool MKRIoTCarrier_Qtouch_Manager::begin(){
return TOUCH.begin();
}
MKRIoTCarrier_Qtouch_Manager::MKRIoTCarrier_Qtouch_Manager(){

}
void MKRIoTCarrier_Qtouch_Manager::update(){
    TOUCH .poll();
    if(TOUCH.available()){
        t_state[0] = TOUCH.read(0);
        t_state[1] = TOUCH.read(1);
        t_state[2] = TOUCH.read(2);
        t_state[3] = TOUCH.read(3);
        t_state[4] = TOUCH.read(4);
    }
}

void MKRIoTCarrier_Qtouch_Manager::updateConfig(int newSens){
    TOUCH.setSensorsSensitivity(newSens);
    //TOUCH.setSernsorsHysteresis(newHyst);
    TOUCH.begin();
	  customSens = true;
}
