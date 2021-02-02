double freq = 100.0;
double peltier = 80.0; // Duty cycle for the peltier
double fan = 100.0; // Duty cycle for the fan
double pump = 50.0; // Duty cycle for the pump

int aPin1 = A7;
int aPin2 = A6;
int aPin3 = A5;
int aPin4 = A4;
int aPin5 = A3;
int aPin6 = A2;
int aPin7 = A1;
int aPin8 = A0;

int aVal1 = 0;
int aVal2 = 0;
int aVal3 = 0;
int aVal4 = 0;
int aVal5 = 0;
int aVal6 = 0;
int aVal7 = 0;
int aVal8 = 0;

void setup() {
  // PWM Set-up on pin: DAC1
  REG_PMC_PCER1 |= PMC_PCER1_PID36;                     // Enable PWM
  
  REG_PIOB_ABSR |= PIO_ABSR_P16; 
  REG_PIOB_ABSR |= PIO_ABSR_P17;
  REG_PIOB_ABSR |= PIO_ABSR_P18;                        // Set PWM pin perhipheral type A or B, in this case B
  
  REG_PIOB_PDR |= PIO_PDR_P16;
  REG_PIOB_PDR |= PIO_PDR_P17;
  REG_PIOB_PDR |= PIO_PDR_P18;                          // Set PWM pin to an output
  
  REG_PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(1);      // Set the PWM clock rate to 84MHz (84MHz/1)
  
  REG_PWM_CMR0 = PWM_CMR_CPRE_CLKA;                     // Enable single slope PWM and set the clock source as CLKA
  REG_PWM_CMR3 = PWM_CMR_CPRE_CLKA;                     // Enable single slope PWM and set the clock source as CLKA
  
  REG_PWM_CPRD0 = 2100;                                  // Set the PWM frequency 84MHz/40kHz = 2100
  REG_PWM_CDTY0 = 1050;                                  // Set the PWM duty cycle 50% (2100/2=1050)

  REG_PWM_CPRD3 = 2100;                                  // Set the PWM frequency 84MHz/40kHz = 2100
  REG_PWM_CDTY3 = 1050;                                  // Set the PWM duty cycle 50% (2100/2=1050)

  
  REG_PWM_ENA = PWM_ENA_CHID0 | PWM_ENA_CHID1 | PWM_ENA_CHID2;                          // Enable the PWM channel  

  Serial.begin(115200); // open the serial port at 115200 bps:
  
  REG_PWM_CPRD0 = (int)(84.0/0.001/freq);
  REG_PWM_CPRD1 = (int)(84.0/0.001/freq);
  REG_PWM_CPRD2 = (int)(84.0/0.001/freq);
  REG_PWM_CDTY0 = (int)(84.0/0.001/freq/100.0*peltier);
  pump = constrain(pump, 0, 25.0);
  REG_PWM_CDTY1 = (int)(84.0/0.001/freq/100.0*pump);
  REG_PWM_CDTY2 = (int)(84.0/0.001/freq/100.0*fan);

  for(double i = 0; i < peltier; i++){
    REG_PWM_CDTY0 = (int)(84.0/0.001/freq/100.0*i);
    delay(10);
  }
}

void loop() {
  aVal5 = analogRead(aPin5);
  aVal6 = analogRead(aPin6);
  aVal7 = analogRead(aPin7);
  aVal8 = analogRead(aPin8);
//  aVal5 = map(analogRead(aPin5), 0, 1023, 0, 330);
//  aVal6 = map(analogRead(aPin6), 0, 1023, 0, 330);
//  aVal7 = map(analogRead(aPin7), 0, 1023, 0, 330);
//  aVal8 = map(analogRead(aPin8), 0, 1023, 0, 330);

  
  Serial.print("Temp1:");
  Serial.print(aVal5);
  Serial.print(", ");
  Serial.print("Temp2:");
  Serial.print(aVal6);
  Serial.print(", ");
  Serial.print("Temp3:");
  Serial.print(aVal7);
  Serial.print(", ");
  Serial.print("Temp4:");
  Serial.print(aVal8);
  Serial.print(", ");

  Serial.print("pump:");
  Serial.print(pump);
  Serial.print(", ");
  Serial.print("fan:");
  Serial.print(fan);
  Serial.print(", ");
  Serial.print("peltier:");
  Serial.println(peltier);
  delay(100);
  
}
