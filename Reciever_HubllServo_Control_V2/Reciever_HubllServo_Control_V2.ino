// Version 1.4.2
// Data is sent in a "<###,###,F> " format
// And then broken down into substrings and converted to integers
// LOW = Forward / HIGH = Backward
// Swap OPCode to be in front of the servo positions
// Potential baud rates: 230400/250000/500000/1000000
// Need to drive power transitor high
// 7.625 minutes | 1 minute
// "<F,##,##,###,###> "

String DATA;
String DATA2;
String Final;
String PanningServo;
String TiltingServo;
int SP1;
int ST1;
int lengthInput;

const int powerTransistor = 51;

#include <Servo.h>;

Servo PanServo, TiltServo;

void setup() 
{ 
  pinMode(powerTransistor, OUTPUT);
  digitalWrite(powerTransistor, HIGH);

  PanServo.attach(9);
  TiltServo.attach(10);

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
  lengthInput = (DATA.length());
  Final = DATA.substring(17,18);
  if (lengthInput == "18" && Final == ">")
  {
  Serial2.println(DATA);
  PanningServo = DATA.substring(10,13);
  TiltingServo = DATA.substring(14,17);
  SP1 = PanningServo.toInt();
  ST1 = TiltingServo.toInt();
  SP1 = (SP1 - 100);
  ST1 = (ST1 - 100);
  DATA2 = DATA;
  }
  else
  {
  Serial2.println(DATA2);
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
  PanServo.write(SP1);
  TiltServo.write(ST1);
}
