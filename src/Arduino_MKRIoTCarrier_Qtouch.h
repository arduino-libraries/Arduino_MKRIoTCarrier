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
#include <MKRIoTCarrierDefines.h>

static bool _available = false;

typedef enum {
  TOUCH0 = 0,
  TOUCH1,
  TOUCH2,
  TOUCH3,
  TOUCH4
} touchButtons;

class MKRIoTCarrierQtouch{
  public:
    MKRIoTCarrierQtouch();
    MKRIoTCarrierQtouch(int (*)(void));
    MKRIoTCarrierQtouch(touchButtons padIndex,int (*)(void));
    bool begin();
    bool update();

    //Set touch settings
    void updateConfig(int newSens, touchButtons padIndex);
    void updateConfig(int newSens);
    bool getTouch(touchButtons _padIndex);
    bool getTouch() __attribute__((deprecated));
    bool onTouchDown(touchButtons _padIndex);
    bool onTouchDown() __attribute__((deprecated));
    bool onTouchUp(touchButtons _padIndex);
    bool onTouchUp() __attribute__((deprecated));
    bool onTouchChange(touchButtons _padIndex);
    bool onTouchChange() __attribute__((deprecated));

    bool customSens = false;

  private:
    touchButtons _padID;
    int _padIndex;

    int (*board_revision)(void);
    int _revision;

    bool _touchesPrev[5] = {0, 0, 0, 0, 0};   //To know last touches

    //Config
    bool setOnChange = false;       //Touch on change
    bool setOnNormal = false;       //Always read
    bool setOnUp = false;           //When the pad is not being touched
    bool setOnDown = false;         //When is pressed, to make 2 Downs you need to touch it, release it and touch it again
};

#endif
