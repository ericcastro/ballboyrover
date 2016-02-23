#include <SerialCommand.h>
#include <SoftwareSerial.h>

#include <Encoder.h>
#include <L293D.h>
#include <TimerOne.h>

SoftwareSerial piSerial(8, 10); // RX, TX
SerialCommand sCmd(piSerial);

void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    
  }

  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  piSerial.begin(9600);
  piSerial.println("Hello, world?");
  
  sCmd.addCommand("ARM_ROT",arm_rotation);
 
}

void loop() // run over and over
{
  sCmd.readSerial();
  if (piSerial.available())
    Serial.write(piSerial.read());
  if (Serial.available())
    piSerial.write(Serial.read());
}


void arm_rotation()    
{
  int en; //enable
  int dir; //direction

  arg = sCmd.next(); 
  if (arg != NULL) 
  {
    en=atoi(arg);
    Serial.print("Enable: "); 
    Serial.println(en); 
    
    piSerial.print("Enable: "); 
    piSerial.print(aNumber); 
  }
  arg = sCmd.next(); 
  if (arg != NULL) 
  {
    dir=atoi(arg);
    Serial.print("Direction: "); 
    Serial.print(dir); 
    
    piSerial.print("Direction "); 
    piSerial.println(aNumber); 
  }
}
