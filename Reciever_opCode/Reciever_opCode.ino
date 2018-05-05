// Version 1.3.3
// Data is sent in a <###,###,F> format
// And then broken down into substrings and converted to integers
// LOW = Forward / HIGH = Backward
// Do not use in its current state. It hasp a high probability of killing the motors

String DATA;
String opCode;

int LWSCN = 90;
int RWSCN = 90;

const int LeftWheelPowerControl = 8;
const int LeftWheelSpeedControl = 7;
const int RightWheelPowerControl = 6;
const int RightWheelSpeedControl = 9;

void setup() 
{

  //PanServo.attach(9);
  //TiltServo.attach(10);
  
  Serial.begin(9600);
  Serial.setTimeout(20);
  
  pinMode(LeftWheelPowerControl, OUTPUT);  //Left wheel
  pinMode(LeftWheelSpeedControl, OUTPUT);  //Left wheel
  pinMode(RightWheelPowerControl, OUTPUT);  //Right wheel
  pinMode(RightWheelSpeedControl, OUTPUT);  //Right wheel
  
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
  opCode = DATA.substring(9,10);
}


void Movement () 
{    
  if (opCode == "F")
  {
    digitalWrite(LeftWheelPowerControl, LOW);
    digitalWrite(LeftWheelSpeedControl, LOW);
    analogWrite(RightWheelPowerControl, LWSCN);
    analogWrite(RightWheelSpeedControl, RWSCN);
  }
  else if (opCode == "B")
  {
    digitalWrite(LeftWheelPowerControl, HIGH);
    digitalWrite(LeftWheelSpeedControl, HIGH);
    analogWrite(RightWheelPowerControl, LWSCN);
    analogWrite(RightWheelSpeedControl, RWSCN);
  }
  else if (opCode == "L")
  {
    digitalWrite(LeftWheelPowerControl, LOW);
    digitalWrite(LeftWheelSpeedControl, HIGH);
    analogWrite(RightWheelPowerControl, LWSCN);
    analogWrite(RightWheelSpeedControl, RWSCN);
  }
  else if (opCode == "R")
  {
    digitalWrite(LeftWheelPowerControl, HIGH);
    digitalWrite(LeftWheelSpeedControl, LOW);
    analogWrite(RightWheelPowerControl, LWSCN);
    analogWrite(RightWheelSpeedControl, RWSCN);
  }
  else if (opCode == "N")
  {
    digitalWrite(LeftWheelPowerControl, LOW);
    digitalWrite(LeftWheelSpeedControl, LOW);
    digitalWrite(RightWheelPowerControl, LOW);
    digitalWrite(RightWheelSpeedControl, LOW);
  }
 }
