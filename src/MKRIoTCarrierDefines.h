
#include <Wire.h>
#include <SPI.h>

#include <Arduino_PMIC.h>       //PMIC

//Sensor libraries
#include <Arduino_APDS9960.h>   //Ambient light
#include <Arduino_LPS22HB.h>    //Pressure sensor
#include "bme68xLibrary.h"
#include <Arduino_HTS221.h>     // env sensor
#define IMU IMU6DS3
#include <Arduino_LSM6DS3.h>
#undef IMU
#include <Arduino_LSM6DSOX.h>

#include <Arduino_MKRIoTCarrier_Relay.h> //Relays
#include <Arduino_MKRIoTCarrier_Buzzer.h>//Buzzer
#include <Arduino_MKRIoTCarrier_Qtouch.h>//Buttons
#include <SD.h>                  //SD card

//Display
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789

#define BOARD_REVISION_2    1
#define BME_SLAVE_ADDRESS   0x76

#ifdef ARDUINO_SAMD_MKRWIFI1010
#define AREF_PIN 25
#endif