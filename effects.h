#ifndef  EFFECTS_H
#define  EFFECTS_H

#include <Adafruit_NeoPixel.h>

//  #define PIN D4
  #define SPOKES 5
  #define MAXSPOKES 6
  #define RADIUS 6
  #define NUMPIXEL RADIUS
  #define MAXRADIUS 60
  #define ALL SPOKES
  //#define BRIGHTNESS -1  // advoids brightness conversion loss
  #define BRIGHTNESS 0x40
  #define WHITE 255 + 255<<8 + 255<<16
  #define BLACK 0
  
  // Parameter 1 = number of pixels in g_strip
  // Parameter 2 = Arduino pin number (most are valid)
  // Parameter 3 = pixel type flags, add together as needed:
  //   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
  //   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
  //   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)  "discreats"
  //   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2) "g_strips"
  #define LED_TYPE NEO_RGB
  
  Adafruit_NeoPixel g_strip[MAXSPOKES] = { Adafruit_NeoPixel(RADIUS, D1, LED_TYPE + NEO_KHZ800),
                                           Adafruit_NeoPixel(RADIUS, D2, LED_TYPE + NEO_KHZ800),
                                           Adafruit_NeoPixel(RADIUS, D3, LED_TYPE + NEO_KHZ800),
                                           Adafruit_NeoPixel(RADIUS, D4, LED_TYPE + NEO_KHZ800),
                                           Adafruit_NeoPixel(RADIUS, D5, LED_TYPE + NEO_KHZ800)};
  
  // IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
  // pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
  // and minimize distance between Arduino and first pixel.  Avoid connecting
  // on a live circuit...if you must, connect GND first.

#endif  // EFFECTS_H
