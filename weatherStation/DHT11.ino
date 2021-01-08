#define DHT_pin 8

int temp = 0;
int tempComma = 0;
bool dhtError = false; // Checksum Error

void getDHTvalue()
{
  pinMode(DHT_pin,OUTPUT); 
  digitalWrite(DHT_pin,HIGH);
  delay(250);                   //Asteptam 250ms
  digitalWrite(DHT_pin,LOW);
  delay(30);                   //Asteptam 30ms
  digitalWrite(DHT_pin,HIGH);
  delayMicroseconds(50);        //Asteptam 50us
  pinMode(DHT_pin,INPUT); 
  recept_data_from_dht11();
  pinMode(DHT_pin,OUTPUT);
  digitalWrite(DHT_pin,HIGH);   //Asteptam un nou bit de start
}

void recept_data_from_dht11()
{
  bool BlockDHT=false;
  long int DataTime = 0;
  byte Result[45];
  byte DataArray = 0;
  byte DataCounter = 0;
  byte DHTData[4];
  
  do 
  {
     if(digitalRead(DHT_pin) == 0 && BlockDHT == false)
     {
       BlockDHT = true;
       Result[DataArray]=(micros()-DataTime);
       DataArray++;
       DataTime=micros();
     }    //Daca DHT sta in 0, citeste noul set de date
    if(digitalRead(DHT_pin) == 1)
       BlockDHT = false;     //Cat timp DHT sta in 1, adaugam timpul in us in                                        //Result
  }while((micros()-DataTime) < 150); //Daca DHT sta in 1 mai mult de
                                     //150us, paraseste bucla

  // Scrie in vectorul Result 1 daca valoarea este mai mare de 90us 
  // (timpul care sta in 0 + timpul care sta in 1 => 50us + 28us = 78us)
  // Primele doua date primite sunt eronate, asa ca le vom ignora
   for (int  i=2; i< DataArray; i++) 
   {
     if (Result[i] <= 90) 
       Result[i]=0; 
     else 
       Result[i]=1;
   }

  for (int  j=0; j< 5; j++)
  {    
    for (int  i=0; i< 8; i++)
      bitWrite(DHTData[j], 7-i, Result[i+2+(j*8)]);  // Din cei 40 de biti formam 5 bytes
  }
  
  // Verificarea corectitudinii datelor/checksum                            
  if (DHTData[4] == (DHTData[0]+DHTData[1]+DHTData[2]+DHTData[3]))
  {
    humidity = DHTData[0];
    temp = DHTData[2];
    tempComma = DHTData[3];
    temperature = temp + toDecimal(tempComma);
    dhtError = false;} 
    else dhtError = true; //Daca checksum-ul este gresit, 
                    //DHTError va semnala eroarea (
                    //Suma Dataset 0-3 = Dataset 4 => Checksum OK)
}

double toDecimal(int number)
{
  int temp = number;
  int count = 0;
  String aux, result; 
  while(temp)
  {
    aux += String(temp%10);
    temp /= 10;
  }
  aux += '.';
  aux += '0';
  for(int i = aux.length()-1; i >= 0; i--)
     result += aux[i];
  return result.toDouble();
}
