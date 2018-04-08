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

  PanServo.attach(9);
  TiltServo.attach(10);
  
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial1.setTimeout(20);
  
  pinMode(powerTransistor, OUTPUT);
  
  digitalWrite(TorsoFan, HIGH);
//  digitalWrite(powerTransistor, LOW);

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
/*     
 * Enable this section for text feedback on movement\
 * 
  if (opCode == "F")
  {
    Serial1.println("Robot is Moving Forward.");
    Serial1.println("");
  }
  else if (opCode == "B")
  {
    Serial1.println("Robot is Moving Backward.");
    Serial1.println("");
  }
  else if (opCode == "L")
  {
    Serial1.println("Robot is Turning Left.");
    Serial1.println("");
  }
  else if (opCode == "R")
  {
    Serial1.println("Robot is Turning Right.");
    Serial1.println("");
  }
  else if (opCode == "N")
  {
    Serial1.println("Robot is Still.");
    Serial1.println("");
  }
*/   
  PanServo.write(SP1);
  TiltServo.write(ST1); 
 }
