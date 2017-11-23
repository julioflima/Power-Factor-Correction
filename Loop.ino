// the loop routine runs over and over again forever:
void loop()
{
  while(Serial.available() > 0)
  {
    voltage();
  
    calculator();
  
    comunication(test());
  
    power_factor_correction(); 
    
    relays_action(relays);
  }
  asm volatile ("  jmp 0");
}

