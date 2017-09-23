//Version 1.1
//0, 1024, 512, 768, 256;
//Control scketch for Maskerspace Mascot

String DATA;
String servoHand;
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

servoHand = map(SP1, 0, 1024, 0, 9);
servoTilt = map(ST1, 0, 1024, 0, 9);
 
DATA = "<" + servoHand + "," + servoTilt + "," + opCode + ">";

Serial.println(DATA);

delay(1000);
}


String generateOpCode (int FB1, int LR1)
{
  
  String str5 = "N";

  if (FB1 > 768)
  {
     str5 = "F";
  }
  else if (FB1 < 256)
  {
    str5 = "B";
  }
  
  if (LR1 > 768)
  {
    str5 = "R";
    }
  
  else if (LR1 < 256)
  {
    str5 = "L";
    }

  return str5;
}
