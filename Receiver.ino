//Version 1.1
// Data is sent in a <1,2,3,4,5,6> format
// And then broken down into substrings and converted to integers

String DATA;
String str1;
String str2;
String str3;

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
  DATA = (Serial.readString());
  Serial.println(DATA);
  

  str1 = DATA.substring(1,2);
  str2 = DATA.substring(3,4);
  str3 = DATA.substring(5,6);
  SP1 = str1.toInt();
  ST1 = str2.toInt();
  SP1 = map(SP1, 0, 9, 0, 180);
  ST1 = map(ST1, 0, 9, 0, 180);
  Serial.print("Panning Servo is at ");
  Serial.print(SP1);
  Serial.println(" Degrees.");
  Serial.print("Tilting Servo is at ");
  Serial.print(ST1);
  Serial.println(" Degrees.");
  
  if (str3.substring(0) == "F")
  {
    digitalWrite(2, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    Serial.println("Robot is Moving Forward.");
  }
  else if (str3.substring(0) == "B")
  {
    digitalWrite(2,HIGH);
    digitalWrite(4,LOW);
    digitalWrite(7,HIGH);
    digitalWrite(8,LOW);
    Serial.println("Robot is Moving Backward.");
  }
  else if (str3 == "L")
  {
    digitalWrite(2,LOW);
    digitalWrite(4,LOW);
    digitalWrite(7,HIGH);
    digitalWrite(8,HIGH);
    Serial.println("Robot is Turning Left.");
    
  }
  else if (str3 == "R")
  {
    digitalWrite(2,HIGH);
    digitalWrite(4,HIGH);
    digitalWrite(7,LOW);
    digitalWrite(8,LOW);
    Serial.println("Robot is Turning Right.");
  }
  else {
    digitalWrite(2,HIGH);
    digitalWrite(4,HIGH);
    digitalWrite(7,HIGH);
    digitalWrite(8,HIGH);
    Serial.println("Robot is Still.");
  }
  
  PanServo.write(90);
  TiltServo.write(90);
  
  }
}
