// Version 1.2.1
// Data is sent in a <###,###,F> format
// And then broken down into substrings and converted to integers
//LOW = Forward / HIGH = Backward

String DATA;
String PanningServo;
String TiltingServo;
String opCode;

int SP1;
int ST1;

const int LeftWheelDirectionControl = 42;
const int LeftWheelSpeedControl = 44;
const int RightWheelDirectionControl = 43;
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
  
  pinMode(LeftWheelDirectionControl, OUTPUT);  //Left wheel
  pinMode(LeftWheelSpeedControl, OUTPUT);  //Left wheel
  pinMode(RightWheelDirectionControl, OUTPUT);  //Right wheel
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
  if (opCode == "S")
  {
    Serial.println("Activated First Line of Movement Loop.");
    Serial.println("Code is not functioning correctly.");
  }
  else if (opCode == "F")
  {
    digitalWrite(LeftWheelDirectionControl, LOW);
    analogWrite(LeftWheelSpeedControl, 125);
    digitalWrite(RightWheelDirectionControl, LOW);
    analogWrite(RightWheelSpeedControl, 125);
    Serial.println("Robot is Moving Forward.");
    Serial.println("");
    delay(100);
  }
  else if (opCode == "B")
  {
    digitalWrite(LeftWheelDirectionControl, HIGH);
    analogWrite(LeftWheelSpeedControl, 125);
    digitalWrite(RightWheelDirectionControl, HIGH);
    analogWrite(RightWheelSpeedControl, 125);
    Serial.println("Robot is Moving Backward.");
    Serial.println("");
    delay(100);
  }
  else if (opCode == "L")
  {
    digitalWrite(LeftWheelDirectionControl, LOW);
    digitalWrite(LeftWheelSpeedControl, LOW);
    digitalWrite(RightWheelDirectionControl, LOW);
    analogWrite(RightWheelSpeedControl, 125);
    Serial.println("Robot is Turning Left.");
    Serial.println("");
    delay(100);
  }
  else if (opCode == "R")
  {
    digitalWrite(LeftWheelDirectionControl, LOW);
    analogWrite(LeftWheelSpeedControl, 125);
    digitalWrite(RightWheelDirectionControl, LOW);
    digitalWrite(RightWheelSpeedControl, LOW);
    Serial.println("Robot is Turning Right.");
    Serial.println("");
    delay(100);
  }
  else {
    digitalWrite(LeftWheelDirectionControl, LOW);
    digitalWrite(LeftWheelSpeedControl, LOW);
    digitalWrite(RightWheelDirectionControl, LOW);
    digitalWrite(RightWheelSpeedControl, LOW);
    Serial.println("Robot is Still.");
    Serial.println("");
    delay(100);
  }
   
  PanServo.write(90);
  TiltServo.write(90); 
 }
