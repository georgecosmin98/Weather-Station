#define Brightness_pin A1

void getBrightnessValue()
{
  brightness = analogRead(Brightness_pin)/4;
}
