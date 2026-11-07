
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define ADC_PIN A0

int adcValue = 0;
float percentage = 0.0;

void setup()
{
  Wire.begin();

  pinMode(ADC_PIN, INPUT);
  analogReference(DEFAULT);

  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop()
{
  // Read ADC
  adcValue = analogRead(ADC_PIN);

  // Calculate percentage
  percentage = ((float)adcValue / 1023.0) * 100.0;

  // Display raw ADC value
  lcd.setCursor(0, 0);
  lcd.print("ADC: ");
  lcd.print(adcValue);
  lcd.print("      ");

  // Display percentage
  lcd.setCursor(0, 1);
  lcd.print("Percentage: ");
  lcd.print(percentage, 1);
  lcd.print("%   ");

  delay(200);
}
