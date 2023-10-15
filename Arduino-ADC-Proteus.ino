/*
  Uno       A4 (SDA), A5 (SCL)
  Mega      20 (SDA), 21 (SCL)
  Leonardo   2 (SDA),  3 (SCL)
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>// Import I2C LCD library
LiquidCrystal_I2C lcd(0x27, 16, 2); // run ic2_scanner sketch and get the IC2 address, which is 0x3f in my case,it could be 0x3f in many cases
int ADC_Value = A0;

void setup()
{
  //init Serial port
  Serial.begin(9600);
  pinMode(ADC_Value, INPUT);
  lcd.init();                      // initialize the lcd
  while (!Serial); //wait for serial port to connect - needed for Leonardo only
  //init RTC
  Serial.println("Init LCD");
}


void loop()
{

  String ADCVALUE = String(analogRead(A0)); //initializing a string and storing ADC value in it
  // set cursor to first line;
  lcd.setCursor(1, 0);
  lcd.backlight();
  lcd.print("MICRODIGISOFT:");
  lcd.setCursor(1, 1);
  lcd.print("ADC VALUE:");
  lcd.print(ADCVALUE);
}
