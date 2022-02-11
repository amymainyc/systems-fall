#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main() {

    // int array 1
    int arr[10];
    arr[0] = 0;

    srand(time(NULL));
    for (int i = 1; i < 10; i++) {
        arr[i] = rand();
    }

    printf("Int Array 1: \n[");
    for (int i = 0; i < 10; i++) {
        if (i == 9) printf("%d]\n\n", arr[i]);
        else printf("%d, ", arr[i]);
    }

    // int array 2
    int arr2[10];
    int *arrp = arr;
    int *arr2p = arr2;

    printf("Int Array 2 (using *): \n[");
    for (int i = 0; i < 10; i++) {
        *(arr2p + i) = *(arrp + (9 - i));
        if (i == 9) printf("%d]\n\n", *(arr2p + i));
        else printf("%d, ", *(arr2p + i));
    }

    printf("Int Array 2 (using []): \n[");
    for (int i = 0; i < 10; i++) {
        if (i == 9) printf("%d]\n\n", arr2[i]);
        else printf("%d, ", arr2[i]);
    }
}