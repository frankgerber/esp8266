#include "effects.h"

  //int breakDetect(void);
  //int delayAndCheckForBreak(unsigned long milliSec);
  //int wiFiFetch( );
  //void parseBuffer(String &g_restString); 
  //String printAllChrs(String strIn); 

#define ID      Serial.print("#ID FILE "); Serial.print(__FILE__); \
                Serial.print(", LINE " );  Serial.print(__LINE__); \
                Serial.print(", FUNC " );  Serial.println(__func__);

int breakDetect(void){
    // Is there a clear cmd ?
    if(g_restString.indexOf("clear") > -1){  // if index > than -1 means found "clear"
        g_restString = ""; // clear input buffer
        g_client.flush();  // clear wifi buffer          
        g_clear_flag = true;   // set escape flag 
        Serial << "#1 Clear Cmd, g_e_flag = "<< g_clear_flag  << endl; // DEBUG PRINT 
        allOff();  // LEDs OFF 
        return 1;
    }
    else{           
        // g_e_flag = false; 
        // Serial << "g_e_flag = false" << endl; 
        return 0;
    }                
}                

// used by effect function delay and early stopping
//int _delay(unsigned long milliSec) 
int delayAndCheckForBreak(unsigned long milliSec)
{  
  unsigned long start = millis();
  unsigned long time = 0; 
  int breakStatus;

    while (start + milliSec >= time){
        time = millis();
        // ID Serial << "wait = " << milliSec << endl; // DEBUG PRINT
        yield();
        wiFiFetch(); // add new wifi commands
        
        if (breakDetect()){ 
            g_clear_flag = true;
            ID Serial << "#2 breakDetected, g_e_flag = " << g_clear_flag <<  endl; // DEBUG PRINT
            return 1; // if found set g_e_flag, clear screen, clear buffer
        }
        else{
            // g_e_flag = false;  
            // ID Serial << "g_e_flag = " << g_e_flag <<  endl; // DEBUG PRINT
           // return 0; // if found set g_e_flag, clear screen, clear buffer 
        }                 
    }
    return 0;
}

int wiFiFetch(void)// wiFiFetch Buffer Producer 
{
  // Get clients coming from g_server
  //g_client = g_server.accept();
  
  // Check if a client has connected
  g_client = g_server.available();
  if (!g_client) {
    return 0;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while(!g_client.available()){
    delay(1);
  }
 
  // Is there is a new client?
  //if (g_client) {
      // Read the first line of the request
      g_restString += g_client.readStringUntil('\n'); // \r\n 0xD,0xA
      g_restString += '\n'; // add '\n'  back in 
      g_client << printAllChrs(g_restString) << endl; // DEBUG PRINT to client       
      g_clear_flag = false; // clear escape flag 
      ID Serial << "#3 Read new cmd, g_e_flag = " << g_clear_flag <<  endl; // DEBUG PRINT 
  //}     
  
  g_client.stop();
  return 0;
}

void parseBuffer(String &g_restString) 
{ 
    // Buffer Consumer
    String command ="";
    uint32_t parmColor;
    uint32_t parmSpeed;
    uint32_t parmDwell;
    // uint32_t parm4;
    uint32_t index;
  
    if (g_restString.length() == 0) 
        return; // if no cmds get out
    
    ID printAllChrs(g_restString); // DEBUG PRINT
    
    // read GET (rest g_striped this)
    index =g_restString.indexOf('/'); 
    command = g_restString.substring(0,index); 
    g_restString.remove(0,index +1); // command + '/'
    Serial << "HTTP -> " << command << endl; // DEBUG PRINT     

    // read Arduino (rest g_striped this)
    index =g_restString.indexOf('/'); 
    command = g_restString.substring(0,index); 
    g_restString.remove(0,index +1); // command + '/'
    Serial << "Arduino -> " << command << endl; // DEBUG PRINT    
      
    // read the command
    index =g_restString.indexOf('/'); 
    command = g_restString.substring(0,index); 
    g_restString.remove(0,index +1); // command + '/'
    Serial << "command -> " << command << endl; // DEBUG PRINT 
    
    //ID printAllChrs(g_restString); // DEBUG PRINT
    
    // Read parmColor Color
    index =g_restString.indexOf('/');
    parmColor = g_restString.toInt();
    g_restString.remove(0,(index+1)); // parmColor + /
    Serial << "parmColor -> " << parmColor << endl; // DEBUG PRINT

    // Read parmSpeed  delay msecs added 8/7/2016
    index =g_restString.indexOf('/');
    parmSpeed = g_restString.toInt();
    g_restString.remove(0,(index+1)); // parmSpeed + /
    Serial << "parmSpeed -> " << parmSpeed << endl; // DEBUG PRINT    
            
    // Read parmDwell time secs
    index =g_restString.indexOf('\n'); // \r\n 0xD,0xA
    parmDwell = g_restString.toInt();
    g_restString.remove (0,(index+1)); // parmDwell + '/' + \r\n
    Serial << "parmDwell -> " << parmDwell << endl ; // DEBUG PRINT
           
    //ID printAllChrs(g_restString); // DEBUG PRINT
  
    // is "colorWipe" command?
    if (command == "colorWipe") {
       // ID             color, delay               
       colorWipe(ALL, 1, parmColor, parmSpeed, parmDwell);
       //colorWipe(parmColor, parmSpeed, parmDwell);
       //colorWipe_S(ALL, 1, parmColor, parmSpeed, parmDwell);
    }
  
    // is "rainbow" command?
    else if (command == "rainbow") {
        // ID         delay
        rainbow(ALL,1,parmSpeed,parmDwell);
        //rainbow(parmSpeed, parmDwell);
    }
  
    // is "rainbowCycle" command?
    else if (command == "rainbowCycle") {
        // ID              delay, time
        rainbowCycle(ALL,1,parmSpeed,parmDwell);
        //rainbowCycle(parmSpeed, parmDwell);
    }
   
    // is "theaterChase" command?
    else if (command == "theaterChase") {
       // ID              color, delay
       theaterChase(ALL,1,parmColor, parmSpeed,parmDwell);
       //theaterChase(parmColor, parmSpeed, parmDwell);
    }
    
    // is "theaterChaseRainbow" command?
    else if (command == "theaterChaseRainbow") { 
       // ID                     delay
       theaterChaseRainbow(ALL,1,parmSpeed,parmDwell); 
       //theaterChaseRainbow(parmSpeed, parmDwell);   
    }
    
    // is "colorTest" command? Runs multable effeects
    else if (command == "colorTest") {  
        // ID  
        colorTest();   
       //effects(parmSpeed);
    }
  
    // is "clear" command?
    else if (command == "clear") {
        // ID 
         colorWipe(ALL, 1, 0, 0, 3); // OFF 
        //colorWipe(0, 0, 0); // OFF 
        //colorWipe_S(5, 1, 0, 0, 0); // OFF
    }
  
    else 
    {
        // ID
        Serial << (F("error: command not defined")) << endl;
        return;
    }   
 
}

/*
This will print out ASCII charters and \0x formated for unprintable values
Will Print to Serial Monitor
Will Return as string to function
*/
String printAllChrs(String strIn)
{
int len;
int x;
String S_temp;

  len = strIn.length();
  if (len == 0) Serial.println("NULL");
  // Serial.print("len -> "); Serial.println(len); // DEBUG PRINT 
  for(x=0;x<len;x++){
    if(strIn.charAt(x)>' ' || strIn.charAt(x)>'~'){
      Serial.print(strIn.charAt(x));
      S_temp += strIn.charAt(x);
    }
    else{
      Serial.print("\\0x"); 
      S_temp += "\\0x";
      Serial.print(strIn.charAt(x),HEX);
      S_temp += String(strIn.charAt(x),HEX);
    }      
  }
  Serial.println();
  return S_temp;
}
