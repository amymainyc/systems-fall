#include <stdio.h>

int multiple_of_1_to_20() {
	int i = 1;
    int j;
	while (1) {
	    for (j = 1; j <= 20; j++) {
            if (i % j != 0) break;
            if (j == 20) {
                printf("The smallest positive number that is evenly divisible by all of the numbers from 1 to 20 is %d.\n", i);
	            return 0;
            }
        }
        i++;
    }
}

int multiple_of_3_5() {
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