// Version 1.3.3
// Data is sent in a <###,###,F> format
// And then broken down into substrings and converted to integers
// LOW = Forward / HIGH = Backward
// Do not use in its current state. It has a high probability of killing the motors

String DATA;
String PanningServo;
String TiltingServo;
String opCode;

int SP1;
int ST1;

const int LeftWheelPowerControl = 42;
const int LeftWheelSpeedControl = 44;
const int RightWheelPowerControl = 43;
const int RightWheelSpeedControl = 45;
const int TorsoFan = 52;

//#include <Servo.h>;

//Servo PanServo, TiltServo;

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
  pinMode(TorsoFan, OUTPUT);  // Torso Fan
  
  digitalWrite(TorsoFan, HIGH);
  pinMode(51, OUTPUT);
  digitalWrite(51, LOW);
  
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
  
  if (opCode == "S")
  {
    Serial.println("Activated First Line of Movement Loop.");

  }
  else if (opCode == "F")
  {
    digitalWrite(LeftWheelPowerControl, LOW);
    analogWrite(LeftWheelSpeedControl, 75);
    digitalWrite(RightWheelPowerControl, LOW);
    analogWrite(RightWheelSpeedControl, 75);
    Serial.println("Robot is Moving Forward.");
    Serial.println("");
  }
  else if (opCode == "B")
  {
    digitalWrite(LeftWheelPowerControl, HIGH);
    analogWrite(LeftWheelSpeedControl, 75);
    digitalWrite(RightWheelPowerControl, HIGH);
    analogWrite(RightWheelSpeedControl, 75);
    Serial.println("Robot is Moving Backward.");
    Serial.println("");
  }
  else if (opCode == "L")
  {
    digitalWrite(LeftWheelPowerControl, HIGH);
    analogWrite(LeftWheelSpeedControl, 75);
    digitalWrite(RightWheelPowerControl, LOW);
    analogWrite(RightWheelSpeedControl, 75);
    Serial.println("Robot is Turning Left.");
    Serial.println("");
  }
  else if (opCode == "R")
  {
    digitalWrite(LeftWheelPowerControl, LOW);
    analogWrite(LeftWheelSpeedControl, 75);
    digitalWrite(RightWheelPowerControl, HIGH);
    analogWrite(RightWheelSpeedControl, 75);
    Serial.println("Robot is Turning Right.");
    Serial.println("");
  }
  else if (opCode == "N")
  {
    digitalWrite(LeftWheelPowerControl, LOW);
    digitalWrite(LeftWheelSpeedControl, LOW);
    digitalWrite(RightWheelPowerControl, LOW);
    digitalWrite(RightWheelSpeedControl, LOW);
    Serial.println("Robot is Still.");
    Serial.println("");
  }
   
  //PanServo.write(90);
  //TiltServo.write(90); 
 }
