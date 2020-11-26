void setup() {

 //Setarea Timer/Counter Control Register A in modul CTC
  //CTC - CLEAR TIMER ON COMPARE MATCH
  //Reseteaza timerul cand ajunge la o anumita valoare care se afla in registrul OCR0A
  TCCR0A=0b00000010;  

  //Asignam valoarea 11111001 care reprezinta 249 in decimal, registrului OCR0A
  //Output Compare Register A
  //Valoarea este aleasa pentru a obtine 1ms impreuna cu prescalerul
  OCR0A=0b11111001; 
  
  //Timer/Counter Intrerrupt Mask Register
  //Activarea tratarii intreruperilor generate de temporizatorul 0
  //OCR0A genereaza o intrerupere atunci cand ajunge la valoarea 11111001 (249)
  TIMSK0=0b00000010;   //Set the interrupt request
  
  //Setam prescaler-ul la clock/64
  TCCR0B=0b00000011; 
}

void loop() {
  // put your main code here, to run repeatedly:

}
