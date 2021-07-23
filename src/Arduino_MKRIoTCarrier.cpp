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


#include <Arduino_MKRIoTCarrier.h>

//Touch pads values for using the case or just directly on the board
//Define on the sketch to use it
bool CARRIER_CASE = false;
    
MKRIoTCarrier::MKRIoTCarrier() {
}

int MKRIoTCarrier::begin() {
  //Display
  display.init(240, 240);//.begin(true);      // Initialize ST7789 screen
  pinMode(3,INPUT_PULLUP);     // RESET fix

  //Default rotation to align it with the carrier
  display.setRotation(2);
  display.fillScreen(ST77XX_BLACK);

  if (!CARRIER_CASE) {
    Buttons.updateConfig(200);
  }

  Buttons.begin();    //init buttons

  //init LEDs
  leds.begin();
  leds.clear();
  leds.show();

  //PMIC init
  PMIC.begin();
  PMIC.enableBoostMode();

  //Sensors
  uint8_t sensorsOK = !Light.begin() << 0 |  !Pressure.begin() << 1 | !IMUmodule.begin() << 2  | !Env.begin() << 3;

  //If some of the sensors are not connected
  if(sensorsOK > 0 ){
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
    return false;
  }
  Relay1.begin();
  Relay2.begin();
  if(!SD.begin(SD_CS)) {
    Serial.println("Sd card not detected");
  }

  return true;
}
