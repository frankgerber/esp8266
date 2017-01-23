#include "effects.h"

//void colorTest(void);


void colorTest(void)
{
byte stat = 0;
/*
    // Serial << "rainDrop" << endl;
    for(int x = 0; x<6; x++)
    {
         stat = rainDrop(x, 0x00ffffff, 100, 3);
         delayAndCheckForBreak(0);
         if(stat) return; // user terminated
         // Serial << "raindrop " << g_e_flag << endl; 
    }
*/
     // Serial << "lightning" << endl;
     for (uint8_t x = 0; x<3 ;x++)
     { 
         // Orange
         stat = colorWipe(ALL, 1, g_strip[0].Color(102 ,255 ,0),0,3); // g r b
         delayAndCheckForBreak(random(1000,10000));
         if(stat) return; // user terminated
         stat = lightning(0,10);
     }
     for (uint8_t x = 0; x<3 ;x++)
     { 
         // Purple
         stat = colorWipe(ALL, 1, g_strip[0].Color(102 , 51 , 153 ),0, 3); 
         delayAndCheckForBreak(random(1000,10000));
         if(stat) return; // user terminated
         stat = lightning(0,10);
     }      
    
    // Serial << "sparkle" << endl;
    for(uint8_t x; x<20; x++){  
        stat = colorWipe(ALL, 1, g_strip[0].Color(  random(100),random(100),random(100)), 50, 3); // Blue
        stat = sparkle(ALL, g_strip[0].Color(  200, 200, 200), 50, 3);
        delayAndCheckForBreak(0);
        if(stat) return; // user terminated
    }

    for(uint8_t y=0;y<10;y++){     
        for(int x = 0; x<5; x++)
        {
            stat = colorWipe(x, -1, g_strip[0].Color(255,   0,   0), 0, 3); // Red
            delayAndCheckForBreak(100);
            if(stat) return; // user terminated
            stat = colorWipe(x,  1, g_strip[0].Color(  0, 255,   0), 0, 3); // Green
       }
       //if(stat) return; // user terminated
    }
    
    // Serial << "rainbow" << endl;
    for(int x = 0; x<6; x++)
    {  
        stat = rainbow(ALL, 1, 1, 1); // rainbow
        stat = rainbow(ALL,-1, 1, 1); // rainbow
        stat = colorWipe(x, 1, g_strip[0].Color(  0,   0,   0), 0, 3); // OFF
        delayAndCheckForBreak(random(1000,10000));
        if(stat) return; // user terminated
    }    
    
    // Serial << "rainbowCycle" << endl;
    for(int x = 0; x<6; x++)
    {  
        stat = rainbowCycle(ALL, 1, 0, 1); // rainbow
        stat = rainbowCycle(ALL,-1, 0, 1); // rainbow
        stat = colorWipe(x, 1, g_strip[0].Color(  0,   0,   0), 0, 3); // OFF
        delayAndCheckForBreak(random(1000,10000));
        if(stat) return; // user terminated
    }

    // Serial << "theaterChase" << endl;
    for(int x = 0; x<6; x++)
    {    
        stat = theaterChase(ALL, -1, g_strip[0].Color(  255,   0,   0), 50, 3); // Red
        stat = theaterChase(ALL,  1, g_strip[0].Color(  255,   0,   0), 50, 3); // Red
        stat = colorWipe(x, -1, g_strip[0].Color(  0,   0,   0), 0, 3); // OFF
        delayAndCheckForBreak(random(1000,10000));
        if(stat) return; // user terminated
    }

    // Serial << "theaterChaseRainbow" << endl;
    for(int x = 0; x<6; x++)
    {    
        stat = theaterChaseRainbow(ALL, -1, 50, 3); // rainbow
        stat = theaterChaseRainbow(ALL, 1, 50, 3); // rainbow
        stat = colorWipe(ALL, -1, g_strip[0].Color(  0,   0,   0), 0, 3); // OFF
        delayAndCheckForBreak(random(1000,10000));
        if(stat) return; // user terminated
    }
    allOff();
    return;
}


