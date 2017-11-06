//Coordinator Flex Sensor Test
// Created by Shaan and Kyle
#include <SoftwareSerial.h>
 SoftwareSerial XBee(2, 3);
 int flexSensorPin = A0; //analog pin 0
 
int flexSensorPin2 = A1;
int flexSensorPin3 = A2;
int flexSensorPin4 = A3;
void setup(){
  XBee.begin(9600);
  Serial.begin(9600);
}

void loop(){
  
  int flexSensor1Reading = analogRead(flexSensorPin); 
  int flexSensorReading2 = analogRead(flexSensorPin2); 
  int flexSensorReading3 = analogRead(flexSensorPin3); 
  int flexSensorReading4 = analogRead(flexSensorPin4);
 
 
  Serial.println('1');
 
  Serial.println(flexSensor1Reading);
  
  //Serial.println ('2');
  //Serial.println(flexSensorReading2);
  
  
  //Serial.println('3');
  //Serial.println(flexSensorReading3);
  
  ///Serial.println('4');
 // Serial.println(flexSensorReading4);
 
  
    
 
  int flex0to100 = map(flexSensor1Reading, 250, 485, 0, 100);
  int flex0to1002 = map(flexSensorReading2, 250, 340, 0, 100);
  int flex0to1003 = map(flexSensorReading3, 310, 590, 0, 100);
  int flex0to1004 = map(flexSensorReading4, 300, 620, 0, 100);
  
  
  
/*
Serial.println('1');
Serial.println(flexSensor1Reading);
Serial.println(flex0to100);
  Serial.println('2');
  Serial.println(flexSensorReading2);
  Serial.println(flex0to1002);
  Serial.println('3'); 
  Serial.println(flexSensorReading3);
 Serial.println(flex0to1003);
  Serial.println('4');
  Serial.println(flexSensorReading4);
 Serial.println(flex0to1004);
 
 
 */
 
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
                      
  boolean ClawOpen =  (flex0to1004 > 0) && (flex0to1003 > 0) && 
                      (flex0to1002 <= 0) &&
                      (flex0to100 <= 0);    
  boolean ClawClose = (flex0to100 > 0) && (flex0to1002 > 0) && 
                      (flex0to1004 <= 0) &&
                      (flex0to1002 <= 0);  
        
  boolean ArmUp = (flex0to1002 > 0) && (flex0to1003 > 0) && 
                  (flex0to1004 <= 0) &&
                   (flex0to100 <= 0);  
       
  boolean ArmDown = (flex0to100 > 0) && (flex0to1004 > 0) && 
                    (flex0to1002 <= 0) &&
                     (flex0to1003 <= 0);    
   boolean Stop =   (flex0to100 > 0) && (flex0to1004 > 0) && 
                    (flex0to1002 > 0) &&
                     (flex0to1003 > 0);       
                     
   if(ClawOpen)
   {
     XBee.write("H");
     Serial.println('5');
   }
   if(ClawClose)
   {
     XBee.write("G");
     Serial.println('6');
   }
   if (ArmUp)
   {
     XBee.write("E");
     Serial.println('7');
   }
   if(ArmDown)
   {
     XBee.write("F");
     Serial.println('8');
     
   }     
    
  
  if(driveForward)
  {
    XBee.write("A");
    Serial.println('2');
  }
  
  if(driveBackward)
  {
    XBee.write("B");
    Serial.println('1');
  }
    if(driveRight)
  {
    XBee.write("C");
   // Serial.println('3');
  }
    if(driveLeft)
  {
    XBee.write("D");
    Serial.println('4');
  }
  
  if(Stop)
  {
  XBee.write("I");
  //Serial.println('9');
  }
  
  delay(100); //just here to slow down the output for easier reading
}
//sensor 1:2 sensor 2:35 sensor 3:26 sensor 4:39
//value < 70 is bent
