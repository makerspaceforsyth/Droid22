// Version 1.3.3
// Data is sent in a <###,###,F> format
// And then broken down into substrings and converted to integers
// LOW = Forward / HIGH = Backward
// Swap OPCode to be in front of the servo positions
// Potential baud rates: 230400/250000/500000/1000000
// Need to drive power transitor high
// 7.625 minutes | 1 minute

String DATA;
String DATA2;
String Final;
String PanningServo;
String TiltingServo;
//String opCode;

int SP1;
int ST1;
int ab = 0;

unsigned long Time;

const int powerTransistor = 51;

#include <Servo.h>;

Servo PanServo, TiltServo;

void setup() 
{ 
  pinMode(powerTransistor, OUTPUT);
  digitalWrite(powerTransistor, HIGH);

  PanServo.attach(9);
  TiltServo.attach(10);

  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial1.setTimeout(20);

  delay(750);
  digitalWrite(powerTransistor, LOW);
}

void loop() 
{
  if (Serial1.available() > 0)
  { 
  
  ParseData();
  
  Movement();
  
  }
}

void ParseData() 
{
  DATA = (Serial1.readString());
  int lengthInput = (DATA.length());
  Final = DATA.substring(10,11);
  if (lengthInput = 11 && Final == ">")
  {
  Serial.println(DATA);
  Serial2.println(DATA);
  //opCode = DATA.substring(9,10);
  PanningServo = DATA.substring(1,4);
  TiltingServo = DATA.substring(5,8);
  SP1 = PanningServo.toInt();
  ST1 = TiltingServo.toInt();
  SP1 = (SP1 - 100);
  ST1 = (ST1 - 100);
  DATA2 = DATA;
  }
  else
  {
  Serial.println(DATA2);
  Serial2.println(DATA2);
  //opCode = DATA.substring(9,10);
  PanningServo = DATA2.substring(1,4);
  TiltingServo = DATA2.substring(5,8);
  SP1 = PanningServo.toInt();
  ST1 = TiltingServo.toInt();
  SP1 = (SP1 - 100);
  ST1 = (ST1 - 100);
  }
}


void Movement () 
{    
  //Time = millis();
  //if( Time > 61000)
  //{
  PanServo.write(SP1);
  TiltServo.write(ST1);
  //}
}
