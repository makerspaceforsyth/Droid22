//0, 1024, 512, 768, 256;

String DATA;
String str1;
String str2;
String str3;
String str4;
String str5;

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

Serial.println(FB1);
Serial.println(LR1);

int DFB = 2; //Data Forward/Backward
int DLR = 2; //Data Left/Right

if (FB1 > 768)
{
   DFB = 1;
}
else if (FB1 < 256)
{
   DFB = 0;
}

if (LR1 > 768)
{
   DLR = 1;
}

else if (LR1 < 256)
{
   DLR = 0;
}

if (DFB == 1)
{
  if (DLR == 1)
  {
    str5 = "FR";
  }
  else if (DLR == 0)
  {
    str5 = "FL";
  }
  else if (DLR == 2)
  {
    str5 = "FF";
  }
}

if (DFB == 0)
{
  if (DLR == 1)
  {
    str5 = "BR";
  }
  else if (DLR == 0)
  {
    str5 = "BL";
  }
  else if (DLR == 2)
  {
    str5 = "BB";
  }
}
if (DFB == 2)
{
  str5 = "NN";
}




str3 = map(SP1, 0, 1024, 0, 9);
str4 = map(ST1, 0, 1024, 0, 9);

str3 = "0";
str4 = "0";
  
str1 = "<";
str2 = ",";
String str11 = ">";

DATA = str1 + str3 + str2 + str4 + str2 + str5 + str11;

Serial.println(DATA);

delay(1000);
}
