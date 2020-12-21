# **MKR IoT Carrier Reference**

This is a basic documentation about the library for the *MKR IoT Carrier* .

The library can be downloaded from the Arduino IDE’s library manager or by going to the [github repository](https://github.com/arduino-libraries/Arduino_MKRIoTCarrier)

This carrier has a lot of features and sensors to play with, some of them are the capacitive buttons, 5 RGB LEDs, the 240x240 RGB display and much more!

## Examples Included
*   Actuators
    *   Buzzer_Melody
    *   Relays_blink
*   All Features
*   Display
*   LEDs
*   SD_card
*   Sensors
    *   Environment
    *   IMU
    *   Light
    *   Pressure
*   TouchPads
    *   getTouch
    *   Relays_control_Qtouch
    *   Touch_and_LEDs
    *   TouchTypes
*   Interruptions (TODO)
*   Arduino Cloud (TODO)

## Classes

### MKRIoTCarrier

Constructor of the object

```cpp
MKRIoTCarrier yourName; //In the examples we name it as *carrier*
```

Intialization example sketch

```cpp
#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;

setup(){
Serial.begin(9600);
//This will adjust the sensitivity of the touch pads, not mandatory to set it, by default is false
CARRIER_CASE = false; 
if(!carrier.begin(){  //It will see any sensor failure
   Serial.println("Failure on init");
   while(1);
 }
}
```

### SD CARD
This can be accessed using the SD library commands that is already #included inside the library

The SD class initialized in the main `begin()`

The chip select (CS) pin can be known with SD_CS


**Syntax Example**

```cpp
#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;

File myFile;

setup(){
   CARRIER_CASE = false; 
   carrier.begin();  //SD card initialized here
   
   myFile = SD.open("test.txt", FILE_WRITE);
}
```

### Buttons class

Init the calaibration and the set up for the touchable pads (Already done in the MKRIoTCarrier class' begin())
```cpp
Buttons.begin()
```
Read the state of the pads and save them to be analize in the diferent type of touch events
```cpp
Buttons.update()
```

### ButtonX class

Button0 - Button4

Get if the pad is getting touched, true until it gets released
```cpp
ButtonX.getTouch()
```

Get when have been a touch down
```cpp 
ButtonX.onTouchDown()
```

Get when the button has been released
```cpp
ButtonX.onTouchUp()
```

Get both, touched and released
```cpp
ButtonX.onTouchChange()
```

In case you have another enclosure you can change the sensivity of the pads, 3-100
Automatically configured when you set the `CARRIER_CASE` boolean, by default is false (sensitivity threshold 4)

```cpp
ButtonX.updateConfig(int newSens)
```

#### Syntax example
```cpp
#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;

void setup(){
   Serial.begin(9600);
   CARRIER_CASE = true/false;
   carrier.begin();
}

void loop(){
   carrier.Buttons.update();	// Read the buttons state
   
   //Check if the Button 0 is being touched
   if (carrier.Button0.getTouch()){
      Serial.println("Touching Button 1");
   }
   
   //You can replace getTouch(), with the other types of touch events
   //If you use more than one type of events in the same Button its not going to be stable, watch out
   //In case you need it, after each touch event make a Buttons.update() to read it correctly
}

```

### Buzzer class

Equivalent to tone(), it will make the tone with the selected frequency
```cpp
Buzzer.sound(freq)
```
Equivalent to noTone(), it will stop the tone signal
```cpp
Buzzer.noSound()
```

### Relay class

Control both relays and get the status of them

You can control them by using `Relay1 `and `Relay2`

Swap to the NormallyOpen (NO) circuit of the relay
```cpp
RelayX.open()
```
Swap to the NormallyClosed (NC) circuit of the relay, default mode on power off
```cpp
RelayX.close()
```

Bool, returns the status LOW means NC and HIGH means NO
```cpp
RelayX.getStatus()
```

### DotStar LEDs

It is controlled with the Adafruit’s DotStar library

The documentation form Adafruit [here](https://learn.adafruit.com/adafruit-dotstar-leds/arduino-library-use)

**Syntax Example**
```cpp
#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;

uint32_t myCustomColor = carrier.leds.Color(255,100,50);

void setup(){
   CARRIER_CASE = false;
   carrier.begin();
   carrier.leds.fill(myCustomColor, 0, 5);
   carrier.leds.show();
}

void loop(){}
```

Some examples
Init the LEDs strip, done by default using the main begin()
```cpp
leds.begin()
```

Sets the color of the index’s LED
```cpp
leds.setPixelColor(index, green, red, blue)
```

In case you have custom colors you can use this method too
```cpp
leds.setPixelColor(index, color)
```

Set the overall brightness
```cpp
leds.setBrightness(0-255)
```

Update the LEDs with the new values
```cpp
leds.show()
```
 
Clear the buffer of the LEDs
```cpp
leds.clear()
```
 
Fill X amount of the LEDs with the same color
```cpp
leds.fill(color, firstLedToCount, count)
```

Save your custom color:
```cpp
uint32_t myColor = carrier.leds.Color(green, red, blue)
```

### Pressure sensor - LPS22HB (Barometric)
Visit our reference about [LPS22HB](https://www.arduino.cc/en/Reference/ArduinoLPS22HB)

**Syntax Example**
```cpp
float pressure; 
pressure = carrier.Pressure.readPressure()
```

### IMU - LSM6DS3
Visit our reference about [LSM6DS3](https://www.arduino.cc/en/Reference/Arduino_LSM6DS3)

**Syntax Example**
```cpp
float aX,aY,aZ;
carrier.IMUmodule.readAcceleration(aX, aY, aZ);
```

### Humidity and Temperature - HTS221
Visit our reference about [HTS221](https://www.arduino.cc/en/Reference/ArduinoHTS221)

**Syntax Example**
```cpp
float humidity;
humidity = carrier.Env.readHumidity();
```

### Ambient light, Gesture and Proximity - APDS9960
Visit our reference about [APDS9960](https://www.arduino.cc/en/Reference/ArduinoAPDS9960)

**Syntax Example**
```cpp
int proximity;
proximity = carrier.Light.readProximity();
```

## Display

It is controlled through the Adafruit-ST7735-Library 

The resolution is 240 x 240.

Initialized inside the main `begin()`

You can find the library documentation from Adafruit to draw [here](https://learn.adafruit.com/adafruit-gfx-graphics-library/graphics-primitives)

Colors : every color with the prefix ‘ST77XX_’ i.e. ST77XX_BLACK. Colors available from the library are BLACK, WHITE, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, ORANGE
