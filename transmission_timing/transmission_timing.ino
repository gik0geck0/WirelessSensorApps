void setup() {
   pinMode(13, OUTPUT);
   Serial.begin(57600);
}

char send_byte[100];
char recstatus = 0;
int end_t = 0;
int start_t = 0;
int nbytes = 10;
char rec_byte[1];

void loop() {
  recstatus = Serial.readBytes(rec_byte, 1);
  
  if (recstatus > 0) {
    start_t = micros();
    Serial.write((const uint8_t*) send_byte, nbytes);
    end_t = micros();
    
    if (recstatus > 0) {
      Serial.print("Transmit ");
      Serial.print(nbytes);
      Serial.print(" bytes: ");
      Serial.print(end_t-start_t);
      Serial.println(" microseconds");
    }
  }
}
