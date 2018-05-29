//"<F,##,##,###,###> "

String opCode;
String DATA;
String servoHead;
String servoTilt;

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

  int SPD1 = map(SP1, 0, 1024, 0, 180);
  int STD1 = map(ST1, 0, 1024, 0, 180);
  servoHead = (100 + SPD1);
  servoTilt = (100 + STD1);
  
  opCode = generateOpCode(FB1, LR1);

  DATA = "<" + opCode + "," + servoHead + "," + servoTilt + "> ";

  Serial.println(DATA);
  delay(100);
}

String generateOpCode (int FB1, int LR1)
{
String opCode = "N,00,00";
String RSpeed;
String LSpeed;

if (FB1 > 560)
{
  if (LR1 > 510)
  {
    
    FB1 = map(FB1, 500, 1024, 0, 99);
    LR1 = map(LR1, 500, 1024, 0, 60);
    int FB2 = FB1 - LR1/2.5;
    if (FB2 < 10)
    {
      FB2 = 10;
    }
    RSpeed = String(FB2);
    LSpeed = String(FB1);
    opCode = "F," + LSpeed + "," + RSpeed; 
  }
  else if (LR1 < 470)
  {
    FB1 = map(FB1, 500, 1024, 0, 99);
    LR1 = map(LR1, 0, 550, 60, 0);
    int FB2 = FB1 - LR1/2.5;
    if (FB2 < 10)
    {
      FB2 = 10;
    }
    RSpeed = String(FB1);
    LSpeed = String(FB2);
    opCode = "F," + LSpeed + "," + RSpeed; 
  }
  else
  {    
    FB1 = map(FB1, 500, 1024, 10, 99);
    String RLSpeed = String(FB1);
    opCode = "F," + RLSpeed + "," + RLSpeed;
  }
}

else if (FB1 < 460)
{
  if (LR1 > 550)
  {
    LR1 = map(LR1, 500, 1024, 0, 60);
    FB1 = map(FB1, 0, 460, 99, 10);
    int FB2 = FB1 - LR1/2.5;
    if (FB2 < 10)
    {
      FB2 = 10;
    }
    RSpeed = String(FB1);
    LSpeed = String(FB2);
    opCode = "B," + LSpeed + "," + RSpeed; 
  }
  else if (LR1 < 470)
  {
    LR1 = map(LR1, 0, 470, 60, 0);
    FB1 = map(FB1, 0, 460, 99, 10);
    int FB2 = FB1 - LR1/2.5;
    if (FB2 < 10)
    {
      FB2 = 10;
    }
    RSpeed = String(FB2);
    LSpeed = String(FB1);
    opCode = "B," + RSpeed + "," + LSpeed; 
  }
  else
  {    
    FB1 = map(FB1, 500, 0, 10, 99);
    String RLSpeed = String(FB1);
    opCode = "B," + RLSpeed + "," + RLSpeed;
  }
 }

else if (LR1 > 611)
{
  LR1 = map(LR1, 500, 1024, 10, 99);
  String RLSpeed = String(LR1);
  opCode = "R," + RLSpeed + "," + RLSpeed;
}
else if (LR1 < 413)
{
  LR1 = map(LR1, 500, 0, 10, 99);
  String RLSpeed = String(LR1);
  opCode = "L," + RLSpeed + "," + RLSpeed;
}

return opCode;
}
