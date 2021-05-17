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


#ifndef ARDUINO_MKRIoTCarrier_Qtouch
#define ARDUINO_MKRIoTCarrier_Qtouch

#include "Arduino.h"
#include "Arduino_MCHPTouch.h"

typedef enum {
  TOUCH1 = 0,
  TOUCH2,
  TOUCH3,
  TOUCH4,
  TOUCH5
} touchButtons;

class MKRIoTCarrierQtouch{
  public:
    MKRIoTCarrierQtouch();
    bool begin();
    bool update();

    //Set touch settings
    void updateConfig(int newSens, touchButtons padIndex);
  
    bool getTouch(touchButtons _padIndex);
    bool onTouchDown(touchButtons _padIndex);
    bool onTouchUp(touchButtons _padIndex);
    bool onTouchChange(touchButtons _padIndex);

    void updateConfig(int newSens);

    bool customSens = false;

  private:
    int _padIndex;
    bool _available = false;

    bool _touchesPrev[5] = {0, 0, 0, 0, 0};   //To know last touches

    //Config
    bool setOnChange = false;       //Touch on change
    bool setOnNormal = false;       //Allways read
    bool setOnUp = false;           //When the pad is not being touched
    bool setOnDown = false;         //When is pressed, to make 2 Downs you need to touch it, release it and touch it again
};

#endif
