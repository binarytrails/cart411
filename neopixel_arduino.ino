#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 9


const int numberLed = 13;
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numberLed, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

String inString = "";    // string to hold input
bool on[numberLed];

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code


  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  strip.begin();


  for (int i = 0; i < numberLed; i++) {

    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }

  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  /*  for (int i = 0; i < numberLed; i++) {
      if (i > 0) {
        strip.setPixelColor(i - 1, strip.Color(0, 0, 0));
      } else {
        strip.setPixelColor(numberLed - 1, strip.Color(0, 0, 0));
      }

      strip.setPixelColor(i, strip.Color(255,255,255));
      strip.show();

      delay(20);
    }*/


  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar) || inChar == ',') {
      // convert the incoming byte to a char
      // and add it to the string:
      inString += (char)inChar;
    }
    // if you get a newline, print the string,
    // then the string's value:
    if (inChar == '\n') {


      int commaIndex = inString.indexOf(',');

      int index = inString.substring(0, commaIndex).toInt();
      int val = inString.substring(commaIndex + 1).toInt();



      if (index >= 0 && index < numberLed) {

        strip.setPixelColor(index, strip.Color(val * 255, val * 255, val * 255));

        strip.show();
      }
      // clear the string for new input:
      inString = "";
    }
  }

  //  for (int i = numberLed; i > 0; i--) {
  //    if (i < numberLed - 1) {
  //      strip.setPixelColor(i + 1, strip.Color(0, 0, 0));
  //    } else {
  //      strip.setPixelColor(0, strip.Color(0, 0, 0));
  //    }
  //
  //    strip.setPixelColor(i, strip.Color(255, 255, 255));
  //    strip.show();
  //
  //    delay(20);
  //  }
}


