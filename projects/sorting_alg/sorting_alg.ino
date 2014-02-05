

const int INT_MAX = 32767;
// in place merge sort courtesy of:
// http://stackoverflow.com/questions/10360963/in-place-merge-sort
// Modified to remove C++ dependencies
void merge_sort(int *data, int start, int end);
void merge(int *data, int start, int middle, int end);

void merge_sort(int *data, int start, int end){
    if (start < end){
        int middle = (end + start) / 2;
        merge_sort(data, start, middle);
        merge_sort(data, middle+1, end);
        merge(data, start, middle+1, end);
    }
}


void merge(int *data, int start, int middle, int end){
    int left[middle-start+1];
    for (int l_cnt=0; l_cnt<middle-start; l_cnt++){
        left[l_cnt] = data[start+l_cnt];
    }
    left[middle-start] = INT_MAX;
    int right[end-middle+2];
    for (int r_cnt=0; r_cnt<end-middle+1; r_cnt++){
        right[r_cnt] = data[middle+r_cnt];
    }
    right[end-middle+1] = INT_MAX;
    int i = 0;
    int j = 0;
    for (int k=start; k<=end; k++){
        if (left[i] < right[j]){
            data[k] = left[i];
            i++;
        }
        else{
            data[k] = right[j];
            j++;
        }
    }
}

void setup() {
	pinMode(13, OUTPUT);
	Serial.begin(57600);
	randomSeed(analogRead(0));
}

int length = 100;
void loop() {
	int* a = (int*) malloc(length*sizeof(int));

	// Show and randomly fill A
	Serial.println("Matrix A:");
	for (int i=0; i<length;i++) {
		a[i] = random(-32767, 32767);
		Serial.print(a[i]);
		Serial.print(" ");
	}
	Serial.println("");

    unsigned long startSortTime = micros();
    merge_sort(a, 0, length);
    unsigned long endSortTime = micros();

    Serial.println("Sorted:");
    unsigned long startSendTime = micros();
	for (int i=0; i<length;i++) {
        Serial.print(a[i]);
		Serial.print(" ");
    }
    Serial.println("");
    unsigned long endSendTime = micros();

    Serial.print("Sort time: ");
	Serial.println(endSortTime - startSortTime);
    Serial.print("With transmission: ");
	Serial.println(endSortTime - startSortTime + endSendTime - startSendTime);
	delay(100);
	free(a);
}
