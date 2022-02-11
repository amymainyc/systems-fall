#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() { 

	mkfifo("in", 0644);
    mkfifo("out", 0644);

    int in = open("in", O_RDONLY);
    int out = open("out", O_WRONLY);
    
    char line[100];
    while (1) {
        printf("Input: ");
        fgets(line, 100, stdin);
        write(out, line, sizeof(line));
        read(in, line, sizeof(line));
        printf("Output: %s\n\n", line);
    }
	return 0;	
}