#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 3

#define ENC_A 15
#define ENC_B 14
#define ENC_PORT PINC

#define STARTLED 70
#define NMLEDCORE 30


//the position, according to the rotary encoder
int counter = 0;

//buffer of direction values, used to filter input
int8_t dirBuffer[10];
int bufferIndex = 0;



const int numberLed = 144;


// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numberLed, PIN, NEO_GRB + NEO_KHZ800);



void setup()
{
  /* Setup encoder pins as inputs */
  pinMode(ENC_A, INPUT);
  digitalWrite(ENC_A, HIGH);
  pinMode(ENC_B, INPUT);
  digitalWrite(ENC_B, HIGH);





  strip.begin();

  //turn off all leds
  for (int i = 0; i < numberLed; i++) {

    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }

  strip.show();
  Serial.begin (9600);
}

void loop()
{


  int8_t tmpdata;
  /**/
  tmpdata = read_encoder();

  if (tmpdata != 0) { //if the encoder has moved
    dirBuffer[bufferIndex] = tmpdata; //add the current direction to the buffer


    Serial.println(counter);

    //map the counter value to the leds
    int val = map(counter, 0, 255, 0, NMLEDCORE);

    //turn off all leds
    for (int i = 0; i < numberLed; i++) {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }

    //light the right pixel using modulo so we cycle back once we reach bottom/top
    strip.setPixelColor(mod(val, NMLEDCORE) + STARTLED, strip.Color(255, 255, 255));

    strip.show();




    //if the three previous values in the buffer are the same direction as the current one, count it in counter, else ignore
    if (dirBuffer[mod(bufferIndex - 1, 10)] == tmpdata && dirBuffer[mod(bufferIndex - 2, 10)] == tmpdata && dirBuffer[mod(bufferIndex - 3, 10)] == tmpdata) {
      counter += tmpdata;
    } else {
      bufferIndex = mod(bufferIndex - 1, 10); //put the index back where it was (ignore the value)
    }


  }

  //increment buffer index
  bufferIndex = (bufferIndex + 1) % 10;
}



/* returns change in encoder state (-1,0,1) */
int8_t read_encoder()
{
  static int8_t enc_states[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};
  static uint8_t old_AB = 0;
  /**/
  old_AB <<= 2;                   //remember previous state
  old_AB |= ( ENC_PORT & 0x03 );  //add current state
  return ( enc_states[( old_AB & 0x0f )]);
}


//mathematical modulo
int mod(int a, int b)
{
  int r = a % b;
  return r < 0 ? r + b : r;
}
