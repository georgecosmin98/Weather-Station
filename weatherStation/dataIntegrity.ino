boolean verifyDataIntegrity()
{
  if( (temperature < 0) || (temperature > 50) )
    return false;
  if( (humidity < 20) || (humidity > 90) )
    return false;
  if( (brightness < 0) || (brightness > 255) )
    return false;
  if( (pressure < 225) || (pressure > 825) )
    return false;
  if ( (external_temp < -55) || (external_temp > 125) )
    return false;
  return true;
}
