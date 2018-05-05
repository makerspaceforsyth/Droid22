// Version 1.3.3
// Data is sent in a <###,###,F> format
// And then broken down into substrings and converted to integers
// LOW = Forward / HIGH = Backward
// Do not use in its current state. It hasp a high probability of killing the motors

String DATA;
String opCode;

int LWSCN = 130;
int RWSCN = 130;

const int LeftWheelDirectionControl = 6;
const int RightWheelDirectionControl = 7;
const int LeftWheelSpeedControl = 8;
const int RightWheelSpeedControl = 9;

void setup() 
{

  //PanServo.attach(9);
  //TiltServo.attach(10);
  
  Serial.begin(9600);
  Serial.setTimeout(20);
  
  pinMode(LeftWheelDirectionControl, OUTPUT);  //Left wheel
  pinMode(RightWheelDirectionControl, OUTPUT);  //Left wheel
  pinMode(LeftWheelSpeedControl, OUTPUT);  //Right wheel
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
    digitalWrite(LeftWheelDirectionControl, LOW);
    digitalWrite(RightWheelDirectionControl, LOW);
    analogWrite(LeftWheelSpeedControl, LWSCN);
    analogWrite(RightWheelSpeedControl, RWSCN);
  }
  else if (opCode == "B")
  {
    digitalWrite(LeftWheelDirectionControl, HIGH);
    digitalWrite(RightWheelDirectionControl, HIGH);
    analogWrite(LeftWheelSpeedControl, LWSCN);
    analogWrite(RightWheelSpeedControl, RWSCN);
  }
  else if (opCode == "L")
  {
    digitalWrite(LeftWheelDirectionControl, LOW);
    digitalWrite(RightWheelDirectionControl, HIGH);
    analogWrite(LeftWheelSpeedControl, LWSCN);
    analogWrite(RightWheelSpeedControl, RWSCN);
  }
  else if (opCode == "R")
  {
    digitalWrite(LeftWheelDirectionControl, HIGH);
    digitalWrite(RightWheelDirectionControl, LOW);
    analogWrite(LeftWheelSpeedControl, LWSCN);
    analogWrite(RightWheelSpeedControl, RWSCN);
  }
  else if (opCode == "N")
  {
    digitalWrite(LeftWheelDirectionControl, LOW);
    digitalWrite(RightWheelDirectionControl, LOW);
    digitalWrite(LeftWheelSpeedControl, LOW);
    digitalWrite(RightWheelSpeedControl, LOW);
  }
 }
