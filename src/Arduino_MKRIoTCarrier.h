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


#ifndef ARDUINO_MKRIoTCarrier_h
#define ARDUINO_MKRIoTCarrier_h

#include <Arduino.h>
#include <MKRIoTCarrierDefines.h>

#include <IMUClass.h>    //IMU
#include <PressureClass.h>    //IMU
#include <EnvClass.h>    //IMU
#include "AirQualityClass.h"

//RGB LEDs
#include <Adafruit_DotStar.h>
#define NUMPIXELS  5 // Number of LEDs in strip
#define DATAPIN    5
#define CLOCKPIN   4

//Taken from the carrier schematics

#define BUZZER      7

#define SD_CS       0

#define INT         6   //Every sensor interrupt pin , PULL-UP

#define LED_CKI     4
#define LED_SDI     5

#define TFT_RST       -1 // Or set to -1 and connect to Arduino RESET pin
#define TFT_BACKLIGHT 3

//Touch pads values for using the case or just directly on the board
//Define on the sketch to use it
extern bool CARRIER_CASE;

//Gesture change for APDS9960
enum {
  NONE = -1,
  DOWN = 3,
  UP = 2 ,
  LEFT  = 1,
  RIGHT = 0
};

typedef enum {
  RELAY_1 = 1,
  RELAY_2
} Relay_t;

class MKRIoTCarrier{
  public:
    MKRIoTCarrier();
    int begin();
    static int getBoardRevision();

    // Case
    void withCase() { CARRIER_CASE = true; };
    void noCase()   { CARRIER_CASE = false; };

    //Sensors
    APDS9960& Light = APDS;
    PressureClass Pressure{MKRIoTCarrier::getBoardRevision};
    IMUClass IMUmodule{MKRIoTCarrier::getBoardRevision};
    EnvClass Env{MKRIoTCarrier::getBoardRevision};
    AirQualityClass AirQuality{MKRIoTCarrier::getBoardRevision};

    //Misc
    //Relays
    MKRIoTCarrier_Relay Relay1 = MKRIoTCarrier_Relay{RELAY_1,MKRIoTCarrier::getBoardRevision};   
    MKRIoTCarrier_Relay Relay2 = MKRIoTCarrier_Relay{RELAY_2,MKRIoTCarrier::getBoardRevision};   

    //Buzzer
    MKRIoTCarrier_Buzzer Buzzer =  MKRIoTCarrier_Buzzer(BUZZER);  //Buzzer, pin 6

    //Buttons
    MKRIoTCarrierQtouch Buttons{MKRIoTCarrier::getBoardRevision};


    MKRIoTCarrierQtouch Button0 __attribute__((deprecated)) = MKRIoTCarrierQtouch(TOUCH0,MKRIoTCarrier::getBoardRevision);
    MKRIoTCarrierQtouch Button1 __attribute__((deprecated)) = MKRIoTCarrierQtouch(TOUCH1,MKRIoTCarrier::getBoardRevision);
    MKRIoTCarrierQtouch Button2 __attribute__((deprecated)) = MKRIoTCarrierQtouch(TOUCH2,MKRIoTCarrier::getBoardRevision);
    MKRIoTCarrierQtouch Button3 __attribute__((deprecated)) = MKRIoTCarrierQtouch(TOUCH3,MKRIoTCarrier::getBoardRevision);
    MKRIoTCarrierQtouch Button4 __attribute__((deprecated)) = MKRIoTCarrierQtouch(TOUCH4,MKRIoTCarrier::getBoardRevision);

    //Display
    Adafruit_ST7789 display = Adafruit_ST7789(-1, -1, -1);
	
    //RGB LEDs
    Adafruit_DotStar leds = Adafruit_DotStar(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BGR);
  private:
    static int _revision;
    int _relay1_pin;
    int _relay2_pin;
};

#endif
