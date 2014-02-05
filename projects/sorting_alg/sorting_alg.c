
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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

int micros() {
    clock_t t;
    // gettimeofday(&t, NULL);
    t = clock();
    return ((double) t) / CLOCKS_PER_SEC * 100000;
}

void loop();

int length = 100;
int main() {
    for (int i=0; i<100000; i++) {
        loop();
    }
}

void loop() {
	int* a = (int*) malloc(length*sizeof(int));

	// Show and randomly fill A
	puts("Matrix A:");
	for (int i=0; i<length;i++) {
		a[i] = rand();
		printf("%i ", a[i]);
	}
	printf("\n");

    unsigned long startSortTime = micros();
    merge_sort(a, 0, length);
    unsigned long endSortTime = micros();

    printf("Sorted:\n");
    unsigned long startSendTime = micros();
	for (int i=0; i<length;i++) {
        printf("%i ", a[i]);
    }
    printf("\n");
    unsigned long endSendTime = micros();

    printf("Sort time: %i\n", endSortTime - startSortTime);
    printf("With transmission: %i\n", endSortTime - startSortTime + endSendTime - startSendTime);
    free(a);
}
