#ifndef _CARRIE_DEFINES_
#define _CARRIE_DEFINES_

#include <Wire.h>
#include <SPI.h>

#include <Arduino_PMIC.h>       //PMIC

//Sensor libraries
#include <Arduino_APDS9960.h>   //Ambient light
#include <Arduino_LPS22HB.h>    //Pressure sensor
#include "bme68xLibrary.h"
#include <Arduino_HTS221.h>     // env sensor
#include <Arduino_LSM6DSOX.h>

#include <Arduino_MKRIoTCarrier_Relay.h> //Relays
#include <Arduino_MKRIoTCarrier_Buzzer.h>//Buzzer
#include <Arduino_MKRIoTCarrier_Qtouch.h>//Buttons
#include <SD.h>                  //SD card

//Display
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789


/* Type for getRevision functions */
using getRev_t = int (*)();

typedef enum {
    BOARD_REVISION_1 = 1,
    BOARD_REVISION_2 = 2,
} _mkr_io_carrier_board_revision;

namespace mkr_iot_carrier_rev1 {
    enum relays {
        RELAY1 = 14,
        RELAY2 = 13,
    };
    enum display {
        TFT_CS = 2,
        TFT_DC = 1,
    };
};

namespace mkr_iot_carrier_rev2 {
    enum relays {
        RELAY1 = 1,
        RELAY2 = 2,
    };
    enum display {
        TFT_CS = 13,
        TFT_DC = 14,
    };
};

#define BME_SLAVE_ADDRESS   0x76

#define LSM6DSOX_ADDRESS           0x6A
#define LSM6DS3_ADDRESS            0x6A

#ifdef ARDUINO_SAMD_MKRWIFI1010
#define AREF_PIN 25
#endif

#endif