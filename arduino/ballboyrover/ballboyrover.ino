#include <SerialCommand.h>
#include <SoftwareSerial.h>

#include <Wire.h>
#include <Adafruit_MotorShield.h>

#include <Encoder.h>
#include <L293D.h>
#include <TimerOne.h>

Adafruit_MotorShield AFMS2 = Adafruit_MotorShield(0x62); 
Adafruit_MotorShield AFMS1 = Adafruit_MotorShield(0x61); 
Adafruit_DCMotor *motDriveRL = AFMS1.getMotor(1);
Adafruit_DCMotor *motDriveRR = AFMS1.getMotor(2);
Adafruit_DCMotor *motDriveFL = AFMS1.getMotor(3);
Adafruit_DCMotor *motDriveFR = AFMS1.getMotor(4);

Adafruit_DCMotor *motGripper = AFMS2.getMotor(1);

int motArmGripDir = RELEASE;

SoftwareSerial piSerial(8, 10); // RX, TX
SerialCommand sCmd(piSerial);

int motArmRotDir = 1;
double motArmRotSpeed = 200;
L293D motArmRotCtrl(5,A2,A3);
long motArmOldPosition  = -999;
Encoder motArmRotEnc(2, 6);

int motArmLiftDir = 1;
double motArmLiftSpeed = 200;
L293D motArmLiftCtrl(11,A0,A1);



void runMotors()
{
}

void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    
  }
  AFMS1.begin();  // create with the default frequency 1.6KHz
  AFMS2.begin();  // create with the default frequency 1.6KHz

  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  piSerial.begin(9600);
  piSerial.println("Hello, world?");
  
  sCmd.addCommand("ARM_ROT",arm_rotation);
  sCmd.addCommand("ARM_LIFT",arm_lift);
  sCmd.addCommand("ARM_GRIP",arm_grip);

  motArmRotCtrl.set(0);
  //Timer1.initialize(200000);
  //Timer1.attachInterrupt(runMotors); 
  
  motGripper->setSpeed(255);
  motGripper->run(RELEASE);

  motGripper->setSpeed(0);
  motGripper->setSpeed(0);
  motGripper->setSpeed(0);
  motGripper->setSpeed(0);
  motDriveRL->run(RELEASE);
  motDriveRR->run(RELEASE);
  motDriveFL->run(RELEASE);
  motDriveFR->run(RELEASE);
}

void loop() // run over and over
{
  sCmd.readSerial();
  
  /*long newPosition = motArmRotEnc.read();
  if (newPosition != motArmOldPosition) {
    motArmOldPosition = newPosition;
    //Serial.println(newPosition);
  }*/
  
  motGripper->run(motArmGripDir);
}
void arm_rotation()    
{
  Serial.print("ARM_ROT ");
  char *arg;
  arg = sCmd.next(); 
  if (arg != NULL) 
    motArmRotDir=atoi(arg);

  if (motArmRotDir != 0)
    motArmRotSpeed = 0.7;
  else
    motArmRotSpeed = 0.0;
  
  if (motArmRotDir < 0)
    motArmRotSpeed = -1*(1-motArmRotSpeed);
    
  Serial.println(motArmRotSpeed);
  motArmRotCtrl.set(motArmRotSpeed);
}

void arm_lift()    
{
  Serial.print("ARM_LIFT" );
  char *arg;
  arg = sCmd.next(); 
  if (arg != NULL) 
    motArmLiftDir=atoi(arg);

  if (motArmLiftDir != 0)
    motArmLiftSpeed = 0.7;
  else
    motArmLiftSpeed = 0.0;
  
  if (motArmLiftDir < 0)
    motArmLiftSpeed = -1*(1-motArmLiftSpeed);
  
  Serial.println(motArmLiftSpeed);
  motArmLiftCtrl.set(motArmLiftSpeed);
}
void arm_grip()    
{
  Serial.print("ARM_GRIP");
  char *arg;
  int dir;
  
  arg = sCmd.next(); 
  if (arg != NULL) 
    dir=atoi(arg);

  if (dir == 0)
    motArmGripDir = RELEASE;
  else if (dir > 0)
    motArmGripDir = FORWARD;
  else
    motArmGripDir = BACKWARD;
    
  Serial.println(dir);
}

