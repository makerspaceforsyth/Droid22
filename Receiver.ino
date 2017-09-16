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
  }
}
  str1 = DATA.substring(1,2);
  str2 = DATA.substring(3,4);
  str3 = DATA.substring(5,7);
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
  
  if (str3 == "FF")
  {
    digitalWrite(2, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    Serial.println("Robot is Moving Forward.");
  }
  else if (str3 == "FL")
  {
    digitalWrite(2,HIGH);
    digitalWrite(4,HIGH);
    digitalWrite(7,HIGH);
    digitalWrite(8,HIGH);
    Serial.println("Robot is Turning Left and Moving Forward.");
  }
  else if (str3 == "FR")
  {
    digitalWrite(2,HIGH);
    digitalWrite(4,HIGH);
    digitalWrite(7,HIGH);
    digitalWrite(8,HIGH);
    Serial.println("Robot is Turning Right and Moving Forward.");
    
  }
  else if (str3 == "BB")
  {
    digitalWrite(2,HIGH);
    digitalWrite(4,HIGH);
    digitalWrite(7,HIGH);
    digitalWrite(8,HIGH);
    Serial.println("Robot is Moving Backward.");
  }
  else if (str3 == "BL")
  {
    digitalWrite(2,HIGH);
    digitalWrite(4,HIGH);
    digitalWrite(7,HIGH);
    digitalWrite(8,HIGH);
    Serial.println("Robot is Turning Left and Moving Backward.");
  }
  else if (str3 == "BR")
  {
    digitalWrite(2,HIGH);
    digitalWrite(4,HIGH);
    digitalWrite(7,HIGH);
    digitalWrite(8,HIGH);
    Serial.println("Robot is Turning Right and Moving Backward.");
  }
  else if (str3 == "NN")
  {
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

