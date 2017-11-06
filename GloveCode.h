#include <SoftwareSerial.h>

SoftwareSerial XBee(2, 3); // Arduino RX, TX (XBee Dout, Din)

int flexSensorPin = A0; //analog pin 0
int flexSensorPin2 = A1;
int flexSensorPin3 = A2;
int flexSensorPin4 = A3;

void setup()
{
  // Initialize XBee Software Serial port. Make sure the baud
  // rate matches your XBee setting (9600 is default).
  XBee.begin(9600); 
  Serial.begin(9600);
}
 
void loop(){
  int flexSensorReading = analogRead(flexSensorPin); 
  int flexSensorReading2 = analogRead(flexSensorPin2); 
  int flexSensorReading3 = analogRead(flexSensorPin3); 
  int flexSensorReading4 = analogRead(flexSensorPin4);
  
  int flex0to100 = map(flexSensorReading, 210, 480, 0, 100);
  int flex0to1002 = map(flexSensorReading2, 305, 510, 0, 100);
  int flex0to1003 = map(flexSensorReading3, 350, 605, 0, 100);
  int flex0to1004 = map(flexSensorReading4, 300, 620, 0, 100);
  
  Serial.println("1");
  Serial.println(flex0to100);
  
  Serial.println("2");
  Serial.println(flex0to1002);
  
  Serial.println("3");
  Serial.println(flex0to1003);
  
  Serial.println("4");
  Serial.println(flex0to1004);  
  
 
                     
  boolean driveForward = (flex0to1002 > 0) && (flex0to1003 > 0) && 
                         (flex0to1004 > 0) &&
                         (flex0to100 <= 0);    // 1 bent -- 2,3,4 not bent 
                         
  boolean driveBackward = (flex0to100 > 0 ) && (flex0to1002 <= 0) && 
                          (flex0to1003 > 0) && (flex0to1004 > 0);    // 2 bent -- 1,3,4 not bent
                          
  boolean driveRight = (flex0to1002 > 0) &&
                       (flex0to100 > 0) && (flex0to1003 <= 0)
                        && (flex0to1004 > 0);  // 3 bent -- 1,2,4 not bent
                        
  boolean driveLeft = (flex0to1004 <= 0) && (flex0to100 > 0) 
                      && (flex0to1002 > 0) && (flex0to1003 > 0);    // 4 bent -- 1,2,3 not bent
  
  boolean Stop = (flex0to1004 > 0) && (flex0to100 > 0) 
                      && (flex0to1002 > 0) && (flex0to1003 > 0);    // 1,2,3,4 not bent                    
  
  boolean moveArmUp = (flex0to1004 > 0) && (flex0to100 <= 0) 
                      && (flex0to1002 <= 0) && (flex0to1003 > 0);    // 1,2  bent                                           
              
  boolean moveArmDown = (flex0to1004 <= 0) && (flex0to100 > 0);

   if (driveForward)
  {
    XBee.print('1');
  }
  else if (driveBackward)
  {
    XBee.print('2');
  }
  else if (driveRight)
  {
    XBee.print('3');
  }
  else if (driveLeft)
  {
    XBee.print('4');
  }
  else if (moveArmUp)
  {
    XBee.print('6');
  }
  else if (moveArmDown)
  {
    XBee.print('7');
  }
  if (Stop)
  {
    XBee.print('5');
   
  }
 
  
  driveForward = false;
  driveBackward = false;
  driveRight = false;
  driveLeft = false;  
  moveArmUp = false;
  moveArmDown = false;
  Stop = false;
}
