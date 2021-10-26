#ifndef _display_
#define _display_

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include "Adafruit_ST77xx.h"
#include <SPI.h>

class Arduino_MKRIoTCarrier_Display : public Adafruit_ST7789
{
public:
    Arduino_MKRIoTCarrier_Display(SPIClass *spiClass, int8_t cs, int8_t dc, int8_t rst)
        : Adafruit_ST7789(spiClass, cs, dc, rst){}

    void test(){
        setTextColor(ST77XX_BLUE);
        setTextSize(5);
        setCursor(2,20);
        print("test");

    }
    
private:
};

#endif