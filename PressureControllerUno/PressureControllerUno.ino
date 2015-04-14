/*
Arduino controller for 5 channel pressure system
establishes Serial communication with PC (first waits for "i" and then sends out "initialized...")
After that Arduino expects commands for reading 4 analog inputs that are connected to pressure sensors
The commands for reading pressure values are: a,b,c,d
The commands to set pressures are: 1..8 followed by a two byte value
We are using two 12-bit DAC MCP4728 (four channels each) to set the pressure values

*/
#include "Wire.h"
#include "mcp4728.h"

mcp4728 dac1 = mcp4728(0); // instantiate mcp4728 object, Device ID = 0
mcp4728 dac2 = mcp4728(1); // instantiate mcp4728 object, Device ID = 1

int setP;    // integer to set 

int iAnVal;  /* Variable to store the Voltage given by the pressure sensor.
              2 byte value. (10-bit ADC). This means that it will map input voltages 
              between 0 and 5 volts into integer values between 0 and 1023. */
              
byte firstByte,secondByte;
             
void setup() {
  pinMode(2, OUTPUT); // valve 1
  pinMode(3, OUTPUT); // valve 2 
  pinMode(4, OUTPUT); // valve 3
  pinMode(5, OUTPUT); // valve 4    
  pinMode(6, OUTPUT); // valve 5    
  pinMode(7, OUTPUT); // valve 6    
  pinMode(8, OUTPUT); // valve 7
  pinMode(9, OUTPUT); // valve 8
  
  digitalWrite(2, LOW);    // turn valve off
  digitalWrite(3, LOW);    // turn valve off
  digitalWrite(4, LOW);    // turn valve off
  digitalWrite(5, LOW);    // turn valve off
  digitalWrite(6, LOW);    // turn valve off
  digitalWrite(7, LOW);    // turn valve off
  digitalWrite(8, LOW);    // turn valve off
  digitalWrite(8, LOW);    // turn valve off
  
  Serial.begin(9600);
  establishContact(); // send waiting... until respone comes
//  Serial.println("before dac.begin");
  dac1.begin();
  dac2.begin();
//  Serial.println("after dac.begin");
  dac1.setVref(0, 0, 0, 0); // set to use external voltage reference (=VDD, 2.7 - 5.5V)
  dac1.setGain(0,0,0,0);
  dac2.setVref(0, 0, 0, 0); // set to use external voltage reference (=VDD, 2.7 - 5.5V)
  dac2.setGain(0,0,0,0);
  delay(100);
}

//get a Byte ###########################
int getByte(){
	int res=0;
	while(1){
		if(Serial.available() > 0){
			res=Serial.read();
			return res;
		}
	}
}

void loop() {
if (Serial.available()>0) {
  // get incoming byte
  int gByte=getByte();
  switch (gByte) {
    case 'a':
      iAnVal = analogRead(0);   // read a value from the pressure sensor
      Serial.println(iAnVal);
      break;
    case 'b':    
      iAnVal = analogRead(1);   // read a value from the pressure sensor
      Serial.println(iAnVal);
      break;
    case 'c':    
      iAnVal = analogRead(2);   // read a value from the pressure sensor
      Serial.println(iAnVal);
      break;
    case 'd':    
      iAnVal = analogRead(3);   // read a value from the pressure sensor
      Serial.println(iAnVal);
      break;
    case '1':
      firstByte=getByte();
      secondByte=getByte();
      setP=firstByte*256+secondByte;
      dac1.analogWrite(0,setP); // write to input register of a DAC. Channel 0-3, Value 0-4095
      Serial.print(firstByte);
      Serial.print(" ");
      Serial.print(secondByte);
      Serial.print(" ");
      Serial.println(setP);
      break;
    case '2':
      firstByte=getByte();
      secondByte=getByte();
      setP=firstByte*256+secondByte;
      dac1.analogWrite(1,setP); // write to input register of a DAC. Channel 0-3, Value 0-4095
      Serial.println("ok");
      break;
    case '3':
      firstByte=getByte();
      secondByte=getByte();
      setP=firstByte*256+secondByte;
      dac1.analogWrite(2,setP); // write to input register of a DAC. Channel 0-3, Value 0-4095
      Serial.println("ok");
      break;
    case '4':
      firstByte=getByte();
      secondByte=getByte();
      setP=firstByte*256+secondByte;
      dac1.analogWrite(3,setP); // write to input register of a DAC. Channel 0-3, Value 0-4095
      Serial.println("ok");
      break;
    case '5':
      firstByte=getByte();
      secondByte=getByte();
      setP=firstByte*256+secondByte;
      dac2.analogWrite(0,setP); // write to input register of a DAC. Channel 0-3, Value 0-4095
      Serial.print(firstByte);
      Serial.print(" ");
      Serial.print(secondByte);
      Serial.print(" ");
      Serial.println(setP);
      break;
    case '6':
      firstByte=getByte();
      secondByte=getByte();
      setP=firstByte*256+secondByte;
      dac2.analogWrite(1,setP); // write to input register of a DAC. Channel 0-3, Value 0-4095
      Serial.println("ok");
      break;
    case '7':
      firstByte=getByte();
      secondByte=getByte();
      setP=firstByte*256+secondByte;
      dac2.analogWrite(2,setP); // write to input register of a DAC. Channel 0-3, Value 0-4095
      Serial.println("ok");
      break;
    case '8':
      firstByte=getByte();
      secondByte=getByte();
      setP=firstByte*256+secondByte;
      dac2.analogWrite(3,setP); // write to input register of a DAC. Channel 0-3, Value 0-4095
      Serial.println("ok");
      break;
    case 'A':
      firstByte=getByte();
      if (firstByte=='0') {
          digitalWrite(2, LOW);      // turn valve off
          Serial.println("2 low");
          }
      else {
          digitalWrite(2, HIGH);     // turn valve on
          Serial.println("2 high");
           }
      break;
    case 'B':
      firstByte=getByte();
      if (firstByte=='0') {
          digitalWrite(3, LOW);      // turn valve off
          Serial.println("3 low");
          }
      else {
          digitalWrite(3, HIGH);     // turn valve on
          Serial.println("3 high");
           }
      break;
    case 'C':
      firstByte=getByte();
      if (firstByte=='0') {
          digitalWrite(4, LOW);      // turn valve off
          Serial.println("4 low");
          }
      else {
          digitalWrite(4, HIGH);     // turn valve on
          Serial.println("4 high");
           }
      break;
    case 'D':
      firstByte=getByte();
      if (firstByte=='0') {
          digitalWrite(5, LOW);      // turn valve off
          Serial.println("5 low");
          }
      else {
          digitalWrite(5, HIGH);     // turn valve on
          Serial.println("5 high");
           }
      break;
    case 'E':
      firstByte=getByte();
      if (firstByte=='0') {
          digitalWrite(6, LOW);      // turn valve off
          Serial.println("6 low");
          }
      else {
          digitalWrite(6, HIGH);     // turn valve on
          Serial.println("6 high");
           }
      break;
    case 'F':
      firstByte=getByte();
      if (firstByte=='0') {
          digitalWrite(7, LOW);      // turn valve off
          Serial.println("7 low");
          }
      else {
          digitalWrite(7, HIGH);     // turn valve on
          Serial.println("7 high");
           }
      break;
    case 'G':
      firstByte=getByte();
      if (firstByte=='0') {
          digitalWrite(8, LOW);      // turn valve off
          Serial.println("8 low");
          }
      else {
          digitalWrite(8, HIGH);     // turn valve on
          Serial.println("8 high");
           }
      break;
    case 'H':
      firstByte=getByte();
      if (firstByte=='0') {
          digitalWrite(9, LOW);      // turn valve off
          Serial.println("9 low");
          }
      else {
          digitalWrite(9, HIGH);     // turn valve on
          Serial.println("9 high");
           }
      break;
    case 'R':
    // reset all pressures
      dac1.analogWrite(0,0); // write 0
      dac1.analogWrite(1,0); // write 0
      dac1.analogWrite(2,0); // write 0
      dac1.analogWrite(3,0); // write 0
      dac2.analogWrite(0,0); // write 0
      dac2.analogWrite(1,0); // write 0
      dac2.analogWrite(2,0); // write 0
      dac2.analogWrite(3,0); // write 0
      Serial.println("ok");
      break;
    case 'V':
    // close all valves
      digitalWrite(2, LOW);    // turn valve off
      digitalWrite(3, LOW);    // turn valve off
      digitalWrite(4, LOW);    // turn valve off
      digitalWrite(5, LOW);    // turn valve off
      digitalWrite(6, LOW);    // turn valve off
      digitalWrite(7, LOW);    // turn valve off
      digitalWrite(8, LOW);    // turn valve off
      digitalWrite(9, LOW);    // turn valve off
      Serial.println("ok");
      break;
    case 'O':
    // open all valves
      digitalWrite(2, HIGH);    // turn valve off
      digitalWrite(3, HIGH);    // turn valve off
      digitalWrite(4, HIGH);    // turn valve off
      digitalWrite(5, HIGH);    // turn valve off
      digitalWrite(6, HIGH);    // turn valve off
      digitalWrite(7, HIGH);    // turn valve off
      digitalWrite(8, HIGH);    // turn valve off
      digitalWrite(9, HIGH);    // turn valve off
      Serial.println("ok");
      break;
    
    default:
      break;
      // turn all the LEDs off:
      }
 }
}

void establishContact() {
  while(1) {
    int inByte=0;
    inByte=getByte();
    if (inByte=='i') {
      Serial.println("initialized...");
      return; }
  }
}

