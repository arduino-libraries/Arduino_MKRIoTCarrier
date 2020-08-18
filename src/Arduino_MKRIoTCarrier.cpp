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

// Constructor
MKRIoTCarrier::MKRIoTCarrier(){
}

// Main begin, initialization of all the features from the carrier
// Output: If some sensor return false, it will Print it in the Serial Monitor
int MKRIoTCarrier::begin(){
    // Display
    display.init(240, 240);            // Initialize ST7789 screen
    pinMode(TFT_BACKLIGHT, OUTPUT);
    digitalWrite(TFT_BACKLIGHT, HIGH); // Backlight on
    
    //Default rotation to align it with the carrier
    display.setRotation(2);
    display.fillScreen(ST77XX_BLACK);

    //Set up the start configuration for the touch pads
    if(CARRIER_CASE){
        TOUCH.setSensorsSensitivity(4u);
    }else{
        TOUCH.setSensorsSensitivity(100u);
    }
	
    // init buttons
    Buttons.begin();

    //init LEDs
    leds.begin();
    leds.clear();
    leds.show();

    //PMIC init
    PMIC.begin();
    PMIC.enableBoostMode();
    
    //Sensors
    uint8_t sensorsOK = !Light.begin() << 0 |  !Pressure.begin() << 1 | !IMUmodule.begin() << 2  | !Env.begin() << 3 ;
    // Serial.println(sensorsOK , BIN);

    // Check if some of the sensors is not connected
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

       //while (true);
	return false;
    }

	//Its OK if the SD card is not plugged in
	if(!SD.begin(SD_CS)){
            Serial.println("Sd card not detected");
        }
    return true;
}
