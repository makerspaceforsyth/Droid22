// Version 1.3
// Data is sent in a <###,###,F> format
// And then broken down into substrings and converted to integers
// LOW = Forward / HIGH = Backward
// Delay are necessary in the movement loop. 
// Without them the code runs quicker than the pwm signal and will run the motors at full speed or stall them.

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
const int BaseFan = 53;
const int MotorControllerSwitch = 51;
const int pingPin1 = 31;
const int pingPin2 = 32;
const int pingPin3 = 33;
const int pingPin4 = 34;
const int ProximityWarningLED1 = 35;
const int ProximityWarningLED2 = 36;
const int ProximityWarningLED3 = 37;
const int ProximityWarningLED4 = 38;

#include <Servo.h>;

Servo PanServo, TiltServo;

void setup() 
{
  PanServo.attach(9);
  TiltServo.attach(10); 
  
  Serial.begin(9600);
  Serial.setTimeout(100); 
  
  pinMode(LeftWheelDirectionControl, OUTPUT);  
  pinMode(LeftWheelSpeedControl, OUTPUT);      
  pinMode(RightWheelDirectionControl, OUTPUT); 
  pinMode(RightWheelSpeedControl, OUTPUT);     
  pinMode(TorsoFan, OUTPUT);                   
  pinMode(BaseFan, OUTPUT);                    
  pinMode(MotorControllerSwitch, OUTPUT);      
  pinMode(ProximityWarningLED1, OUTPUT);
  pinMode(ProximityWarningLED2, OUTPUT);
  pinMode(ProximityWarningLED3, OUTPUT);
  pinMode(ProximityWarningLED4, OUTPUT);
  
  
  digitalWrite(MotorControllerSwitch, HIGH);   
  digitalWrite(TorsoFan, HIGH);                
  digitalWrite(BaseFan, HIGH);              
  digitalWrite(LeftWheelSpeedControl, LOW);
  digitalWrite(RightWheelSpeedControl, LOW);     
}

void loop() 
{
  if (Serial.available() > 0)
  { 
  
  ParseData();
  
  Movement();

  ProximitySensors();
  
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
    Serial.println("If your reading this the code is not functioning correctly.");
  }
  else if (opCode == "F")
  {
    digitalWrite(MotorControllerSwitch, LOW);
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
    digitalWrite(MotorControllerSwitch, LOW);
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
    digitalWrite(MotorControllerSwitch, LOW);
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
    digitalWrite(MotorControllerSwitch, LOW);
    digitalWrite(LeftWheelDirectionControl, LOW);
    analogWrite(LeftWheelSpeedControl, 125);
    digitalWrite(RightWheelDirectionControl, LOW);
    digitalWrite(RightWheelSpeedControl, LOW);
    Serial.println("Robot is Turning Right.");
    Serial.println("");
    delay(100);
  }
  else {
    digitalWrite(MotorControllerSwitch, LOW);
    digitalWrite(LeftWheelDirectionControl, LOW);
    digitalWrite(LeftWheelSpeedControl, LOW);
    digitalWrite(RightWheelDirectionControl, LOW);
    digitalWrite(RightWheelSpeedControl, LOW);
    Serial.println("Robot is Still.");
    Serial.println("");
    delay(100);
  }

  digitalWrite(MotorControllerSwitch, HIGH); //May cause problems if wheels don't move delete this line.
   
  PanServo.write(SP1);
  TiltServo.write(ST1); 
 }

 void ProximitySensors()
 {
  long duration1, inches1, duration2, inches2, duration3, inches3, duration4, inches4;

  pinMode(pingPin1, OUTPUT);
  digitalWrite(pingPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin1, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin1, LOW);
  
  pinMode(pingPin1, INPUT);
  duration1 = pulseIn(pingPin1, HIGH);

  pinMode(pingPin2, OUTPUT);
  digitalWrite(pingPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin2, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin2, LOW);
  
  pinMode(pingPin2, INPUT);
  duration2 = pulseIn(pingPin2, HIGH);

  pinMode(pingPin3, OUTPUT);
  digitalWrite(pingPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin3, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin3, LOW);
  
  pinMode(pingPin3, INPUT);
  duration3 = pulseIn(pingPin3, HIGH);

  pinMode(pingPin4, OUTPUT);
  digitalWrite(pingPin4, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin4, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin4, LOW);

  pinMode(pingPin4, INPUT);
  duration4 = pulseIn(pingPin4, HIGH);

  inches1 = microsecondsToInches1(duration1);
  inches2 = microsecondsToInches2(duration2);
  inches3 = microsecondsToInches3(duration3);
  inches4 = microsecondsToInches4(duration4);
  
  Serial.print(inches1);
  Serial.println("in, "); 
  Serial.print(inches2);
  Serial.println("in, "); 
  Serial.print(inches3);
  Serial.println("in, "); 
  Serial.print(inches4);
  Serial.println("in."); 

  if (inches1 <= 24)
  {
    digitalWrite(ProximityWarningLED1, HIGH);
  }
  if (inches2 <= 24)
  {
    digitalWrite(ProximityWarningLED2, HIGH);
  }
  
  if (inches3 <= 24)
  {
    digitalWrite(ProximityWarningLED3, HIGH);
  }
  
  if (inches4 <= 24)
  {
    digitalWrite(ProximityWarningLED4, HIGH);
  }

  if (inches1 > 24)
  {
    digitalWrite(ProximityWarningLED1, LOW);
  }
  
  if (inches2 > 24)
  {
    digitalWrite(ProximityWarningLED2, LOW);
  }
 
  if (inches3 > 24)
  {
    digitalWrite(ProximityWarningLED3, LOW);
  }

  if (inches4 > 24)
  {
    digitalWrite(ProximityWarningLED4, LOW);
  }
 
 }
 
 long microsecondsToInches1(long microseconds1)
 {
  return microseconds1 / 74 / 2;
 }
long microsecondsToInches2(long microseconds2)
 {
  return microseconds2 / 74 / 2;
 }
long microsecondsToInches3(long microseconds3)
 {
  return microseconds3 / 74 / 2;
 }
long microsecondsToInches4(long microseconds4)
 {
  return microseconds4 / 74 / 2;
 }


