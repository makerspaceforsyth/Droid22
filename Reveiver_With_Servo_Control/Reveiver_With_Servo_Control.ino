// Version 1.4.1
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

const int LeftWheelPowerControl = 42;
const int LeftWheelSpeedControl = 44;
const int RightWheelPowerControl = 43;
const int RightWheelSpeedControl = 45;
const int TorsoFan = 52;

void setup() 
{
  
  Serial1.begin(9600);
  Serial2.begin(2400);
  Serial1.setTimeout(20);
  
  pinMode(LeftWheelPowerControl, OUTPUT);  //Left wheel
  pinMode(LeftWheelSpeedControl, OUTPUT);  //Left wheel
  pinMode(RightWheelPowerControl, OUTPUT);  //Right wheel
  pinMode(RightWheelSpeedControl, OUTPUT);  //Right wheel
  pinMode(TorsoFan, OUTPUT);  // Torso Fan
  
  digitalWrite(TorsoFan, HIGH);
  pinMode(51, OUTPUT);
  digitalWrite(51, LOW);
  
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
  Serial1.print(DATA);
  PanningServo = DATA.substring(1,4);
  TiltingServo = DATA.substring(5,8);
  opCode = DATA.substring(9,10);
  SP1 = PanningServo.toInt();
  ST1 = TiltingServo.toInt();
  SP1 = (SP1 - 100);
  ST1 = (ST1 - 100);
  SP1 = map(SP1, 0, 180, 0, 1200);
  ST1 = map(ST1, 0, 180, 0, 1200);
}


void Movement () 
{    
  
  if (opCode == "S")
  {
    Serial1.println("Activated First Line of Movement Loop.");

  }
  else if (opCode == "F")
  {
    digitalWrite(LeftWheelPowerControl, LOW);
    analogWrite(LeftWheelSpeedControl, 75);
    digitalWrite(RightWheelPowerControl, LOW);
    analogWrite(RightWheelSpeedControl, 75);
    Serial1.println("Robot is Moving Forward.");
    Serial1.println("");
  }
  else if (opCode == "B")
  {
    digitalWrite(LeftWheelPowerControl, HIGH);
    analogWrite(LeftWheelSpeedControl, 75);
    digitalWrite(RightWheelPowerControl, HIGH);
    analogWrite(RightWheelSpeedControl, 75);
    Serial1.println("Robot is Moving Backward.");
    Serial1.println("");
  }
  else if (opCode == "L")
  {
    digitalWrite(LeftWheelPowerControl, HIGH);
    analogWrite(LeftWheelSpeedControl, 75);
    digitalWrite(RightWheelPowerControl, LOW);
    analogWrite(RightWheelSpeedControl, 75);
    Serial1.println("Robot is Turning Left.");
    Serial1.println("");
  }
  else if (opCode == "R")
  {
    digitalWrite(LeftWheelPowerControl, LOW);
    analogWrite(LeftWheelSpeedControl, 75);
    digitalWrite(RightWheelPowerControl, HIGH);
    analogWrite(RightWheelSpeedControl, 75);
    Serial1.println("Robot is Turning Right.");
    Serial1.println("");
  }
  else if (opCode == "N")
  {
    digitalWrite(LeftWheelPowerControl, LOW);
    digitalWrite(LeftWheelSpeedControl, LOW);
    digitalWrite(RightWheelPowerControl, LOW);
    digitalWrite(RightWheelSpeedControl, LOW);
    Serial1.println("Robot is Still.");
    Serial1.println("");
changeServoP(9, SP1);
changeServoT(10, ST1);

  }
}
  
int changeServoP(int chan, int posi){
 
int pw = posi; 
byte lsb = pw;
byte msb =  pw >> 8;
int ramp = 0;
 
 
   Serial2.write(33);  //!
   Serial2.write(83);  //S
   Serial2.write(67);  //C
   Serial2.write(chan);  //channel
   Serial2.write(ramp);  //rampspeed
   Serial2.write(lsb);  //LSB
   Serial2.write(msb);  //MSB
   Serial2.write(13);
}
int changeServoT(int chan, int posi){
 
int pw = posi; 
byte lsb = pw;
byte msb =  pw >> 8;
int ramp = 0;
 
 
   Serial2.write(33);  //!
   Serial2.write(83);  //S
   Serial2.write(67);  //C
   Serial2.write(chan);  //channel
   Serial2.write(ramp);  //rampspeed
   Serial2.write(lsb);  //LSB
   Serial2.write(msb);  //MSB
   Serial2.write(13);
}

