//Version 1.1
// Data is sent in a <1,2,3,4,5,6> format
// And then broken down into substrings and converted to integers

String DATA;
String PanningServo;
String TiltingServo;
String Opcode;

int SP1;
int ST1;

#include <Servo.h>;

Servo PanServo, TiltServo;

void setup() 
{

PanServo.attach(9);
TiltServo.attach(10);

Serial.begin(9600);

Serial.setTimeout(500);
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
  PanningServo = DATA.substring(1,2);
  TiltingServo = DATA.substring(3,4);
  Opcode = DATA.substring(5,6);
  SP1 = PanningServo.toInt();
  ST1 = TiltingServo.toInt();
  SP1 = map(SP1, 0, 9, 0, 180);
  ST1 = map(ST1, 0, 9, 0, 180);  
}

void Movement () 
{
  if (Opcode.substring(0) == "F")
  {
    digitalWrite(2, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    Serial.println("Robot is Moving Forward.");
    Serial.println("");
  }
  else if (Opcode.substring(0) == "B")
  {
    digitalWrite(2,HIGH);
    digitalWrite(4,LOW);
    digitalWrite(7,HIGH);
    digitalWrite(8,LOW);
    Serial.println("Robot is Moving Backward.");
    Serial.println("");
  }
  else if (Opcode == "L")
  {
    digitalWrite(2,LOW);
    digitalWrite(4,LOW);
    digitalWrite(7,HIGH);
    digitalWrite(8,HIGH);
    Serial.println("Robot is Turning Left.");
    Serial.println("");
  }
  else if (Opcode == "R")
  {
    digitalWrite(2,HIGH);
    digitalWrite(4,HIGH);
    digitalWrite(7,LOW);
    digitalWrite(8,LOW);
    Serial.println("Robot is Turning Right.");
    Serial.println("");
  }
  else {
    digitalWrite(2,HIGH);
    digitalWrite(4,HIGH);
    digitalWrite(7,HIGH);
    digitalWrite(8,HIGH);
    Serial.println("Robot is Still.");
    Serial.println("");
  }
   
  PanServo.write(90);
  TiltServo.write(90);
 
 }
