//Version 1.3
//0, 1024, 512, 768, 256;
//Control sketch for Maskerspace Mascot

String DATA;
String servoHead;
String servoTilt;
String opCode;

void setup() 
{
  Serial.begin(9600); 
}

void loop() 
{

  int SP1 = analogRead(A0); //Panning Servo
  int ST1 = analogRead(A1); //Tilting Servo
  int FB1 = analogRead(A2); //Forward/Backward
  int LR1 = analogRead(A3); //Left/Right
  
  opCode = generateOpCode(FB1, LR1);
  
  int SPD1 = map(SP1, 0, 1024, 0, 180);
  int STD1 = map(ST1, 0, 1024, 0, 180);
  servoHead = (100 + SPD1);
  servoTilt = (100 + STD1);
   
  DATA = "<" + servoHead + "," + servoTilt + "," + opCode + "> ";
  
  Serial.println(DATA);
  
  delay(125);
}


String generateOpCode (int FB1, int LR1)
{  
  String op = "N";

  if (FB1 > 768)
  {
     op = "F";
  }
  else if (FB1 < 256)
  {
    op = "B";
  }
  
  if (LR1 > 768)
  {
    op = "R";
    }
  
  else if (LR1 < 256)
  {
    op = "L";
    }

  return op;
}
