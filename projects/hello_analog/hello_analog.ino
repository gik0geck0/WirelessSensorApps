void setup()
{
	Serial.begin(57600);
}

float floatMap(int val, int inLow, int inHigh, float outLow, float outHigh) {
	return ((float) val - inLow) / ((float) inHigh-inLow) * (outHigh - outLow) + outLow;
}

int xInput;
float xVolt;
void loop()
{
	xInput = analogRead(0);
	xVolt = floatMap(xInput, 0, 1024, 0, 3.3);
	Serial.println(xVolt,4);
	delay(100);
}
