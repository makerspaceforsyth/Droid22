//Version 1.1
//0, 1024, 512, 768, 256;
//Control scketch for Maskerspace Mascot

String DATA;
String str1;
String str2;
String str3;
String str4;
String str6;

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

String str5 = generateOpCode(FB1, LR1);


str3 = map(SP1, 0, 1024, 0, 9);
str4 = map(ST1, 0, 1024, 0, 9);
 
str1 = "<";
str2 = ",";
String str11 = ">";

DATA = str1 + str3 + str2 + str4 + str2 + str5 + str11;

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
