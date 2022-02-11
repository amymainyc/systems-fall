#include <stdio.h>

int main() {
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

