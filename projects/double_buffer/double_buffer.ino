#include <MsTimer2.h>

// 2048 bytes for buffers? Sure.
#define BUFFERSIZE 10
int bufferA[BUFFERSIZE];
int bufferB[BUFFERSIZE];

int fakeRead = 0;

byte writeState = 0x00;
byte readState = 0x03;

// Start with read waiting to switch buffers, and write starting with a fresh one
int readIndex = BUFFERSIZE;
int writeIndex = 0;

void sense();

void setup()
{
	Serial.begin(57600);
	MsTimer2::set(1000, sense);
	MsTimer2::start();
	
	// bufferA = (int*) malloc(BUFFERSIZE*sizeof(int));
	// bufferB = (int*) malloc(BUFFERSIZE*sizeof(int));
}

void sense() {
	Serial.println("Starting Write step");
	// Writer impl
	if (writeState == 0x00 || writeState == 0x01) {
		fakeRead++;
		Serial.println("Trying to write at ");
		// Serial.println("Trying to write at ");
		// Serial.print((int) writeIndex);
        // We can attempt transmitting
		/*
        if (writeIndex < BUFFERSIZE) {
            // Read in the value
			// ++fakeRead;
			
			// Serial.print("Writing ");
			/*
			if (writeState == 0x00) {
				bufferA[writeIndex] = fakeRead; // analogRead(0);
				Serial.print(bufferA[writeIndex]);
			} else {
				bufferB[writeIndex] = fakeRead; // analogRead(0);
				Serial.print(bufferB[writeIndex]);
			}
			*
            // Serial.print(" to ");
            // Serial.println(writeIndex);
            // ++writeIndex;
        } else {
            Serial.print("Writing done with buffer ");
            Serial.print(writeState);
            Serial.print(". Moving to state ");
            // We reached the end of the buffer. Change to the done state
            if (writeState == 0x00)
                writeState = 0x02;
            else if (writeState == 0x01)
                writeState = 0x03;
            Serial.println(writeState);
        }
		*/
    } else if (writeState == 0x02 || writeState == 0x03) {
		Serial.println("Write done with buffer");
        // Can we swap buffers?
        if (writeState == 0x02) {
            // Is the writer done with bufferB?
            if (readState == 0x01) {
                // No? oh, okay...
                Serial.println("Deferring write");
            } else {
                // Yay! Switch to bufferB
                writeState = 0x01;
                writeIndex = 0;
                Serial.print("Write swapped to buffer ");
                Serial.println(writeState);
            }
        } else {
            // Is the writer done with bufferA?
            if (readState == 0x00) {
                // No? oh, okay...
                Serial.println("Deferring write");
            } else {
                // Yay! Switch to bufferA
                writeState = 0x00;
                writeIndex = 0;
                Serial.print("Write swapped to buffer ");
                Serial.println(readState);
            }
        }
    }
	Serial.println("Done with write step");
}

void loop() {
	// Reader impl
	Serial.println("Starting Read");
	/*
	if (readState == 0x00 || readState == 0x01) {
		Serial.println("Trying to transmit");
        // We can attempt transmitting
        if (readIndex < BUFFERSIZE) {
            // Transmit this value
            // Serial.println(readBuffer[readIndex]);
            Serial.print("Reading ");
			if (readState == 0x00) {
				Serial.print(bufferA[readIndex]);
			} else {
				Serial.print(bufferB[readIndex]);
			}
            Serial.print(" from ");
            Serial.println(readIndex);
			
            ++readIndex;
        } else {
            // We reached the end of the buffer. Change to the done state
            Serial.print("Read done with buffer ");
            Serial.print(readState);
            Serial.print(". Moving to state ");
            if (readState == 0x00)
                readState = 0x02;
            else if (readState == 0x01)
                readState = 0x03;
            Serial.println(readState);
        }
    } else if (readState == 0x02 || readState == 0x03) {
		Serial.println("Read done with buffer");
        // Can we swap buffers?
        if (readState == 0x02) {
            // Is the writer done with bufferB?
            if (writeState == 0x01) {
                // No? oh, okay...
                Serial.println("Deferring read");
            } else {
                // Yay! Switch to bufferB
                readState = 0x01;
                readIndex = 0;
                Serial.print("Read swapped to buffer ");
                Serial.println(readState);
            }
        } else {
            // Is the writer done with bufferA?
            if (writeState == 0x00) {
                // No? oh, okay...
                Serial.println("Deferring read");
            } else {
                // Yay! Switch to bufferA
                readState = 0x00;
                readIndex = 0;
                Serial.print("Read swapped to buffer ");
                Serial.println(readState);
            }
        }
    }
	*/
	Serial.println("Done with read step");
	
	// Wait a bit
	delay(800);
}
