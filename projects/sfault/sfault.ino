void setup()
{
   pinMode(13, OUTPUT);
   Serial.begin(57600);
}


void loop()
{
	byte* b = NULL;
	Serial.println(*b);
  delay(1000);               // wait for a second
}