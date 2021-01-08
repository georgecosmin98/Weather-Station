#define Brightness_pin A2

void getBrightnessValue()
{
  brightness = myAnalogRead(Brightness_pin)/4;
}
