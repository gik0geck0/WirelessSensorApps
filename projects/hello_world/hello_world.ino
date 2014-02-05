void setup() {
   pinMode(13, OUTPUT);
   Serial.begin(57600);
}

int ledVal;

void loop() {
  ledVal = digitalRead(13);
  if (ledVal == HIGH) {
    digitalWrite(13,LOW);
  } else {
    digitalWrite(13,HIGH);
  }
  Serial.println("Hello, world!");
  delay(1000);               // wait for a second
}
