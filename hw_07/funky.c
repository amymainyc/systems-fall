#include <stdlib.h>
#include <stdio.h>

#define ARR_SIZE 10

void print_int_array(int *arrp) {
	printf("Int Array:");
	for (int i = 0; i < ARR_SIZE; i++) {
		printf(" %d", *(arrp + i));
	}
}

void average_int_array(int *arrp) {
	printf("\nArray Average:");
	int sum = 0;
	for (int i = 0; i < ARR_SIZE; i++) {
		sum += *(arrp + i);
	}
	float average = (float) sum / (float) ARR_SIZE;
	printf(" %f", average);
}

void copy_two_arrays(int *arr1p, int *arr2p) {
	for (int i = 0; i < ARR_SIZE; i++) {
		*(arr2p + i) = *(arr1p + i);
	}
}

int main() {
	int arr[ARR_SIZE];
	for (int i = 0; i < ARR_SIZE; i++) {
		arr[i] = i + 10;
	}
	print_int_array(arr);
	
	average_int_array(arr);
	
	int arr_copy[ARR_SIZE];
	copy_two_arrays(arr, arr_copy);
	
	printf("\nInt Array 1:");
	for (int i = 0; i < ARR_SIZE; i++) {
		printf(" %d", arr[i]);
	}
	printf("\nInt Array 1:");
	for (int i = 0; i < ARR_SIZE; i++) {
		printf(" %d", arr_copy[i]);
	}
	printf("\n");
}
