
int sum(int* list, int length) {
	int total = 0;
	for (int i=0; i<length; i++) {
		total += list[i];
	}
	return total;
}

int* zipWithMult(int* listA, int* listB, int length) {
	int* retList = (int*) malloc(length*sizeof(int));
	for (int i=0; i<length; i++) {
		retList[i] = listA[i] * listB[i];
	}
	return retList;
}

int** matrixMult(int** a, int** b, int ra, int carb, int cb) {
	int** retMult = (int**) malloc(ra*sizeof(int*));
	for (int i=0; i<ra; i++) {
        retMult[i] = (int*) malloc(cb*sizeof(int));
		for (int j=0; j<cb; j++) {
			// The value in [i,j] is...
            int* zwm = zipWithMult(a[i], b[j], carb);
			retMult[i][j] = sum(zwm, carb);
            free(zwm);
		}
	}
	return retMult;
}

void setup()
{
	pinMode(13, OUTPUT);
	Serial.begin(57600);
	randomSeed(analogRead(0));
}

int ra = 10;
int carb = 10;
int cb = 10;

void loop()
{
	// Room for the two matricies
	int** a = (int**) malloc(ra*sizeof(int*));
    for(int i=0; i<ra; i++)
        a[i] = (int*) malloc(carb*sizeof(int));

	int** b = (int**) malloc(carb*sizeof(int*));
    for(int i=0; i<carb; i++)
        b[i] = (int*) malloc(ra*sizeof(int));

	// Show and randomly fill A
	Serial.println("Matrix A:");
	for (int i=0; i<ra;i++) {
		for (int j=0; j<carb; j++) {
			a[i][j] = rand();
			Serial.print(a[i][j]);
			Serial.print(' ');
		}
		Serial.println("");
	}
	
	// Show and randomly fill B
	Serial.println("Matrix B:");
	for (int i=0; i<carb;i++) {
		for (int j=0; j<cb; j++) {
			b[i][j] = (int) rand();
			Serial.print(b[i][j]);
			Serial.print(' ');
		}
		Serial.println("");
	}
	
	unsigned long startCalcTime = micros();
	int** result = matrixMult(a, b, ra, carb, cb);
	unsigned long endCalcTime = micros();
	
	// Show the mult result
	Serial.println("Mult result:");
    unsigned long startTransTime = micros();
	for (int i=0; i<ra; i++) {
		for (int j=0; j<cb; j++) {
			Serial.print(result[i][j]);
			Serial.print(' ');
		}
		Serial.println("");
	}
    unsigned long endTransTime = micros();

    Serial.print("Calc time: ");
    Serial.println(endCalcTime - startCalcTime);

    Serial.print("With transmission: ");
    Serial.println(endCalcTime - startCalcTime + endTransTime - startTransTime);

    for(int i=0; i<ra; i++)
        free(a[i]);
    free(a);

    for(int i=0; i<carb; i++) {
        free(result[i]);
        free(b[i]);
    }

    free(b);
    free(result);
	delay(100);
}
