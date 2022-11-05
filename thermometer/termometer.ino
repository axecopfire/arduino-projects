// www.elegoo.com
// 2016.12.9

/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 8
 * LCD D4 pin to digital pin 9
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 11
 * LCD D7 pin to digital pin 12
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>
int tmpPin = 0;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void tempRead(int lineNumber)
{
  int tempReading = analogRead(tmpPin);
  double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK)) * tempK); //  Temp Kelvin
  float tempC = tempK - 273.15;                                                          // Convert Kelvin to Celcius
  float tempF = (tempC * 9.0) / 5.0 + 32.0;                                              // Convert Celcius to Fahrenheit
  /*  replaced
    float tempVolts = tempReading * 5.0 / 1024.0;
    float tempC = (tempVolts - 0.5) * 10.0;
    float tempF = tempC * 9.0 / 5.0 + 32.0;
  */

  // Display Temperature in C
  // lcd.print("Temp         C  ");
  // Display Temperature in F
  lcd.print("Temp         F  ");
  lcd.setCursor(6, lineNumber);
  // Display Temperature in C
  // lcd.print(tempC);
  // Display Temperature in F
  lcd.print(tempF);
  delay(500);
}

void helloWorldCounter()
{
  // print the number of seconds since reset:
  String helloWorldString = "Hello, World! ";
  String counter = String(millis() / 1000);
  lcd.print(String(helloWorldString + counter));
}

void loop()
{
  lcd.setCursor(0, 0);
  tempRead(0);

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  helloWorldCounter();
}
