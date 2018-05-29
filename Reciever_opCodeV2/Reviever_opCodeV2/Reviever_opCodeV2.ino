// Version 2.0
// Data is sent in a "<F,##,##,###,###> " format
// And then broken down into substrings and converted to integers
// LOW = Forward / HIGH = Backward

String DATA;
String opCode;
String speedRight;
String speedLeft;

int LWSCN;
int RWSCN;

const int LeftWheelPowerControl = 8;  //LWPC
const int RightWheelPowerControl = 7; //LWSC
const int LeftWheelSpeedControl = 6;  //RWPC
const int RightWheelSpeedControl = 9; //RWSC

void setup() 
{

  //PanServo.attach(9);
  //TiltServo.attach(10);
  
  Serial.begin(9600);
  Serial.setTimeout(20);
  
  pinMode(LeftWheelPowerControl, OUTPUT);   //Left wheel
  pinMode(LeftWheelSpeedControl, OUTPUT);   //Left wheel
  pinMode(RightWheelPowerControl, OUTPUT);  //Right wheel
  pinMode(RightWheelSpeedControl, OUTPUT);  //Right wheel
  
}

void loop() 
{
  if (Serial.available() > 0)
  { 
  
  ParseData();
  
  Movement();

  Serial.println(opCode + "," + speedLeft + "," + speedRight);
  
  }
}

void ParseData() 
{
  DATA = (Serial.readString());
  opCode = DATA.substring(1,2);
  speedRight = DATA.substring(3,5);
  speedLeft = DATA.substring(6,8);
  RWSCN = speedRight.toInt();
  LWSCN = speedLeft.toInt();
  RWSCN = map(RWSCN, 10, 99, 0, 100);
  LWSCN = map(LWSCN, 10, 99, 0, 100);
}


void Movement () 
{    
  if (opCode == "F")
  {
    digitalWrite(LeftWheelPowerControl, LOW);
    digitalWrite(RightWheelPowerControl, LOW);
    analogWrite(LeftWheelSpeedControl, LWSCN);
    analogWrite(RightWheelSpeedControl, RWSCN);
  }
  else if (opCode == "B")
  {
    digitalWrite(LeftWheelPowerControl, HIGH);
    digitalWrite(RightWheelPowerControl, HIGH);
    analogWrite(LeftWheelSpeedControl, LWSCN);
    analogWrite(RightWheelSpeedControl, RWSCN);
  }
  else if (opCode == "L")
  {
    digitalWrite(LeftWheelPowerControl, LOW);
    digitalWrite(RightWheelPowerControl, HIGH);
    analogWrite(LeftWheelSpeedControl, LWSCN);
    analogWrite(RightWheelSpeedControl, RWSCN);
  }
  else if (opCode == "R")
  {
    digitalWrite(LeftWheelPowerControl, HIGH);
    digitalWrite(RightWheelPowerControl, LOW);
    analogWrite(LeftWheelSpeedControl, LWSCN);
    analogWrite(RightWheelSpeedControl, RWSCN);
  }
  else if (opCode == "N")
  {
    digitalWrite(LeftWheelPowerControl, LOW);
    digitalWrite(RightWheelPowerControl, LOW);
    digitalWrite(LeftWheelSpeedControl, LOW);
    digitalWrite(RightWheelSpeedControl, LOW);
  }
}
