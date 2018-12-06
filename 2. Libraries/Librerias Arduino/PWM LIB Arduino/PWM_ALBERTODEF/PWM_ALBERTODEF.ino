/*
 Mimics the fade example but with an extra parameter for frequency. It should dim but with a flicker 
 because the frequency has been set low enough for the human eye to detect. This flicker is easiest to see when 
 the LED is moving with respect to the eye and when it is between about 20% - 60% brighness. The library 
 allows for a frequency range from 1Hz - 2MHz on 16 bit timers and 31Hz - 2 MHz on 8 bit timers. When 
 SetPinFrequency()/SetPinFrequencySafe() is called, a bool is returned which can be tested to verify the 
 frequency was actually changed.
  This example runs on mega and uno.
 */

#include <PWM.h>

int PinPWM = 11;             // Pin de salida PWM
int PorcentajePWM = 0;      // Porcentaje de PWM a nivel alto (0-100%)
int EnableBOMB = 7;
int32_t frequencia = 100;   //Frecuencia en Hz
bool SW1, SW2, SW3;
void setup(){
  for(int i=8; i<=10;i++)
    pinMode(i,INPUT);
  
  pinMode(PinPWM,OUTPUT);
  pinMode(EnableBOMB,OUTPUT); 
  digitalWrite(EnableBOMB,LOW); //Inicializamos el enable de la bombilla a 0
  InitTimersSafe();  //Inicializa todos los temporizadores excepto el 0, para poder utilizarlo en los delays
  
  bool success = SetPinFrequencySafe(PinPWM, frequencia);  //Fija la frecuencia al pin establecido
  if(success) {      //Si la frecuencia se fija correctamente, el LED de la placa estará siempre encendido
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);}
  Serial.begin(9600);
} //END setup

void loop(){
  SW1 = digitalRead(10);
  SW2 = digitalRead(9);
  SW3 = digitalRead(8);

  if (SW1==HIGH && SW2==LOW){ // && SW3==LOW){         //PWM 100% PARA 1A
    PorcentajePWM = 100;        
    int variablePWM = map(PorcentajePWM,0,100,0,255); //Funcion de mapeado que convierte un valor de porcentaje 0-100% a un numero proporcional de 32 bits 0-255
    pwmWrite(PinPWM,variablePWM);
    delay(50);
    digitalWrite(EnableBOMB,HIGH);}

  else if (SW1==LOW && SW2==HIGH){ // && SW3==LOW){
    PorcentajePWM = 25;        
    int variablePWM = map(PorcentajePWM,0,100,0,255);
    pwmWrite(PinPWM,variablePWM);
    delay(50);
    digitalWrite(EnableBOMB,HIGH);}
 
  else
  digitalWrite(EnableBOMB,LOW);
  
    
  Serial.print("PorcentajePWM: ");
  Serial.println(PorcentajePWM);
  delay(200);
  
  Serial.print("SW1: ");
  Serial.println(SW1);
  delay(100);
  
  Serial.print("SW2: ");
  Serial.println(SW2);
  delay(100);

 // else if (SW1==LOW && SW2==LOW && SW3==HIGH){
 //   PorcentajePWM = 55;        
 //   int variablePWM = map(PorcentajePWM,0,100,0,255);
 //   pwmWrite(PinPWM,variablePWM);
 //   delay(50);
 //   digitalWrite(EnableBOMB,HIGH);}
    
 
  
  }

