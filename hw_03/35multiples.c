#include <stdio.h>

int main() {
	int i;
	int sum = 0;
	for (i = 0; i < 1000; i++) {
	    if (i % 3 == 0 || i % 5 == 0) {
			sum += i;
		}
    }
    printf("The sum of all the multiples of 3 or 5 below 100 is %d.\n", sum);
	return 0;
}

