void myDelay_setup() 
{
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

void myDelay(int time)
{
  while(time > timerCounter ){
    digitalWrite(13,HIGH); 
  }
  timerCounter=0;
}

ISR(TIMER2_COMPA_vect){ 
  timerCounter++;
}
