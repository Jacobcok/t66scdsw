

/*******************************************************************\
| Description: This program illuminates LEDs to then be measured by | 
|   a photoresistor. Data is sent over serial. A value of 1024 = 5V |
| Author: Jacob Cok                                                 |
| Date Updated: 04/17/2018                                          |
|                                                                   |
\*******************************************************************/

//www.elegoo.com
//2016.12.9

#include <Wire.h>

int lightPin = 0;
int latchPin = 11;
int clockPin = 9;
int dataPin = 12;

int leds = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  delay(500);  
}
void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}
void loop() 
{
  int reading  = analogRead(lightPin);
  int numLEDSLit = reading / 57;  //1023 / 9 / 2
  numLEDSLit = 8;  //currently set to 8 to force all LEDs to illuminate
  leds = 0;   // no LEDs lit to start    
  for (int i = 0; i < numLEDSLit; i++)
  {
    leds = leds + (1 << i);  // sets the i'th bit
  }
  updateShiftRegister();
  Serial.println(reading);
}


