// Author: Kali Regenold
// Date: July 2020

// Arduino code to run my LED strip.
// Reads RGB bytes in from serial and displays them on a pixel.
// Currently sets pixel 200 because it's one that I can see from my desk.
// TODO: Retreive several colors from serial and cycle through them.

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define NUM_PIX 300
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIX, PIN, NEO_GRB + NEO_KHZ800);

int red_byte = 0;
int blu_byte = 0;
int gre_byte = 0;

int packet_size = 0;
uint32_t palette[5];

void setup() {
  Serial.begin(9600);

  strip.begin();
  strip.setBrightness(50);
  set_off();
}

void loop() {
  // Read in RGB and sets pixel to that value
  if(Serial.available() > 0)
  {
    packet_size = Serial.read();
    for(int i = 0; i < packet_size; i++)
    {
      palette[i] = read_RGB();
      for(int j = 0; j < 20; j++)
      {
        strip.setPixelColor(150+(i*20)+j, palette[i]);
      }
    }
    strip.show();
  }
  delay(200);
}

uint32_t read_RGB()
{
  red_byte = Serial.read();
  blu_byte = Serial.read();
  gre_byte = Serial.read();

  return strip.Color(red_byte, blu_byte, gre_byte);
}


// Set `num` number of pixels to red
// Used to visually display how many bytes are available on the serial port
void set_num(int num) {
  set_off();
  for(int i = 0; i < num; i++){
    strip.setPixelColor(200+i, strip.Color(255,0,0));
  }
  strip.show();
}

// Set all pixels to off.
void set_off() {
  for(int i = 0; i < NUM_PIX; i++) {
    strip.setPixelColor(i, 0);
  }
  strip.show();
}

///////////////////////////////////////
// Set given pixel to function color
///////////////////////////////////////
void set_red(int i) {
  strip.setPixelColor(i, strip.Color(255,0,0));
  strip.show();
}

void set_gre(int i) {
  strip.setPixelColor(i, strip.Color(0,255,0));
  strip.show();
}

void set_blu(int i) {
  strip.setPixelColor(i, strip.Color(0,0,255));
  strip.show();
}
