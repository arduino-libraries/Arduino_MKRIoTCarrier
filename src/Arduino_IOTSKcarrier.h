
#ifndef ARDUINO_IOTSKcarrier_h
#define ARDUINO_IOTSKcarrier_h



#include <Arduino.h>
#include <Wire.h>

#include <Arduino_PMIC.h>       //PMIC

//Sensor libraries
#include <Arduino_APDS9960.h>   //Ambient light
#include <Arduino_LPS22HB.h>    //Preassure sensor
#include <Arduino_LSM6DS3.h>    //IMU
#include <Arduino_HTS221.h>     // env sensor

#include <Arduino_IOTSK_Relay.h> //Relays
#include <Arduino_IOTSK_Buzzer.h>//Buzzer
#include <Arduino_IOTSK_Qtouch.h>//Buttons
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

#define DISP_DC     1
#define DISP_CS     2
#define DISP_BL_RST 3   //BOTH DISP_BL and DISP_RST , DISP_RST connected to Arduino's RST pin too

#define INT         7   //Every sensor interrupt pin , PULL-UP

#define LED_CKI     4
#define LED_SDI     5

#define TFT_CS        2
#define TFT_RST       -1 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC        1
#define TFT_BACKLIGHT 3

//Touch pads values for using the case or just directly on the board
//Define on the sketch to use it
extern bool CARRIER_CASE;


class IOTSKcarrier{
    public:
    IOTSKcarrier();
    int begin();

    //Sensors
    APDS9960& Light = APDS;
    LPS22HBClass& Preassure = BARO;
    LSM6DS3Class& IMUmodule  = IMU;
    HTS221Class& Env = HTS;

    //Misc
    //Relays
    IOTSKcarrier_Relay Relay1 = IOTSKcarrier_Relay(RELAY_1);    //Relay 1 , pin 14
    IOTSKcarrier_Relay Relay2 = IOTSKcarrier_Relay(RELAY_2);    //Relay 2 , pin 13

    //Buzzer
    IOTSKcarrier_Buzzer Buzzer =  IOTSKcarrier_Buzzer(BUZZER);  //Buzzer, pin 6

    //Buttons
    IOTSKcarrier_Qtouch_Manager Buttons = IOTSKcarrier_Qtouch_Manager();
    IOTSKcarrier_Qtouch Button1 = IOTSKcarrier_Qtouch(0, &Buttons);
    IOTSKcarrier_Qtouch Button2 = IOTSKcarrier_Qtouch(1, &Buttons);
    IOTSKcarrier_Qtouch Button3 = IOTSKcarrier_Qtouch(2, &Buttons);
    IOTSKcarrier_Qtouch Button4 = IOTSKcarrier_Qtouch(3, &Buttons);
    IOTSKcarrier_Qtouch Button5 = IOTSKcarrier_Qtouch(4, &Buttons);

    //Display
    Adafruit_ST7789 display = Adafruit_ST7789(&SPI, TFT_CS, TFT_DC, TFT_RST);
	
    //RGB LEDs
    Adafruit_DotStar leds = Adafruit_DotStar(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);
    private:
};



#endif