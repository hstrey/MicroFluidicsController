/*
  Writing programmable device id (0-7)
    Because of critical timing of LDAC latch during the address write and read, 
    the library use software I2C master library just for address read and writing.
    Included modified SoftI2cMaster library is required.
    Original library is from fat16lib , http://forums.adafruit.com/viewtopic.php?f=25&t=13722

  I2C CLOCK pin (SCL) need to connected to digital pin 2.
  I2C DATA pin (SDA) need to connected to digital pin 3.
  LDAC pin need to be connected to digital pin 8.

  If you are using new chip, Device ID is 0.
  If you don't know current device ID, just run this scketch and check the serial monitor.
  Once you get current Device ID, put proper current device ID in writeAddress() command.
*/

#include "SoftI2cMaster.h"

/*
  Change the pin, if you connect them other pins
*/
#define SCL_PIN 2
#define SDA_PIN 3
#define LDACpin 8

SoftI2cMaster i2c;

void setup()
{
  Serial.begin(9600);  // initialize serial interface for readAddress()
  i2c.init(SCL_PIN, SDA_PIN); // initialize i2c interface
  pinMode(LDACpin, OUTPUT); // Set LDACpin to OUTPUT
  writeAddress(0,1);  // Write new address (current Device ID, new Device ID)
  delay(100); // wait for EEPROM writing 
  readAddress(); // Read current Device ID 
} 

void loop()
{
} 


void readAddress() {
  digitalWrite(LDACpin, HIGH);
  i2c.start(0B00000000);
  i2c.ldacwrite(0B00001100, LDACpin); // modified command for LDAC pin latch
  i2c.restart(0B11000001);
  uint8_t address = i2c.read(true);
  i2c.stop();
  int scanedAddress = (address & 0B00001110) >> 1;
  Serial.print("Scaned Address = ");
  Serial.print(scanedAddress,DEC);
  Serial.print("(");
  Serial.print(scanedAddress,BIN);
  Serial.println(")");
}

void writeAddress(int oldAddress, int newAddress) {
  digitalWrite(LDACpin, HIGH);
  i2c.start(0B11000000 | (oldAddress << 1));
  i2c.ldacwrite(0B01100001 | (oldAddress << 2), LDACpin); // modified command for LDAC pin latch
  i2c.write(0B01100010 | (newAddress << 2));
  i2c.write(0B01100011 | (newAddress << 2));
  i2c.stop();
}

