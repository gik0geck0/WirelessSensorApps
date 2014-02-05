
int ledVal;
double arraything[8191];
int i = 0;
int a=2;

void setup()
{
   pinMode(13, OUTPUT);
   Serial.begin(57600);
	arraything[8191] = 20;
}


void loop()
{
  ledVal = digitalRead(13);
  if (ledVal == HIGH) {
    digitalWrite(13,LOW);
  } else {
    digitalWrite(13,HIGH);
  }
  
  Serial.print("Hello, world!");
  Serial.println(arraything[8191]);
  Serial.println(i);
  Serial.println(a);
  i++;
  delay(1000);               // wait for a second
}