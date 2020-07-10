#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier; //Constructor of the carrier maybe we can include it on the library itself

//Auto configure the sense distance for the touch pads
bool CARRIER_CASE = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial);

  //Init all the components from the board
  carrier.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  //Each time you want to update the reads from the pads use this
  //It will update all the pads at the same time
  carrier.Buttons.update();

  //Different types of touches
  //When you first touch it
  if (carrier.Button1.onTouchDown()) {
    Serial.print("TOUCH DOWN");
    carrier.leds.setPixelColor(0, 20, 20, 20);   // 'Off' pixel at tail
    carrier.leds.show();                     // Refresh strip
    delay(50);
  } else {
    carrier.leds.setPixelColor(0, 0);
    carrier.leds.show();                     // Refresh strip
  }

  //When you release it
  if (carrier.Button2.onTouchUp()) {
    Serial.print("TOUCH UP");
    carrier.leds.setPixelColor(1, 20, 20, 20);   // 'Off' pixel at tail
    carrier.leds.show();                     // Refresh strip
    delay(50);
  } else {
    carrier.leds.setPixelColor(1, 0);
    carrier.leds.show();                     // Refresh strip
  }

  //When it detects a change, down or up
  if (carrier.Button3.onTouchChange()) {
    Serial.print("TOUCH CHANGE");
    carrier.leds.setPixelColor(2, 20, 20, 20);   // 'Off' pixel at tail
    carrier.leds.show();                     // Refresh strip
    delay(50);
  } else {
    carrier.leds.setPixelColor(2, 0);
    carrier.leds.show();                     // Refresh strip
  }

  //Normal, if it is being pressed
  if (carrier.Button4.getTouch()) {
    Serial.print("GETTING TOUCH");
    carrier.leds.setPixelColor(3, 20, 20, 20);   // 'Off' pixel at tail
    carrier.leds.show();                     // Refresh strip
    delay(5);
  } else {
    carrier.leds.setPixelColor(3, 0);
    carrier.leds.show();                     // Refresh strip
  }

  if (carrier.Button5.getTouch()) {
    Serial.print("GETTING TOUCH");
    carrier.leds.setPixelColor(4, 20, 20, 20);   // 'Off' pixel at tail
    carrier.leds.show();                     // Refresh strip
    delay(5);
  } else {
    carrier.leds.setPixelColor(4, 0);
    carrier.leds.show();                     // Refresh strip
  }


  Serial.println();
  delay(10);
}
