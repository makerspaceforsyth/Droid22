void setup() 
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

void loop() 
{
analogWrite(44, 50);
analogWrite(45, 50);
digitalWrite(51, LOW);
delay(50);
digitalWrite(42, HIGH);
digitalWrite(43, HIGH);
delay(1000);
}
