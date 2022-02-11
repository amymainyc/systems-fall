#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main() {
    int out = open("in", O_RDONLY);
    int in = open("out", O_WRONLY);

    char line[100];
    while (1) {
        read(in, line, sizeof(line));
        
        // reverse the string
        printf("Reversing string: %s\n", line);
        char new_line[100];
        int end = strlen(line) - 1;
        int start = 0;
        new_line[end] = 0;
        end--;
        while (end >= 0) {
            // printf("%c\n", line[end]);
            new_line[start] = line[end];
            end--;
            start++;
        }
        printf("Reversed string: %s\n", new_line);

        // write to the pipe
        write(out, new_line, sizeof(line));
    }
    return 0;
}