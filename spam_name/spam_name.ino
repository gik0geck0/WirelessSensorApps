void setup() {
   pinMode(13, OUTPUT);
   Serial.begin(57600);
   Serial.setTimeout(1);
}

char receive_byte[1];
int incr;
char recstatus;

void loop() {
  recstatus = Serial.readBytes(receive_byte, 1);
  if (recstatus != 0) {
    if (receive_byte[0] == 'S') {
      incr = 0;
    }
  }
  
  if (receive_byte[0] == 'S') {
    Serial.print("B ");
    Serial.println(incr);
    incr++;
  }
}
