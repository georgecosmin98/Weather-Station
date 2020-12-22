#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

void LCD_setup()
{
  lcd.init();
}
void LCDrefresh()
{
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("T:" + String(temperature) + "dC " + "B:" + String(brightness) + "lux");
  lcd.setCursor(0,1);
  lcd.print("H:" + String(humidity) + "%  " + "P:" + String(pressure) + "hPa");
}
