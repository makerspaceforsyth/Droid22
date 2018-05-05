// Version 1.3.3
// Data is sent in a <###,###,F> format
// And then broken down into substrings and converted to integers
// LOW = Forward / HIGH = Backward
// Swap OPCode to be in front of the servo positions
// Potential baud rates: 230400/250000/500000/1000000
// Need to drive power transitor high

String DATA;
String PanningServo;
String TiltingServo;
//String opCode;

int SP1;
int ST1;

const int powerTransistor = 51;

#include <Servo.h>;

Servo PanServo, TiltServo;

void setup() 
{ 
  pinMode(powerTransistor, OUTPUT);
  digitalWrite(powerTransistor, LOW);

  PanServo.attach(9);
  TiltServo.attach(10);
  
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial1.setTimeout(20);

  delay(73);
  digitalWrite(powerTransistor, HIGH);

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
  Serial2.println(DATA);
  //opCode = DATA.substring(9,10);
  PanningServo = DATA.substring(1,4);
  TiltingServo = DATA.substring(5,8);
  SP1 = PanningServo.toInt();
  ST1 = TiltingServo.toInt();
  SP1 = (SP1 - 100);
  ST1 = (ST1 - 100);
}


void Movement () 
{ 
  PanServo.write(SP1);
  TiltServo.write(ST1); 
}
