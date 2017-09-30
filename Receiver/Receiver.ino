// Version 1.2.1
// Data is sent in a <###,###,F> format
// And then broken down into substrings and converted to integers

String DATA;
String PanningServo;
String TiltingServo;
String opCode;

int SP1;
int ST1;

const int LeftWheelPowerControl = 42;
const int LeftWheelSpeedControl = 43;
const int RightWheelPowerControl = 44;
const int RightWheelSpeedControl = 45;
const int TorsoFan = 52;

#include <Servo.h>;

Servo PanServo, TiltServo;

void setup() 
{

  PanServo.attach(9);
  TiltServo.attach(10);
  
  Serial.begin(9600);
  Serial.setTimeout(500);
  
  pinMode(LeftWheelPowerControl, OUTPUT);  //Left wheel
  pinMode(LeftWheelSpeedControl, OUTPUT);  //Left wheel
  pinMode(RightWheelPowerControl, OUTPUT);  //Right wheel
  pinMode(RightWheelSpeedControl, OUTPUT);  //Right wheel
  pinMode(TorsoFan, OUTPUT);  // Torso Fan
  
  digitalWrite(TorsoFan, HIGH);

}

void loop() 
{
  if (Serial.available() > 0)
  { 
  
  ParseData();
  
  Movement();
  
  }
}

void ParseData() 
{
  DATA = (Serial.readString());
  Serial.print(DATA);
  PanningServo = DATA.substring(1,4);
  TiltingServo = DATA.substring(5,8);
  opCode = DATA.substring(9,10);
  SP1 = PanningServo.toInt();
  ST1 = TiltingServo.toInt();
  SP1 = (SP1 - 100);
  ST1 = (ST1 - 100);
}


void Movement () 
{
  if (opCode.substring(0) == "F")
  {
    digitalWrite(LeftWheelPowerControl, HIGH);
    digitalWrite(LeftWheelSpeedControl, HIGH);
    digitalWrite(RightWheelPowerControl, HIGH);
    digitalWrite(RightWheelSpeedControl, HIGH);
    Serial.println("Robot is Moving Forward.");
    Serial.println("");
  }
  else if (opCode.substring(0) == "B")
  {
    digitalWrite(LeftWheelPowerControl, HIGH);
    digitalWrite(LeftWheelSpeedControl, LOW);
    digitalWrite(RightWheelPowerControl, HIGH);
    digitalWrite(RightWheelSpeedControl, LOW);
    Serial.println("Robot is Moving Backward.");
    Serial.println("");
  }
  else if (opCode == "L")
  {
    digitalWrite(LeftWheelPowerControl, LOW);
    digitalWrite(LeftWheelSpeedControl, LOW);
    digitalWrite(RightWheelPowerControl, HIGH);
    digitalWrite(RightWheelSpeedControl, HIGH);
    Serial.println("Robot is Turning Left.");
    Serial.println("");
  }
  else if (opCode == "R")
  {
    digitalWrite(LeftWheelPowerControl, HIGH);
    digitalWrite(LeftWheelSpeedControl, HIGH);
    digitalWrite(RightWheelPowerControl, LOW);
    digitalWrite(RightWheelSpeedControl, LOW);
    Serial.println("Robot is Turning Right.");
    Serial.println("");
  }
  else {
    digitalWrite(LeftWheelPowerControl, LOW);
    digitalWrite(LeftWheelSpeedControl, LOW);
    digitalWrite(RightWheelPowerControl, LOW);
    digitalWrite(RightWheelSpeedControl, LOW);
    Serial.println("Robot is Still.");
    Serial.println("");
  }
   
  PanServo.write(90);
  TiltServo.write(90); 
 }
