
// Version 1.3.2
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

//#include <Servo.h>;

//Servo PanServo, TiltServo;

void setup() 
{
<<<<<<< HEAD

  //PanServo.attach(9);
  //TiltServo.attach(10); 
=======
/*
  PanServo.attach(29);
  TiltServo.attach(31); 
>>>>>>> 70bc1920af1e8cdb65ef46c6f624d22fdebfad66
  
  Serial.begin(9600);
  Serial.setTimeout(100); 
 
  pinMode(LeftWheelDirectionControl, OUTPUT);  
  pinMode(LeftWheelSpeedControl, OUTPUT);      
  pinMode(RightWheelDirectionControl, OUTPUT); 
  pinMode(RightWheelSpeedControl, OUTPUT);     
  pinMode(TorsoFan, OUTPUT);                   
  pinMode(BaseFan, OUTPUT);                    
  pinMode(MotorControllerSwitch, OUTPUT);      
 
  digitalWrite(MotorControllerSwitch, HIGH);   
  digitalWrite(TorsoFan, HIGH);                
  digitalWrite(BaseFan, HIGH);              
  digitalWrite(LeftWheelSpeedControl, LOW);
  digitalWrite(RightWheelSpeedControl, LOW);*/
  
  testSetup();

}

void loop() 
{
  /*(if (Serial.available() > 0)
  { 
  
  ParseData();
  
  Movement();

  }*/
  testLoop();
}

void testLoop()
{
  digitalWrite(44, HIGH);
  digitalWrite(45, HIGH);
  
  //analogWrite(44, 50);
  //analogWrite(45, 50);
  digitalWrite(51, LOW);
  delay(50);
  digitalWrite(42, HIGH);
  digitalWrite(43, HIGH);
  delay(1000);  
}

void testSetup()
{
  pinMode(51, OUTPUT);
  digitalWrite(51, HIGH);
  pinMode(42, OUTPUT);
  pinMode(43, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(45, OUTPUT);
  digitalWrite(42, LOW);
  digitalWrite(43, LOW);
  
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
    analogWrite(LeftWheelSpeedControl, 50);
    digitalWrite(RightWheelDirectionControl, LOW);
    analogWrite(RightWheelSpeedControl, 50);
    Serial.println("Robot is Moving Forward.");
    Serial.println("");
    delay(100);
  }
  else if (opCode == "B")
  {
    digitalWrite(MotorControllerSwitch, LOW);
    digitalWrite(LeftWheelDirectionControl, HIGH);
    analogWrite(LeftWheelSpeedControl, 50);
    digitalWrite(RightWheelDirectionControl, HIGH);
    analogWrite(RightWheelSpeedControl, 50);
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
    analogWrite(RightWheelSpeedControl, 50);
    Serial.println("Robot is Turning Left.");
    Serial.println("");
    delay(100);
  }
  else if (opCode == "R")
  {
    digitalWrite(MotorControllerSwitch, LOW);
    digitalWrite(LeftWheelDirectionControl, LOW);
    analogWrite(LeftWheelSpeedControl, 50);
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
   
  //PanServo.write(SP1);
  //TiltServo.write(ST1); 
 }
