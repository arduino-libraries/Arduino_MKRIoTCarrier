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

//manager
class MKRIoTCarrier_Qtouch_Manager{
    public:
    MKRIoTCarrier_Qtouch_Manager(); 
    
    bool begin();
    void update();

    int t_state[5];

    //Set touch settings
    void updateConfig(int newSens);
  	bool customSens = false;
  
};

class MKRIoTCarrier_Qtouch{
    public:
    MKRIoTCarrier_Qtouch(int padIndex, MKRIoTCarrier_Qtouch_Manager * pManager); //Individual
    
    bool getTouch();
    bool onTouchDown();
    bool onTouchUp();
    bool onTouchChange();

    private:
    MKRIoTCarrier_Qtouch_Manager  * _pManager;
    int _padIndex;  

    bool _touches[10];                //To know last touches

    void _saveToHistory(bool newEntry);

    //Cfg
    bool setOnChange = false;       //Touch on change
    bool setOnNormal = false;       //Allways read
    bool setOnUp = false;           //When the pad is not being touched
    bool setOnDown = false;         //When is pressed, to make 2 Downs you need to touch it, release it and touch it again
};

#endif
