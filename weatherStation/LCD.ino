#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

void LCD_setup()
{
  lcd.init();
  lcd.backlight();
}

void LCDrefresh()
{
  LCDPrintTemperature();
  myDelay(4000);
  LCDPrintHumidity();
  myDelay(4000);
  LCDPrintPressure();
  myDelay(4000);
  LCDPrintBrightness();
  myDelay(4000);
  LCDPrintExternalTemp();
  myDelay(4000);
}

void LCDPrintTemperature()
{
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Temperatura");
  lcd.setCursor(4,1);
  lcd.print(String(temperature) + " C");
}

void LCDPrintHumidity()
{
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("Umiditate");
  lcd.setCursor(5,1);
  lcd.print(String(humidity) + "%");
}

void LCDPrintPressure()
{
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("Presiune");
  lcd.setCursor(2,1);
  lcd.print(String(pressure) + " mmHg");
}

void LCDPrintBrightness()
{
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Luminozitate");
  lcd.setCursor(5,1);
  lcd.print(String(brightness) + " lux");
}

void LCDPrintExternalTemp()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temperatura ext");
  lcd.setCursor(4,1);
  lcd.print(String(external_temp) + " C");
}
