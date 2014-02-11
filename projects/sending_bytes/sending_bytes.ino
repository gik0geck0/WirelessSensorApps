
void runTest();

void setup() {
   pinMode(13, OUTPUT);
   Serial.begin(57600);
   Serial.setTimeout(2);
}

char receive_byte[10];
char recstatus = 0;

void loop() {
  recstatus = Serial.readBytes(receive_byte, 3);
  if (recstatus == 1) {
    if (receive_byte[0] == 'T') {
		runTest();
	}
  }
  delay(100);
}

int length = 1000;
void runTest() {
	// make a test array with random int16s
	int* a = (int*) malloc(length*sizeof(int));

	// Show and randomly fill A
	for (int i=0; i<length;i++) {
		a[i] = random(-32767, 32767);
	}
	
	// Time sending as ints
	unsigned long startInt = micros();
	for (int i=0; i<length;i++) {
		Serial.print(a[i]);
	}
	unsigned long endInt = micros();
	
	// Time sending as bytes
	unsigned long startBPrint = micros();
	byte* bs = (byte*) a;
	for (int i=0; i<length*2;i++) {
		Serial.print(bs[i]);
	}
	unsigned long endBPrint = micros();
	
		
	// Time sending as bytes, using write(buf, len) instead of print
	byte* b = (byte*) a;
	unsigned long startByte = micros();
	Serial.write(b, length*2);
	unsigned long endByte = micros();
	
	///////////////////////////////////////////////////////
	//////////////////// Test 2 ///////////////////////////
	///////////////////////////////////////////////////////
	
	// make a test array with random doubles
	// Note: Were using the exact byte count as the int test: 2000 bytes.
	double* da = (double*) malloc(length/2*sizeof(double));

	// randomly fill A
	for (int i=0; i<length/2;i++) {
		da[i] = random(-32767, 32767);
	}
	
	// Time sending as ints
	unsigned long startDoub = micros();
	for (int i=0; i<length/2;i++) {
		Serial.print(da[i]);
	}
	unsigned long endDoub = micros();
	
	// Time sending as bytes
	unsigned long startDBPrint = micros();
	byte* db = (byte*) da;
	for (int i=0; i<length*2;i++) {
		Serial.print(db[i]);
	}
	unsigned long endDBPrint = micros();
	
	// Time sending as bytes, using write(buf, len) instead of print
	byte* dbs = (byte*) da;
	unsigned long startDByte = micros();
	Serial.write(dbs, length*2);
	unsigned long endDByte = micros();
	
	//// Int Results
	Serial.println("");
	Serial.print("Int Print: ");
	Serial.println(endInt - startInt);
	
	Serial.print("Byte Print: ");
	Serial.println(endBPrint - startBPrint);
	
	Serial.print("Byte Write: ");
	Serial.println(endByte - startByte);
	
	//// Double Results
	Serial.println("");
	Serial.print("Double Print: ");
	Serial.println(endDoub - startDoub);
	
	Serial.print("Double-Byte Print: ");
	Serial.println(endDBPrint - startDBPrint);
	
	Serial.print("Double-Byte Write: ");
	Serial.println(endDByte - startDByte);
	
	// Free up malloc'd resources
	free(a);
	free(da);
	// Ignore dangling pointers. They fall out of scope
}
