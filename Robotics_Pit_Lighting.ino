#include <DmxSimple.h>
#include <Adafruit_NeoPixel.h>
//LED STRIP PINS
int strip1Pin = 22;
int strip2Pin = 3;
int strip3Pin = 4;
int strip4Pin = 5;
int strip5Pin = 6;
int strip6Pin = 7;


//INPUT PINS
int potRPin = 0; //Red Potentiometer
int potGPin = 1; //Green Potentiometer
int potBPin = 2; //Blue Potentiometer
int preset1Pin = 7; //Preset 1 Button
int preset2Pin = 8; //Preset 2 Button
int preset3Pin = 9; //Preset 3 Button
int parSelectPin = 10; //Select PAR LEDs button
int stripSelectPin = 11; //Select LED Strips button

//VARIABLES & STUFF
int R;
int G;
int B;
String serialData;
boolean done;

//STRIP SETUP
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(60, strip1Pin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(60, strip2Pin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(60, strip3Pin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(60, strip4Pin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(60, strip5Pin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip6 = Adafruit_NeoPixel(60, strip6Pin, NEO_GRB + NEO_KHZ800);



void setup() 
{
  //Set the DMX Output Pin. Is 3 by default, but just to be sure
  DmxSimple.usePin(3);

  //Max Number of DMX Channels. If not set, will be set by the highest .write(). 
  //Using 4 lights with 1-8 each, so using 35 for wiggle room
  DmxSimple.maxChannel(35);

  //Set pin modes for buttons
  pinMode(preset1Pin, INPUT);
  pinMode(preset2Pin, INPUT);
  pinMode(preset3Pin, INPUT);
  pinMode(parSelectPin, INPUT);
  pinMode(stripSelectPin, INPUT);

  //Initialize neopixel strips
  strip1.begin();
  strip2.begin();
  strip3.begin();
  strip4.begin();
  strip5.begin();
  strip6.begin();

  //Start showing colors
  strip1.show();
  strip2.show();
  strip3.show();
  strip4.show();
  strip5.show();
  strip6.show();

  //Enable the serial port for communication with laptop
  Serial.begin(9600);
  Serial.println("Setup Executed!");
}

void loop() 
{
  //Fetch the latest RGB Values, on a 0-255 scale
  //updatePotValues();
  if(done == false)
  {
    moodLighting();
    done = true; 
    Serial.println("Done!");
  }
  
 //moodLighting();
 //lmBlue();
 rainbowCycle(0);
 //delay(5000);
 //workLighting();
 //delay(5000);
}


/**
 * Lighting presets
 */
void moodLighting()
{
  setColor(1, 0, 200, 200, 0);
  setColor(5, 0, 200, 200, 0);
  setColor(9, 0, 200, 200, 0);
  setColor(13, 0, 200, 200, 0);

  //lmBlue();
  //darkBlue();
  
}

void workLighting()
{
  setColor(1, 255, 255, 255, 0);
  setColor(5, 255, 255, 255, 0);
  setColor(9, 255, 255, 255, 0);
  setColor(13, 255, 255, 255, 0);
}

void rainbowCycle(uint8_t wait) 
{
  uint16_t i, j;
    for(j=0; j<256*5; j++) // 5 cycles of all colors on wheel
    { 
      for(i=0; i< strip1.numPixels(); i++) 
      {
        strip1.setPixelColor(i, Wheel(((i * 256 / strip1.numPixels()) + j) & 255));
        strip2.setPixelColor(i, Wheel(((i * 256 / strip2.numPixels()) + j) & 255));
        strip3.setPixelColor(i, Wheel(((i * 256 / strip3.numPixels()) + j) & 255));
        strip4.setPixelColor(i, Wheel(((i * 256 / strip4.numPixels()) + j) & 255));
        strip5.setPixelColor(i, Wheel(((i * 256 / strip5.numPixels()) + j) & 255));
        strip6.setPixelColor(i, Wheel(((i * 256 / strip6.numPixels()) + j) & 255));
      }
      strip1.show();
      strip2.show();
      strip3.show();
      strip4.show();
      strip5.show();
      strip6.show();
      delay(wait);
    }
}

void lmBlue()
{
  uint32_t colorLmBlue = strip1.Color(0, 255, 255);
  for(uint16_t i=0; i<strip1.numPixels(); i++)  
  {   
      strip1.setPixelColor(i, colorLmBlue);    
      strip2.setPixelColor(i, colorLmBlue);  
      strip3.setPixelColor(i, colorLmBlue);  
      strip4.setPixelColor(i, colorLmBlue);  
      strip5.setPixelColor(i, colorLmBlue);  
      strip6.setPixelColor(i, colorLmBlue);   
  }
  strip1.show();
  strip2.show();
  strip3.show();
  strip4.show();
  strip5.show();
  strip6.show();
}

void darkBlue()
{
  uint32_t colorDarkBlue = strip1.Color(0, 0, 255);
  for(uint16_t i=0; i<strip1.numPixels(); i++)  
  {
      strip1.setPixelColor(i, colorDarkBlue);    
      strip2.setPixelColor(i, colorDarkBlue);  
      strip3.setPixelColor(i, colorDarkBlue);  
      strip4.setPixelColor(i, colorDarkBlue);  
      strip5.setPixelColor(i, colorDarkBlue);  
      strip6.setPixelColor(i, colorDarkBlue);  
  }
}


/**
 * Functional functions that function to perform frequently functioned functions.
 * Call them if you want, see if I care
 */
 
void setColor(int f, int r, int g, int b, int u)
{
  DmxSimple.write(f, r);
  DmxSimple.write(f+1, g);
  DmxSimple.write(f+2, b);
  DmxSimple.write(f+3, u);
}

void updatePotValues()
{
  //Gets the values of the RGB potentiometers, and converts them to 255 color numbers
  int potR = analogRead(potRPin);
  int potG = analogRead(potGPin);
  int potB = analogRead(potBPin);
  int medR = potR/1023;
  int medG = potG/1023;
  int medB = potB/1023;
  R = medR * 255;
  G = medG * 255;
  B = medB * 255;
}

uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip1.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip1.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip1.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}


