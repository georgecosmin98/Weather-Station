#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//Variabile pentru ESP8266 
String ssid     = "Simulator Wifi";    // SSID 
String password = "";           //WiFi-ul virtual nu are o parola prestabilita in ThinkerCAD
String host     = "api.thingspeak.com"; //API
const int httpPort   = 80;        //Portul pe care se trimit datele
String tempURL     = "/update?api_key=ZOPP08IZU17W667D&field1=0"; 
String lightURL    = "/update?api_key=ZOPP08IZU17W667D&field2=0";

//Contorul pentru secunda
volatile int timerCounter = 0;

int setupESP8266(void) {
  //Pornirea comunicatiei seriale pe ESP8266
  Serial.begin(115200);  
  Serial.println("AT");   
  delay(10);
  if (!Serial.find("OK")) return 1;
    
  // Conectarea circuitului la WiFI prin SSID si parola
  Serial.println("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"");
  delay(10);        //Adaugam un delay pentru ca ESP8266 sa aiba timp sa raspunda
  if (!Serial.find("OK")) return 2;
  
  //Deschiderea conexiunii TCP la gazda
  Serial.println("AT+CIPSTART=\"TCP\",\"" + host + "\"," + httpPort);
  delay(50);        //Adaugam un delay pentru ca ESP8266 sa aiba timp sa raspunda
  if (!Serial.find("OK")) return 3;
  
  return 0;
}

int readTemp(void) {
  myDelay(20000);
  int temp = map(analogRead(A0),20,358,-40,125);
  sendDataToThingSpeak(tempURL,temp);
  return temp;
}

void sendDataToThingSpeak(String URL, int value){
  // Construire call/request HTTP
  String httpPacket = "GET " + URL + String(value) + " HTTP/1.1\r\nHost: " + host + "\r\n\r\n";
  int length = httpPacket.length();
  
  // Trimitem lungimea mesajului
  Serial.print("AT+CIPSEND=");
  Serial.println(length);
  myDelay(10); //Adaugam un delay pentru ca ESP8266 sa aiba timp sa raspunda
  // if(!Serial.find(">")) return -1;

  // Trimitem request-ul HTTP 
  Serial.print(httpPacket);
  myDelay(10); //Adaugam un delay pentru ca ESP8266 sa aiba timp sa raspunda
  if (!Serial.find("SEND OK\r\n")) return;
}

void setupTIMMER2(void){
  //Setarea Timer/Counter Control Register A in modul CTC
  //CTC - CLEAR TIMER ON COMPARE MATCH
  //Reseteaza timerul cand ajunge la o anumita valoare care se afla in registrul OCR2A
    TCCR2A=0b00000010;  

  //Asignam valoarea 11111001 care reprezinta 249 in decimal, registrului OCR2A
  //Output Compare Register A
  //Valoarea este aleasa pentru a obtine 1ms impreuna cu prescalerul
    OCR2A=0b11111001; 
  
  //Timer/Counter Intrerrupt Mask Register
  //Activarea tratarii intreruperilor generate de temporizatorul 0
  //OCR2A genereaza o intrerupere atunci cand ajunge la valoarea 11111001 (249)
    TIMSK2=0b00000010;   //Set the interrupt request
  
  //Setam prescaler-ul la clock/64
    TCCR2B=0b00000100; 
  }

void setupLCD(){
  lcd.begin(16, 2);
    lcd.setCursor(2, 0);
    //Afisam temperatura
    lcd.print("Initializare");
}

void setup() {
  setupESP8266();
  setupTIMMER2();  
  pinMode(13, OUTPUT);  
  setupLCD();
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
}

//Implementarea proprie pentru functie de delay
//Timpul este reprezentat in ms!
void myDelay (int time){
  while(time > timerCounter ){
    digitalWrite(13,HIGH); 
  }
  timerCounter=0;
}

int light(){
  myDelay(20000);
  int light=analogRead(A1);
  light/=100;
  sendDataToThingSpeak(lightURL,light);
  return light;
}

void printOnLCD(int temp, int light){
  
  //Curatam display-ul  
  lcd.clear();
  //Pozitionam cursorul pe prima linie si a doua coloana
  lcd.setCursor(1, 0);
  //Afisam temperatura
  lcd.print("Temp: ");
  lcd.print(temp);
  //Pozitionam cursorul pe a doua linie si a doua coloana
  lcd.setCursor(1, 1);
  //Afisam indexul iluminarii ambientale
  lcd.print("Light: ");
  lcd.print(light);
}

void loop() {
 //Serial.println("Am intrat din loop");
 //int temp1 = readTemp();
 //ThingSpeak varianta free suport un update la fiecare
 //15 secunde, de aceea am pus un delay mai mare intre fiecare 
 //request de update catre ThingSpeak
 //delay(20000);
 //int light1 = light();
 //delay(20000);
 printOnLCD(readTemp(),light());
 //myDelay(10000);
 digitalWrite(13,LOW); 
 //Serial.println("Am iesit din loop");
}

//Cand apare o cerere de intrerupere, timerCounter se incrementeaza
//Timer/Counter2 Compare Match A (Vectorul numarul 15)
ISR(TIMER2_COMPA_vect){ 
  timerCounter++;
}
