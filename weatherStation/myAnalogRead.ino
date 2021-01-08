int myAnalogRead(int pin)
{
  ADMUX_setup(pin);
  ADCSRA_setup();
  return ADC;
}

uint8_t pinToChannel(int pin)
{
  if((pin < 0) | ((pin > 5) & (pin < 14)) | (pin > 19))
    return 0;
  return (pin > 13) ? (pin - 14) : pin;

}

void ADMUX_setup(int pin)
{
  ADMUX |= (1 << REFS0);
  ADMUX |= pinToChannel(pin);
}

void ADCSRA_setup()
{
  delay(1);
  ADCSRA |= 1 << ADSC;
  while (bit_is_set(ADCSRA, ADSC));
}
