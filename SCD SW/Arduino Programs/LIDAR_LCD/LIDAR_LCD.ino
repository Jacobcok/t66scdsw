/*------------------------------------------------------------------------------
| SCD Team 66                                                                   |      
| Latest Update: 4/3/2018                                                       |
|                                                                               |
| Current issues that are present with program:                                 |
|   - doesn't account for non-linearity for distances under 1 meter             |
|   - entire screen refresh is noticeable when distances are below              |
|     and above 1 meter                                                         |
------------------------------------------------------------------------------*/




/*------------------------------------------------------------------------------

  LIDARLite Arduino Library
  GetDistanceI2c

  This example shows how to initialize, configure, and read distance from a
  LIDAR-Lite connected over the I2C interface.

  Connections:
  LIDAR-Lite 5 Vdc (red) to Arduino 5v
  LIDAR-Lite I2C SCL (green) to Arduino SCL
  LIDAR-Lite I2C SDA (blue) to Arduino SDA
  LIDAR-Lite Ground (black) to Arduino GND
  
  (Capacitor recommended to mitigate inrush current when device is enabled)
  680uF capacitor (+) to Arduino 5v
  680uF capacitor (-) to Arduino GND

  See the Operation Manual for wiring diagrams and more information:
  http://static.garmin.com/pumac/LIDAR_Lite_v3_Operation_Manual_and_Technical_Specifications.pdf

------------------------------------------------------------------------------*/

#include <Wire.h>
#include <LIDARLite.h>
#include <LiquidCrystal.h>

LIDARLite myLidarLite;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup()
{
  Serial.begin(115200); // Initialize serial connection to display distance readings

  /*
    begin(int configuration, bool fasti2c, char lidarliteAddress)

    Starts the sensor and I2C.

    Parameters
    ----------------------------------------------------------------------------
    configuration: Default 0. Selects one of several preset configurations.
    fasti2c: Default 100 kHz. I2C base frequency.
      If true I2C frequency is set to 400kHz.
    lidarliteAddress: Default 0x62. Fill in new address here if changed. See
      operating manual for instructions.
  */
  myLidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz

  /*
    configure(int configuration, char lidarliteAddress)

    Selects one of several preset configurations.

    Parameters
    ----------------------------------------------------------------------------
    configuration:  Default 0.
      0: Default mode, balanced performance.
      1: Short range, high speed. Uses 0x1d maximum acquisition count.
      2: Default range, higher speed short range. Turns on quick termination
          detection for faster measurements at short range (with decreased
          accuracy)
      3: Maximum range. Uses 0xff maximum acquisition count.
      4: High sensitivity detection. Overrides default valid measurement detection
          algorithm, and uses a threshold value for high sensitivity and noise.
      5: Low sensitivity detection. Overrides default valid measurement detection
          algorithm, and uses a threshold value for low sensitivity and noise.
    lidarliteAddress: Default 0x62. Fill in new address here if changed. See
      operating manual for instructions.
  */
  myLidarLite.configure(0); // Change this number to try out alternate configurations

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print("Distance (cm): ");
}

void loop()
{
  /*
    distance(bool biasCorrection, char lidarliteAddress)

    Take a distance measurement and read the result.

    Parameters
    ----------------------------------------------------------------------------
    biasCorrection: Default true. Take aquisition with receiver bias
      correction. If set to false measurements will be faster. Receiver bias
      correction must be performed periodically. (e.g. 1 out of every 100
      readings).
    lidarliteAddress: Default 0x62. Fill in new address here if changed. See
      operating manual for instructions.
  */

  // Take a measurement with receiver bias correction and print to serial terminal
  Serial.println(myLidarLite.distance());

  // Take 99 measurements without receiver bias correction and print to serial terminal
  for(int i = 0; i < 99; i++)
  {
    Serial.println(myLidarLite.distance(false));
  }
  

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(1, 1);

  int tempData = (int)(myLidarLite.distance()); 
  
  //needed so LCD only displays relevant digits. *non-linearity exists when dist < 1meter.
  if (tempData < 100) {
    //clears the entire LCD screen
    lcd.begin(16,2);
    //reprint first line. 
    lcd.print("Distance (cm):");
    //data offset by 1 slot
    lcd.setCursor(2,1);
  }  
  
  //needed so LCD displays relevant digits. *non-linearity exists when dist < 1meter.
  if (tempData > 999) {
    //clears the entire LCD screen
    lcd.begin(16,2);
    //reprint first line
    lcd.print("Distance (cm):");
    //data offset by 1 slot
    lcd.setCursor(1,1);
  }

  lcd.print(tempData);
}
