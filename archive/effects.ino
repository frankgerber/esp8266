#include "effects.h"

//void allOff(void);
//byte colorWipe(uint8_t spoke, uint32_t c, uint16_t wait, uint16_t timeOut);
//byte rainbow(uint8_t wait, uint16_t timeOut);
//byte rainbowCycle(uint16_t wait, uint16_t timeOut);
//byte theaterChase(uint32_t c, uint16_t wait, uint16_t timeOut);
//byte theaterChaseRainbow(uint16_t wait, uint16_t timeOut);
//void TimeOut_Set(uint32_t milliSec);
//byte TimeOut_Status(void); 
//uint32_t Wheel(byte WheelPos);



//void effects_setup() {
//  for (int x=0;x<SPOKES;x++){
//       g_strip[x].begin();
//        g_strip[x].setBrightness(BRIGHTNESS);
//        g_strip[x].clear();
//        g_strip[x].show();
//  }
//  return ;
//}

/*
void allOff(void){
  colorWipe(ALL,0,0,0);
  colorWipe_S(5,1,0,0,0);
}

// Fill the dots one after the other with a color
byte colorWipe(uint8_t spoke, uint32_t c, uint16_t wait, uint16_t timeOut) {

  TimeOut_Set(timeOut * 1000);
  do{
    for(uint16_t i=0; i<g_strip[0].numPixels(); i++) {
      g_strip[spoke].setPixelColor(i, c);
      g_strip[spoke].show();
      if(delayAndCheckForBreak(wait))return 1;
    }  
  }while(TimeOut_Status() == 0);
  return 0;
}

byte rainbow(uint8_t wait, uint16_t timeOut) {
  uint16_t i, j;
  
  TimeOut_Set(timeOut * 1000);
  do{
    for(j=0; j<256; j++) {
      for(i=0; i<g_strip[0].numPixels(); i++) {
        g_strip[0].setPixelColor(i, Wheel((i+j) & 255));
      }
      g_strip[0].show();
      if(delayAndCheckForBreak(wait))return 1;
    }
  }while(TimeOut_Status() == 0);
  return 0;
}

// Slightly different, this makes the rainbow equally distributed throughout
byte rainbowCycle(uint16_t wait, uint16_t timeOut) {
  uint16_t i, j;

  TimeOut_Set(timeOut * 1000);
  do{
    for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
      for(i=0; i< g_strip[0].numPixels(); i++) {
        g_strip[0].setPixelColor(i, Wheel(((i * 256 / g_strip[0].numPixels()) + j) & 255));
      }
      g_strip[0].show();
      if(delayAndCheckForBreak(wait))return 1;
    }
  }while(TimeOut_Status() == 0);
  return 0;
}

//Theatre-style crawling lights.
byte theaterChase(uint32_t c, uint16_t wait, uint16_t timeOut) 
{
  TimeOut_Set(timeOut * 1000);
  do{
    for (int j=0; j<10; j++) {  //do 10 cycles of chasing
      for (int q=0; q < 3; q++) {
        for (int i=0; i < g_strip[0].numPixels(); i=i+3) {
          g_strip[0].setPixelColor(i+q, c);    //turn every third pixel on
        }
        g_strip[0].show();
  
        if(delayAndCheckForBreak(wait))return 1;
  
        for (int i=0; i < g_strip[0].numPixels(); i=i+3) {
          g_strip[0].setPixelColor(i+q, 0);        //turn every third pixel off
        }
      }
    }
  }while(TimeOut_Status() == 0);   
  return 0;
}

//Theatre-style crawling lights with rainbow effect
byte theaterChaseRainbow(uint16_t wait, uint16_t timeOut) 
{
  TimeOut_Set(timeOut * 1000);
  do{
    for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
      for (int q=0; q < 3; q++) {
        for (int i=0; i < g_strip[0].numPixels(); i=i+3) {
          g_strip[0].setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        g_strip[0].show();
  
        if(delayAndCheckForBreak(wait))return 1;
  
        for (int i=0; i < g_strip[0].numPixels(); i=i+3) {
          g_strip[0].setPixelColor(i+q, 0);        //turn every third pixel off
        }
      }
    }
  }while(TimeOut_Status() == 0);
  return 0;
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return g_strip[0].Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return g_strip[0].Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return g_strip[0].Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
*/

//uint32_t g_TimeOut, g_TimeStamp;

//void TimeOut_Set(uint32_t milliSec)
//{
//   g_TimeOut = milliSec;
//    g_TimeStamp = millis();
//}

//byte TimeOut_Status(void)
//{  
//        if ( millis() > g_TimeOut + g_TimeStamp){ 
//          //Serial << millis() << " > " << g_TimeOut + g_TimeStamp << endl;
//          return 1;
//        }
//        else{
//          //Serial << millis() << " >> " << g_TimeOut + g_TimeStamp << endl;
//          return 0; 
//        }
//}


