/*
  This file is part of the Arduino_MKRIoTCarrier library.
  Copyright (c) 2020 Arduino SA. All rights reserved.

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


#include <Arduino_MKRIoTCarrier.h>
    
MKRIoTCarrier::MKRIoTCarrier(){
}

int MKRIoTCarrier::begin(){
    //Display
    display.init(240, 240);                // Initialize ST7789 screen
    pinMode(TFT_BACKLIGHT, OUTPUT);
    digitalWrite(TFT_BACKLIGHT, HIGH); // Backlight on
    
    //Default rotation to align it with the carrier
    display.setRotation(2);

    if(CARRIER_CASE){
        TOUCH.setSensorsSensitivity(4u);
    }else{
        TOUCH.setSensorsSensitivity(100u);
    }
    Buttons.begin();    //init buttons

    //init LEDs
    leds.begin();

    //PMIC init
    PMIC.begin();
    PMIC.enableBoostMode();
    
    //Sensors
    uint8_t sensorsOK = 0;

    if(!Light.begin()){
        sensorsOK |= 0b1 << 0;
    }
    if(!Pressure.begin()){
        sensorsOK |= 0b1 << 1;
    }
    if(!IMUmodule.begin()){
        sensorsOK |= 0b1 << 2;
    }
    if(!Env.begin()){
        sensorsOK |= 0b1 << 3;
    }

    //SD  card, not checkign the begin, if it doesnt have a SD plugged returns false
    SD.begin(SD_CS);

    Serial.println(sensorsOK,BIN);

    //If some of the sensors are not connected
    if(sensorsOK > 0){
        Serial.println("Error detected!");
        if(sensorsOK & 0b0001){
            Serial.println("Ambient light sensor is not connected!");
        }
        if(sensorsOK & 0b0010){
            Serial.println("Pressure sensor is not connected!");
        }
        if(sensorsOK & 0b0100){
            Serial.println("IMU is not connected");
        }
        if(sensorsOK & 0b1000){
            Serial.println("Environmental sensor is not connected!");
        }

       //while (true);
	   return false;
    }

    return true;
}
