#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



int main() {
    int parent_fds[2];
    pipe(parent_fds);
    int child_fds[2];
    pipe(child_fds);

    int f = fork();
    if (f) {
        // parent
        char line[100];
        while (1) {
            printf("Input: ");
            char line[100];
            fgets(line, 100, stdin);
            close(child_fds[0]);
            write(child_fds[1], line, sizeof(line));
            close(parent_fds[1]);
            read(parent_fds[0], line, sizeof(line));
            printf("Output: %s\n\n", line);
        }

    } else {
        // child
        while (1) {
            // get input 
            char line[100];
            close(child_fds[1]);
            read(child_fds[0], line, sizeof(line));
            
            if (line) {
                // reverse the string
                // printf("Reversing string: %s\n", line);
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
                // printf("Reversed string: %s\n", new_line);

                // write to the pipe
                close(parent_fds[0]);
                write(parent_fds[1], new_line, sizeof(line));
                sleep(1);
            }
            
        }
    }
}