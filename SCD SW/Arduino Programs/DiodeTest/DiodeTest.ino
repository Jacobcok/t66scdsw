#include <Wire.h>
#include <LIDARLite.h>

LIDARLite myLidarLite;
int temp = 0;
int reading = 0;

void setup()
{
  Serial.begin(115200); 
  myLidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz
  myLidarLite.configure(0); // Change this number to try out alternate configurations
}

void loop()
{ 
  Serial.print("Diode: ");
  Serial.print(temp);  
  Serial.print("   LIDAR: ");
  Serial.println(myLidarLite.distance());  
  
//  for(int i = 0; i < 99; i++)
//  {
//    Serial.println(myLidarLite.distance(false));
//  }
//  while (analogRead(0) < 10)
//  {
//    reading  = analogRead(0);
//  }
  reading  = analogRead(0);
  if (reading > 1) 
  {
    temp = reading;
  }

}
