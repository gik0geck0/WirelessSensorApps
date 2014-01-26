void setup() {
   pinMode(13, OUTPUT);
   Serial.begin(57600);
   Serial.setTimeout(1);
}

char receive_byte[3];
int incr = 0;
char recstatus = 0;
char myname = 'B';
int gotime = 0;

void loop() {
  recstatus = Serial.readBytes(receive_byte, 3);
  if (recstatus == 3) {
    if (receive_byte[0] == 'S' && receive_byte[2] == myname) {
      incr = 0;
      gotime = 1;
    } else if (receive_byte[0] == 'T' && receive_byte[2] == myname) {
      gotime = 0;
    }
  }
  
  if (gotime == 1) {
    Serial.print(myname);
    Serial.print(" ");
    Serial.println(incr);
    incr++;
  }
  delay(1);
}
