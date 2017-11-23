double read_Reference()
{
  // read the input on analog pin anlg_reference:
  return (analogRead(anlg_reference));
}

double read_Voltage()
{
  // read the input on analog pin anlg_voltage:
  return (analogRead(anlg_voltage));
}

double read_Current()
{
  // read the input on analog pin anlg_current:
  return (analogRead(anlg_current));
}

void voltage(void)
{  
  count = 0;
  while(count < 600)
  {
    double received_v = ((((read_Voltage() - read_Reference())*anti_gain_Voltage)- read_Reference())/1023)*5;
    double received_c = (((((read_Current() - read_Reference())*anti_gain_Current)- read_Reference())/shunt_resistor)/1023)*5;
  
   
    voltages[count] = received_v;
    currents[count] = received_c;
  
    count++;
  }
}

void calculator(void)
{
    sum_V_RMS = 0;
    sum_C_RMS = 0;
    sum_power_P = 0;
    v_Peak = 0;
    c_Peak = 0;


    for(int i=0 ; i<count ; i++)
    {
      voltages[i] > v_Peak ? : v_Peak = voltages[i];
      currents[i] > c_Peak ? : c_Peak = currents[i];
      
      sum_V_RMS = sum_V_RMS + voltages[i]*voltages[i];
      sum_C_RMS = sum_C_RMS + currents[i]*currents[i];
      
      sum_power_P = sum_power_P + voltages[i]*currents[i];

      /*
      Serial.print(voltages[i]);
      Serial.print("     ");
      Serial.print(currents[i]);
      Serial.print("     ");
      Serial.print(sum_power_P);
      Serial.print("     ");
      Serial.println(i);
      delay(10);
       */

      
    }

    v_RMS = sqrt((sum_V_RMS)/count);
    c_RMS = sqrt((sum_C_RMS)/count);

    power_S = v_RMS*c_RMS;
    power_P = sum_power_P/count;
    
      /*
    Serial.print("     ");
    Serial.print(power_S);
    Serial.print("     ");
    Serial.println(power_P);
       */
    
    

    power_Factor = power_P/power_S;
}

void power_factor_correction(void)
{
  if( !(abs(power_Factor) > 0.92 && abs(power_Factor)<1) )
  {
    if(abs(power_Factor) < 0.92)
    {
      if(relays <8)
      {
        relays++;
      }
    }
    else if(abs(power_Factor) > 1)
    {
      if(relays > 0)
      {
        relays++;
      }
    }
  }
}

void relays_action(int a)
{
  switch(a)
  {
    case 1: 
    {
      digitalWrite(relay_1, LOW);
      digitalWrite(relay_2, HIGH);
      digitalWrite(relay_3, HIGH);
      digitalWrite(relay_4, HIGH);
      digitalWrite(relay_5, HIGH);
      digitalWrite(relay_6, HIGH);
      digitalWrite(relay_7, HIGH);
      digitalWrite(relay_8, HIGH);
      break;
    }
    case 2: 
    {
      digitalWrite(relay_1, LOW);
      digitalWrite(relay_2, LOW);
      digitalWrite(relay_3, HIGH);
      digitalWrite(relay_4, HIGH);
      digitalWrite(relay_5, HIGH);
      digitalWrite(relay_6, HIGH);
      digitalWrite(relay_7, HIGH);
      digitalWrite(relay_8, HIGH);
      break;
    }
    case 3: 
    {
      digitalWrite(relay_1, LOW);
      digitalWrite(relay_2, LOW);
      digitalWrite(relay_3, LOW);
      digitalWrite(relay_4, HIGH);
      digitalWrite(relay_5, HIGH);
      digitalWrite(relay_6, HIGH);
      digitalWrite(relay_7, HIGH);
      digitalWrite(relay_8, HIGH);
      break;
    }
    case 4: 
    {
      digitalWrite(relay_1, LOW);
      digitalWrite(relay_2, LOW);
      digitalWrite(relay_3, LOW);
      digitalWrite(relay_4, LOW);
      digitalWrite(relay_5, HIGH);
      digitalWrite(relay_6, HIGH);
      digitalWrite(relay_7, HIGH);
      digitalWrite(relay_8, HIGH);
      break;
    }
    case 5: 
    {
      digitalWrite(relay_1, LOW);
      digitalWrite(relay_2, LOW);
      digitalWrite(relay_3, LOW);
      digitalWrite(relay_4, LOW);
      digitalWrite(relay_5, LOW);
      digitalWrite(relay_6, HIGH);
      digitalWrite(relay_7, HIGH);
      digitalWrite(relay_8, HIGH);
      break;
    }
    case 6: 
    {
      digitalWrite(relay_1, LOW);
      digitalWrite(relay_2, LOW);
      digitalWrite(relay_3, LOW);
      digitalWrite(relay_4, LOW);
      digitalWrite(relay_5, LOW);
      digitalWrite(relay_6, LOW);
      digitalWrite(relay_7, HIGH);
      digitalWrite(relay_8, HIGH);
      break;
    }
    case 7: 
    {
      digitalWrite(relay_1, LOW);
      digitalWrite(relay_2, LOW);
      digitalWrite(relay_3, LOW);
      digitalWrite(relay_4, LOW);
      digitalWrite(relay_5, LOW);
      digitalWrite(relay_6, LOW);
      digitalWrite(relay_7, LOW);
      digitalWrite(relay_8, HIGH);
      break;
    }
    case 8: 
    {
      digitalWrite(relay_1, LOW);
      digitalWrite(relay_2, LOW);
      digitalWrite(relay_3, LOW);
      digitalWrite(relay_4, LOW);
      digitalWrite(relay_5, LOW);
      digitalWrite(relay_6, LOW);
      digitalWrite(relay_7, LOW);
      digitalWrite(relay_8, LOW);
      break;
    }
    default: 
    {
      digitalWrite(relay_1, HIGH);
      digitalWrite(relay_2, HIGH);
      digitalWrite(relay_3, HIGH);
      digitalWrite(relay_4, HIGH);
      digitalWrite(relay_5, HIGH);
      digitalWrite(relay_6, HIGH);
      digitalWrite(relay_7, HIGH);
      digitalWrite(relay_8, HIGH);
      break;
    }
  }
}

void comunication(boolean a)
{
  if(!a)
  {
    Serial.print("?");
    Serial.print(abs(v_RMS)*10,0);
    Serial.print("&");
    Serial.print(abs(v_Peak)*10,0);
    Serial.print("&");
    Serial.print(abs(c_RMS),4);
    Serial.print("&");
    Serial.print(abs(c_Peak),4); 
    Serial.print("&");
    Serial.print(abs(power_S*10),0); 
    Serial.print("&");
    Serial.print(abs(power_P*10),0);    
    Serial.print("&");
    Serial.print(abs(power_Factor),4);     
    Serial.print("&");
    Turn(((int)relays));  
    Serial.println("!");
    delay(10); 
  }
}

boolean test()
{
  boolean a = 0;
  if( (isnan(abs(v_RMS)) ||  isnan(abs(v_Peak)) ||  isnan(abs(c_RMS)) ||  isnan(abs(c_RMS)) ||  isnan(abs(power_S)) ||  isnan(abs(power_P)) ||  isnan(abs(power_Factor))) ) 
  {
    a = 1;
  }
  return a;
}

void Turn(int a)
{
  if(a < -9)
  {
    Serial.print("0");
    Serial.print(a,DEC);
  }
  
  if(a >= -9 && a < 0)
  {
    Serial.print("00");
    Serial.print(a,DEC);
  }

  if(a >= 0 && a <= 9)
  {
    Serial.print("000");
    Serial.print(a,DEC);
  }
  if(a >= 10 && a <= 99)
  {
    Serial.print("00");
    Serial.print(a,DEC);
  }
  if(a >= 100 && a<= 999)
  {
    Serial.print("0");
    Serial.print(a,DEC);
  }
    if(a >= 1000)
  {
    Serial.print(a,DEC);
  }
}



void software_Reset() // Restarts program from beginning but does not reset the peripherals and registers
{
  if(millis()  > time_reset)
  {
    asm volatile ("  jmp 0"); 
  }
} 

