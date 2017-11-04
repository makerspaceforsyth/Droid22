// Version ipoyt 1.4.1
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

const int TorsoFan = 52;

#include <Servo.h>

Servo PanServo, TiltServo;

void setup() 
{

  PanServo.attach(4);
  TiltServo.attach(5);
  
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial.begin(9600);
  Serial1.setTimeout(20);
  
  pinMode(TorsoFan, OUTPUT);  // Torso Fan
  
  digitalWrite(TorsoFan, HIGH);
  
}

void loop() 
{
 // if (Serial1.available() > 0)
 // { 
  
  ParseData();
  
  Movement();
  
 // }
}

void ParseData() 
{
  DATA = (Serial1.readString());
  Serial1.print(DATA);
  PanningServo = DATA.substring(1,4);
  TiltingServo = DATA.substring(5,8);
  opCode = DATA.substring(9,10);
  SP1 = PanningServo.toInt();
  ST1 = TiltingServo.toInt();
  SP1 = (SP1 - 100);
  ST1 = (ST1 - 100);
  Serial1.println(SP1);
  Serial1.println(ST1);
}


void Movement () 
{    
    Serial2.println(DATA);

    PanServo.write(SP1);
    TiltServo.write(ST1);
    delay(1000);
}

