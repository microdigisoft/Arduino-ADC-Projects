#include <Adafruit_PCF8591.h>
// Make sure that this is set to the value in volts of VCC
#define ADC_REFERENCE_VOLTAGE 5.0
Adafruit_PCF8591 pcf = Adafruit_PCF8591();
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // run ic2_scanner sketch and get the IC2 address, which is 0x27 in my case,it could be 0x3f in many cases
void setup()
{
  //init Serial port
  Serial.begin(9600);
   if (!pcf.begin()) {
    Serial.println("# Adafruit PCF8591 not found!");
    while (1)
      delay(10);
  }
  Serial.println("# Adafruit PCF8591 found");
  pcf.enableDAC(true);
  lcd.init();                      // initialize the lcd 
}

uint8_t dac_counter = 0;
void loop()
{
  // Make a triangle wave on the DAC output
  pcf.analogWrite(dac_counter);
  dac_counter = dac_counter + 10;
  Serial.print("AIN0: ");
  Serial.print(int_to_volts(pcf.analogRead(0), 8, ADC_REFERENCE_VOLTAGE));
  Serial.print("\t AIN1: ");
  Serial.print(int_to_volts(pcf.analogRead(1), 8, ADC_REFERENCE_VOLTAGE));
  Serial.print("\t AIN2: ");
  Serial.print(int_to_volts(pcf.analogRead(2), 8, ADC_REFERENCE_VOLTAGE));
  Serial.print("\t AIN3: ");
  Serial.print(int_to_volts(pcf.analogRead(3), 8, ADC_REFERENCE_VOLTAGE));
  Serial.println("");
  delay(3);
  // set cursor to first line
  lcd.setCursor(5, 0);
  lcd.backlight();
  lcd.print("Hello!");
  lcd.setCursor(1, 1);
  lcd.print("MICRODIGISOFT");
  //wait a second
  delay(10);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("ADC =");
  lcd.print(int_to_volts(pcf.analogRead(1), 8, ADC_REFERENCE_VOLTAGE));
  delay(1000);
  lcd.clear();

}
float int_to_volts(uint16_t dac_value, uint8_t bits, float logic_level) {
  return (((float)dac_value / ((1 << bits) - 1)) * logic_level);
} 
