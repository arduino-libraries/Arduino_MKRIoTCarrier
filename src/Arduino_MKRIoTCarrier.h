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
#include <Wire.h>

#include <Arduino_PMIC.h>       //PMIC

//Sensor libraries
#include <Arduino_APDS9960.h>   //Ambient light
#include <Arduino_LPS22HB.h>    //Pressure sensor
#include <Arduino_LSM6DS3.h>    //IMU
#include <Arduino_HTS221.h>     // env sensor

#include <Arduino_MKRIoTCarrier_Relay.h> //Relays
#include <Arduino_MKRIoTCarrier_Buzzer.h>//Buzzer
#include <Arduino_MKRIoTCarrier_Qtouch.h>//Buttons
#include <SD.h>                  //SD card

//Display
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

//RGB LEDs
#include <Adafruit_DotStar.h>
#define NUMPIXELS  5 // Number of LEDs in strip
#define DATAPIN    5
#define CLOCKPIN   4

//Taken from the carrier schematics
#define RELAY_1     14
#define RELAY_2     13
#define BUZZER      7

#define GROVE_AN1   A5
#define GROVE_AN2   A6

#define SD_CS       0

#define Y0          A0
#define Y1          A1
#define Y2          A2
#define Y3          A3
#define Y4          A4

#define INT         6   //Every sensor interrupt pin , PULL-UP

#define LED_CKI     4
#define LED_SDI     5

#define TFT_CS        2
#define TFT_RST       -1 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC        1
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

class MKRIoTCarrier{
  public:
    MKRIoTCarrier();
    int begin();

    // Case
    void withCase() { CARRIER_CASE = true; };
    void noCase()   { CARRIER_CASE = false; };

    //Sensors
    APDS9960& Light = APDS;
    LPS22HBClass& Pressure = BARO;
    LSM6DS3Class& IMUmodule  = IMU;
    HTS221Class& Env = HTS;

    //Misc
    //Relays
    MKRIoTCarrier_Relay Relay1 = MKRIoTCarrier_Relay(RELAY_1);    //Relay 1 , pin 14
    MKRIoTCarrier_Relay Relay2 = MKRIoTCarrier_Relay(RELAY_2);    //Relay 2 , pin 13

    //Buzzer
    MKRIoTCarrier_Buzzer Buzzer =  MKRIoTCarrier_Buzzer(BUZZER);  //Buzzer, pin 6

    //Buttons
    MKRIoTCarrierQtouch Buttons = MKRIoTCarrierQtouch();


    MKRIoTCarrierQtouch Button0 __attribute__((deprecated)) = MKRIoTCarrierQtouch(TOUCH0);
    MKRIoTCarrierQtouch Button1 __attribute__((deprecated)) = MKRIoTCarrierQtouch(TOUCH1);
    MKRIoTCarrierQtouch Button2 __attribute__((deprecated)) = MKRIoTCarrierQtouch(TOUCH2);
    MKRIoTCarrierQtouch Button3 __attribute__((deprecated)) = MKRIoTCarrierQtouch(TOUCH3);
    MKRIoTCarrierQtouch Button4 __attribute__((deprecated)) = MKRIoTCarrierQtouch(TOUCH4);

    //Display
    Adafruit_ST7789 display = Adafruit_ST7789(TFT_CS, TFT_DC, -1);
	
    //RGB LEDs
    Adafruit_DotStar leds = Adafruit_DotStar(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BGR);
};
#endif
