#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial XBee(2, 3); // Arduino RX, TX (XBee Dout, Din)

const int motor1pin1 = 6;
const int motor1pin2 = 7;
const int motor2pin1 = 8;
const int motor2pin2 = 9;

int armpos = 70;
int clawpos = 100;
Servo claw, arm;

void setup() {
  // put your setup code here, to run once:
  XBee.begin(9600);
  Serial.begin(9600);
  
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  
  claw.attach(12);
  arm.attach(13);  
  
  claw.write(clawpos);
  arm.write(armpos);
}

void loop() {// put your main code here, to run repeatedly:
    while(!XBee.available()){}
    char i = XBee.read();
    Serial.println(i);
      switch(i)
      {
      case '6':
        moveClawOpen();
        break;
      case '7':
        moveClawClose();
        break;
      case '5':
        Stop();
        break;
      case '1':
        driveForward();
        break;
      case '2':
        driveBackward();
        break;
      case '3':
        driveRight();
        break;
      case '4':
        driveLeft();
        break;
    }
 }


void Stop()
{
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, LOW);  
    
}
void moveArmUp()
{
   digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);     
  
  
  armpos ++;
    if (armpos > 100)
    {
      armpos = 100;
    }
    arm.write(armpos);
}
void moveArmDown()
{
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, LOW);  
     armpos --;
     if (armpos < 20)
     {
         armpos = 20;
     }
     arm.write(armpos);
}
void moveClawOpen()
{ 
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, LOW);  
    clawpos -= 3;
    if (clawpos < 0)
    {
      clawpos = 0;
    }
    claw.write(clawpos);
}
void moveClawClose()
{
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, LOW);  
    clawpos += 3;
    if (clawpos > 100)
    {
      clawpos = 100;
    }
    claw.write(clawpos);
}
void driveForward()
{
    digitalWrite(motor1pin1,LOW);
    digitalWrite(motor1pin2, HIGH);
    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
}
void driveBackward()
{
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);
}
void driveRight()
{
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);  
}
void driveLeft()
{
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW); 
}
