

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);

 // set  the preescaler of ADC:
 ADCSRA &= ~PS_128;  //clean the pre configuration of arduino librarie:
 
 // possibles values for prescaler
 // PS_16, PS_32, PS_64 or PS_128
 // ADCSRA |= PS_128; // 64 prescaler
 // ADCSRA |= PS_64; // 64 prescaler
  ADCSRA |= PS_32; // 32 prescaler
 // ADCSRA |= PS_16; // 16 prescaler

  // initialize digital pins as an output:
  pinMode(relay_1,OUTPUT);
  pinMode(relay_2,OUTPUT);
  pinMode(relay_3,OUTPUT);
  pinMode(relay_4,OUTPUT);
  pinMode(relay_5,OUTPUT);
  pinMode(relay_6,OUTPUT);
  pinMode(relay_7,OUTPUT);
  pinMode(relay_8,OUTPUT);

  // initialize digital pins an low level:
  digitalWrite(relay_1, HIGH);
  digitalWrite(relay_2, HIGH);
  digitalWrite(relay_3, HIGH);
  digitalWrite(relay_4, HIGH);
  digitalWrite(relay_5, HIGH);
  digitalWrite(relay_6, HIGH);
  digitalWrite(relay_7, HIGH);
  digitalWrite(relay_8, HIGH);
}

