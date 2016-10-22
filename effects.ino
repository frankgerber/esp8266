#include "effects.h"

	//void effects_setup();	
	//void TimeOut_Set(uint32_t milliSec)
	//byte TimeOut_Status(void)
	//void allOff(void); 
	//byte rainDrop ( int8_t spoke, uint32_t c, uint8_t wait);
	//byte sparkle ( int8_t spoke, uint32_t c, uint8_t wait);
	//byte lightning (int8_t spoke );
	//byte colorWipe(int8_t spoke, int8_t dir, uint32_t c, uint16_t wait ); 
	//byte rainbow(int8_t spoke, int8_t dir, uint16_t wait, uint16_t _time); 
	//byte rainbowCycle(int8_t spoke, int8_t dir, uint16_t wait, uint16_t _time); 
	//byte theaterChase(int8_t spoke, int8_t dir, uint32_t c, uint16_t wait); 
	//byte theaterChaseRainbow(int8_t spoke, int8_t dir , uint16_t wait); 
	//byte circleBuffer ( int8_t spoke, uint32_t * a_data, uint8_t sizeOfData, uint8_t wait );
	//uint32_t Wheel( byte WheelPos); 

void setup_effects() {
	for (int x = 0; x<SPOKES; x++) {
		g_strip[x].begin();
		g_strip[x].setBrightness(BRIGHTNESS);
		g_strip[x].clear();
		g_strip[x].show();
	}
	return;
}

uint32_t g_TimeOut, g_TimeStamp;

void TimeOut_Set(uint32_t milliSec)
{
	g_TimeOut = milliSec;
	g_TimeStamp = millis();
}

byte TimeOut_Status(void)
{
	if (millis() > g_TimeOut + g_TimeStamp) {
		//Serial << millis() << " > " << g_TimeOut + g_TimeStamp << endl;
		return 1;
	}
	else {
		//Serial << millis() << " >> " << g_TimeOut + g_TimeStamp << endl;
		return 0;
	}
}

// Fill the dots one after the other with a color
void allOff(void) 
{
  uint16_t i;
    Serial << " *allOff *" << endl; 
    for(uint8_t y=0;y<SPOKES;y++){
        for(i=0; i<g_strip[y].numPixels(); i++) {
            g_strip[y].setPixelColor(i,0);
            g_strip[y].show();
            // if(g_e_flag) return;  
        }
    }
}


byte rainDrop ( int8_t spoke, uint32_t c, uint8_t wait, uint16_t timeOut){
  uint32_t a_PatternTemp[RADIUS];
  int32_t x;
  Serial << "rainDrop" << endl;
  
  g_strip[spoke].setPixelColor(3, 0x00ffffff);
  g_strip[spoke].setPixelColor(2, 0x00c0c0c0);
  g_strip[spoke].setPixelColor(1, 0x000f0f0f);
  g_strip[spoke].setPixelColor(0, 0x000a0a0a);
      
  for(uint8_t iter=0; iter < (RADIUS * 5) ; iter++)
  {
      a_PatternTemp[0] =  g_strip[spoke].getPixelColor(RADIUS-1);     // temp save last
  
      for (x=RADIUS-1; x>0; x--)            // move rest up one
      {
          g_strip[spoke].setPixelColor(x, g_strip[spoke].getPixelColor(x-1) );
          //pixels_setPixelColor(x, g_a_PixelApp[x]);
          if ( delayAndCheckForBreak(0)) return 1;
          // if(g_e_flag) return;
		  if (TimeOut_Status() != 0)return 1;
      }
       
      g_strip[spoke].setPixelColor(0, a_PatternTemp[0] );  // replace first with temp
      g_strip[spoke].show();  // show pixel
      if ( delayAndCheckForBreak(wait)) return 1;
      // if(g_e_flag) return;
	  if (TimeOut_Status() != 0)return 1;
  }
  return 0;
}


byte sparkle ( int8_t spoke, uint32_t c, uint8_t wait, uint16_t timeOut)
{
  uint8_t strip, index;
  uint32_t pixelMemory;  
  Serial << "sparkle" << endl;   
    for (uint8_t iteration = 0; iteration < 10; iteration++)
    {
        strip=random(SPOKES);
        index=random(RADIUS);
        pixelMemory = g_strip[strip].getPixelColor(index);
        g_strip[strip].setPixelColor(index, c); // sparkle Color          
        g_strip[strip].show(); 
        delay(wait);
        g_strip[strip].setPixelColor(index, pixelMemory);
        g_strip[strip].show(); 
        if ( delayAndCheckForBreak(0)) return 1;
		if (TimeOut_Status() != 0)return 1;
    } 
    return 0; 
}


byte lightning (int8_t spoke, uint16_t timeOut)
{
  uint32_t colorMemory[RADIUS];
  Serial << "lightning" << endl;
    for ( uint8_t y=0;y<random(0,10);y++)
    {
        spoke = random(0, SPOKES);
            
        for (int x = 0;x<RADIUS;x++){
          colorMemory[x]= g_strip[spoke].getPixelColor(x);
        }
    
        for (int x=0;x<(random(0,20));x++){
            colorWipe(spoke, 1, g_strip[0].Color(255,255,255),0,3); // WHITE
            delay(random(0,100));
            colorWipe(spoke, 1, 0, 0,3); // Black   
            // delayAndCheckForBreak(random(0,500));
            if ( delayAndCheckForBreak(random(0,500))) return 1;
			if (TimeOut_Status() != 0)return 1;
        }
    
        for (int x = 0;x<RADIUS;x++){
            g_strip[spoke].setPixelColor(x,colorMemory[x])  ;
            if(delayAndCheckForBreak(0))return 1;
            //if(g_e_flag) return;
			if (TimeOut_Status() != 0)return 1;
        }
        g_strip[spoke].show();  
    }
    return 0;
}


  // One Spoke  or all Spokes
  // Fill the dots one after the other with a color
  // g_strip[1,2,3...,ALL], [1=out, -1=in,[color(0-255,0-255,0-255)], [0...255 ms]
byte colorWipe(int8_t spoke, int8_t dir, uint32_t c, uint16_t wait, uint16_t timeOut)
{  
  int8_t radiusStart, radiusFinish, spokeStart, spokeFinish, parallel, i, offsetInc, spokeInc, spokeLocal ;
  Serial << "colorWipe" << endl;

   if (dir ==  1){ radiusStart = 0;        radiusFinish = RADIUS; } 
   if (dir == -1){ radiusStart = RADIUS-1; radiusFinish = -1     ; } // 0 based
   if ( spoke >  SPOKES-1 ) { parallel = true ; spokeStart = 0;     spokeFinish = SPOKES;  } 
   if ( spoke <= SPOKES-1 ) { parallel = false; spokeStart = spoke; spokeFinish = spoke+1; }
 
   TimeOut_Set(timeOut * 1000);
   do {
      for(i=radiusStart; i != radiusFinish; i=i+dir) { // radius inc
          for (spokeInc = spokeStart ; spokeInc != spokeFinish; spokeInc++){  // spoke inc
              g_strip[spokeInc].setPixelColor(i, c);  // buffer write
              // Serial << "spoke= " << spokeInc << ", radius= " <<  i <<" color "<< c << endl;
              g_strip[spokeInc].show(); // buffer display
              if ( ! parallel ) {delayAndCheckForBreak(wait);}  
              if(g_clear_flag) return 1;   
			  if (TimeOut_Status() != 0)return 1;
          }                                                  
          if (parallel) {delayAndCheckForBreak(wait);}
          if(g_clear_flag) return 1;
		  if (TimeOut_Status() != 0)return 1;
      }
    } while (TimeOut_Status() == 0);
    return 0;
}


byte rainbow(int8_t spoke, int8_t dir, uint16_t wait, uint16_t timeOut)
{  
  int8_t radiusStart, radiusFinish, spokeStart, spokeFinish, parallel, i, offsetInc, spokeInc, spokeLocal ;
  Serial << "rainbow" << endl;  
    
    if (dir ==  1){ radiusStart = 0;        radiusFinish = RADIUS; } 
    if (dir == -1){ radiusStart = RADIUS-1; radiusFinish = -1     ; } // 0 based
    if ( spoke >  SPOKES-1 ) { parallel = true ; spokeStart = 0;     spokeFinish = SPOKES;  } 
    if ( spoke <= SPOKES-1 ) { parallel = false; spokeStart = spoke; spokeFinish = spoke+1; }

	TimeOut_Set(timeOut * 1000);
	do {
		//for(uint16_t x=0; x<_time; x++){
		  for(uint16_t j=0; j<256; j++) {  // interation
			  for(i=radiusStart; i != radiusFinish; i=i+dir) { // radius inc
				  for (spokeInc = spokeStart ; spokeInc != spokeFinish; spokeInc++){  // spoke inc
					  g_strip[spokeInc].setPixelColor(i, Wheel((i+j) & 255));  // buffer write
					  g_strip[spokeInc].show(); // buffer display
					  if ( ! parallel ) {delayAndCheckForBreak(wait);}
					  if(g_clear_flag) return 1;
					  if (TimeOut_Status() != 0)return 1;
				  }                                                  
				  if (parallel) {delayAndCheckForBreak(wait);}
				  if(g_clear_flag) return 1;
				  if (TimeOut_Status() != 0)return 1;
			  }
		  }
		//}
	} while (TimeOut_Status() == 0);
    return 0;      
}


// Slightly different, this makes the rainbow equally distributed throughout
byte rainbowCycle(int8_t spoke, int8_t dir, uint16_t wait, uint16_t timeOut)
{  
  uint32_t c;
  int8_t radiusStart, radiusFinish, spokeStart, spokeFinish, parallel, i, offsetInc, spokeInc, spokeLocal ;
  Serial << "rainbowCycle" << endl;  
    
  if (dir ==  1){ radiusStart = 0;        radiusFinish = RADIUS; } 
  if (dir == -1){ radiusStart = RADIUS-1; radiusFinish = -1     ; } // 0 based
  if ( spoke >  SPOKES-1 ) { parallel = true ; spokeStart = 0;     spokeFinish = SPOKES;  } 
  if ( spoke <= SPOKES-1 ) { parallel = false; spokeStart = spoke; spokeFinish = spoke+1; }
  TimeOut_Set(timeOut * 1000);
  do {
	  //for(uint16_t x=0; x<_time; x++){
		for(uint16_t j=0; j<256; j+=10) {  // once thru the rainbow
		  for(i=radiusStart; i != radiusFinish; i=i+dir) { // radius inc
			  for (spokeInc = spokeStart ; spokeInc != spokeFinish; spokeInc++){  // spoke inc
				  c = Wheel(((i * 256 / g_strip[spokeInc].numPixels()) + j) & 255);  // c = Effect
				  //Serial << "spoke= " << spokeInc << ", radius= " <<  i <<" color "<< c << endl;
				  g_strip[spokeInc].setPixelColor(i, c);  // buffer write
				  g_strip[spokeInc].show(); // buffer display
				  if ( ! parallel ) {delayAndCheckForBreak(wait);} 
				  if(g_clear_flag) return 1;   
				  if (TimeOut_Status() != 0)return 1;
			  }                                                  
			  if (parallel) {delayAndCheckForBreak(wait);}
			  if(g_clear_flag) return 1;
			  if (TimeOut_Status() != 0)return 1;
		  }
		}
	  //}
  } while (TimeOut_Status() == 0);
  return 0;
}


byte theaterChase(int8_t spoke, int8_t dir, uint32_t c, uint16_t wait, uint16_t timeOut)
{  
  int8_t offsetStart, offsetFinish, radiusStart, radiusFinish, spokeStart, spokeFinish, 
  parallel, radiusInc, offsetInc, spokeInc, spokeLocal ;
  Serial << "theaterChase" << endl;     

  if (dir ==  1){ offsetStart=0; offsetFinish= 3;   radiusStart = 0;        radiusFinish = RADIUS; } 
  if (dir == -1){ offsetStart=2; offsetFinish=-1;   radiusStart = 0 /*RADIUS-1*/; radiusFinish = RADIUS /*-1*/; } // 0 based
  if ( spoke >  SPOKES-1 ) { parallel = true ; spokeStart = 0;     spokeFinish = SPOKES;  } 
  if ( spoke <= SPOKES-1 ) { parallel = false; spokeStart = spoke; spokeFinish = spoke+1; }

  TimeOut_Set(timeOut * 1000);
  do {
    for (int j=0; j < 5; j++) {          // itereration inc
        for ( offsetInc = offsetStart; offsetInc != offsetFinish; offsetInc=offsetInc+dir) {   // radius base inc 1, 2, 3
            for(radiusInc = radiusStart; radiusInc < radiusFinish; radiusInc = radiusInc + 3) {             // radius inc
                for (spokeInc = spokeStart ; spokeInc != spokeFinish; spokeInc++){ // spoke inc
                    // Serial << "spoke= " << spokeInc << ", radius= " <<  radiusInc << "+" << offsetInc <<" color "<< c << endl;
                    g_strip[spokeInc].setPixelColor(radiusInc + offsetInc, c);  // buffer write
                    g_strip[spokeInc].show(); // buffer display
                    //if ( ! parallel ) delayAndCheckForBreak(wait); // made uneven display
                    //if(g_e_flag) return 1;                         
                } 
            //if (parallel) delayAndCheckForBreak(wait); // made uneven display
            //if(g_e_flag) return 1;                                                           
            }        
            delayAndCheckForBreak(wait); 		
            if(g_clear_flag) return 1; 
            if (TimeOut_Status() != 0)return 1;
			if (TimeOut_Status() != 0)return 1;

            for (spokeInc = spokeStart ; spokeInc != spokeFinish; spokeInc++){  // spoke incSPOKES
                for(radiusInc = radiusStart; radiusInc < radiusFinish; radiusInc=radiusInc + 3)  // radius inc 
                    g_strip[spokeInc].setPixelColor(radiusInc + offsetInc, 0);  //Buffer every third pixel OFF (Clear)
            }
        }
    }
  } while (TimeOut_Status() == 0);
    return 0;
}


// Slightly different, this makes the rainbow equally distributed throughout
byte theaterChaseRainbow(int8_t spoke, int8_t dir , uint16_t wait, uint16_t timeOut)
{  
  int8_t offsetStart, offsetFinish, radiusStart, radiusFinish, spokeStart, spokeFinish, 
  parallel, radiusInc, offsetInc, spokeInc, spokeLocal ;
  uint32_t c;
  Serial << "theaterChaseRainbow" << endl; 
       
    if (dir ==  1){ offsetStart=0; offsetFinish= 3; radiusStart = 0;        radiusFinish = RADIUS; } 
    if (dir == -1){ offsetStart=2; offsetFinish=-1;   radiusStart = 0 /*RADIUS-1*/; radiusFinish = RADIUS /*-1*/; } // 0 based
    if ( spoke >  SPOKES-1 ) { parallel = true ; spokeStart = 0;     spokeFinish = SPOKES;  } 
    if ( spoke <= SPOKES-1 ) { parallel = false; spokeStart = spoke; spokeFinish = spoke+1; }
	TimeOut_Set(timeOut * 1000);
	do {
		for (int j=0; j < 256; j+=10) {          // itereration inc
			for ( offsetInc = offsetStart; offsetInc != offsetFinish; offsetInc=offsetInc+dir) {   // radius offset inc 1, 2, 3
				for(radiusInc = radiusStart; radiusInc < radiusFinish; radiusInc = radiusInc + 3) {             // radius inc
					for (spokeInc = spokeStart; spokeInc != spokeFinish; spokeInc++){ // spoke inc
						c = Wheel(((radiusInc* 256 / g_strip[spokeInc].numPixels()) + j) & 255);  // c = Effect
						// Serial << "spoke= " << spokeInc << ", radius= " <<  radiusInc<<" color "<< c << endl;
						g_strip[spokeInc].setPixelColor(radiusInc + offsetInc, c);  // buffer write
						g_strip[spokeInc].show(); // buffer display  // made uneven display
						// if ( ! parallel ) {delayAndCheckForBreak(wait);} 
						// if(g_e_flag) return 1;
                                              
					} 
				// if (parallel) {delayAndCheckForBreak(wait);}  // made uneven display
				// if(g_e_flag) return 1;                                                          
				}   
				delayAndCheckForBreak(wait);
				if (g_clear_flag) return 1;
				if (TimeOut_Status() != 0)return 1;
            
				// erase last pixel ON state      
				for (spokeInc = spokeStart ; spokeInc != spokeFinish; spokeInc++){  // spoke inc
					for(radiusInc = radiusStart; radiusInc < radiusFinish; radiusInc = radiusInc + 3)  // radius inc 
						g_strip[spokeInc].setPixelColor( radiusInc + offsetInc, 0);  // Buffer write every third pixel OFF (Clear)
				}
			}
		}
	} while (TimeOut_Status() == 0);
	return 0;
}


// Buffer is larger than display window to allow data to scroll on and scroll off
byte circleBuffer ( int8_t spoke, uint32_t * a_data, const uint8_t sizeOfData, uint8_t wait, uint16_t timeOut){

    uint32_t a_buffer[RADIUS + 2 * sizeOfData] , tempLast, tempFirst;
    // init a_buffer
    memset(a_buffer,0,(RADIUS + 2 * sizeOfData)*4); // clear buffer bytes
   
    // load front with data
    for (uint8_t x = 0; x < sizeOfData; x++){
        a_buffer[x] = a_data[x];     
    }
	TimeOut_Set(timeOut * 1000);
	do {
		for (uint8_t y=0; y<RADIUS+sizeOfData; y++){ // display and shift onnce though entire sequence
			for (uint8_t x = 0; x < RADIUS ; x++){
				g_strip[spoke].setPixelColor(x, a_buffer[sizeOfData + x]);  // set buffer
				g_strip[spoke].show();
				delay(wait);
			}           
			//  shift entire data one to the right
			tempLast = a_buffer[RADIUS + 2* sizeOfData]; // save last
			for (uint8_t x = 0; x < RADIUS + (2* sizeOfData)-1; x++){ // shift to right
				a_buffer[x]= a_buffer[x+1];
			}
			a_buffer[0] = tempLast; // first <- last   
		}
	} while (TimeOut_Status() == 0);
    return 0;
} // END circleBuffer()


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel( byte WheelPos) {
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


