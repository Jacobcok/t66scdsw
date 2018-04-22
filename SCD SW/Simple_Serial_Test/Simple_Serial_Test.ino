#include <Wire.h>

int temp = 0;

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  Serial.println(temp);
  delay(100);
  temp++;
}

