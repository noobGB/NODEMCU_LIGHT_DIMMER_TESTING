#include <Arduino.h>

#define Zero_Cross_Detection_input 12 // D6
#define Potentiometer_Input A0
#define Triac_Pulse_Out 4 // D2

unsigned int Triac_Pulse_MicroSec_Delay = 0;
//int Pot_Read = 0;
//added to github
void ICACHE_RAM_ATTR ACdimmer() // put this function in the instruction RAM
{
  //  Serial.println(digitalRead(Zero_Cross_Detection_input));
  //  Serial.println(analogRead(Potentiometer_Input));
  //  Serial.print("Pulse : ");
  //  Serial.println(Triac_Pulse_MicroSec_Delay);
  //Triac_Pulse_MicroSec_Delay = map(analogRead(Potentiometer_Input),0,1024,7200,200); 
  delayMicroseconds(Triac_Pulse_MicroSec_Delay); // read AD0
  digitalWrite(Triac_Pulse_Out, HIGH);
  
  // Serial.println(digitalRead(triacPulse));
  
  delayMicroseconds(80);  //delay 50 uSec on output pulse to turn on triac
  digitalWrite(Triac_Pulse_Out, LOW);
  
  // Serial.println(digitalRead(triacPulse));
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("NODEMCU started at 115200 baud rate..!!");
  pinMode(Zero_Cross_Detection_input, INPUT);
  pinMode(Potentiometer_Input, INPUT);
  pinMode(Triac_Pulse_Out, OUTPUT); 
  attachInterrupt(Zero_Cross_Detection_input, ACdimmer, RISING); // attach Interrupt at PIN Zero_Cross_Detection
}

void loop() {

    //Pot_Read = analogRead(Potentiometer_Input);
    //Serial.println(Pot_Read);
    Triac_Pulse_MicroSec_Delay = map(analogRead(Potentiometer_Input),0,1024,7200,200); 
    //Triac_Pulse_MicroSec_Delay = 10000 - Triac_Pulse_MicroSec_Delay;
    //Serial.println(digitalRead(Zero_Cross_Detection_input));
    //delay(1000);

}

