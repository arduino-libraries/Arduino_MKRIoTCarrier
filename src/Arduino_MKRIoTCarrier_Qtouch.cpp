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
MKRIoTCarrierQtouch::MKRIoTCarrierQtouch() {
}

//Individual pad
MKRIoTCarrierQtouch::MKRIoTCarrierQtouch(touchButtons padIndex) {
  _padID = padIndex;
}

bool MKRIoTCarrierQtouch::getTouch(touchButtons padIndex) {
  if(_available) {
    return TOUCH.read(padIndex);
  }
  return false;
}

bool MKRIoTCarrierQtouch::getTouch() {
  return getTouch(_padID);
}

bool MKRIoTCarrierQtouch::onTouchDown(touchButtons padIndex) {
  if(_available) {
    if(getTouch(padIndex) && _touchesPrev[padIndex] == 0) {
      _touchesPrev[padIndex] = 1;
      return true;
    }
    _touchesPrev[padIndex] = getTouch(padIndex);
  }
  return false;
}

bool MKRIoTCarrierQtouch::onTouchDown() {
  return onTouchDown(_padID);
}

bool MKRIoTCarrierQtouch::onTouchUp(touchButtons padIndex) {
  if(_available) {
    if(!getTouch(padIndex) && _touchesPrev[padIndex] == 1) {
      _touchesPrev[padIndex] = 0;
      return true;
    }
    _touchesPrev[padIndex] = getTouch(padIndex);
  }
  return false;
}

bool MKRIoTCarrierQtouch::onTouchUp() {
  return onTouchUp(_padID);
}

bool MKRIoTCarrierQtouch::onTouchChange(touchButtons padIndex) {
  if(_available) {
    if(_touchesPrev[padIndex] != getTouch(padIndex)){
        _touchesPrev[padIndex] = getTouch(padIndex);
        return true;
    }
  }
  return false;
}

bool MKRIoTCarrierQtouch::onTouchChange() {
  return onTouchChange(_padID);
}

void MKRIoTCarrierQtouch::updateConfig(int newSens, touchButtons padIndex) {
  TOUCH.setSensorsSensitivity(newSens, padIndex);
  customSens = true;
}


//Manager
bool MKRIoTCarrierQtouch::begin() {
  return TOUCH.begin();
}

bool MKRIoTCarrierQtouch::update() {
  TOUCH.poll();
  if(TOUCH.available()) {
    _available = true;
    return _available;
  }
  _available =  false;
  return _available;
}

void MKRIoTCarrierQtouch::updateConfig(int newSens) {
  TOUCH.setSensorsSensitivity(newSens);
  customSens = true;
}
