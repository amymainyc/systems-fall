#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char ** parse_args(char * line) {
	char ** args = calloc(5, sizeof(char *));
    char * arg;
    int i = 0;
    while (line) {
        arg = strsep(&line, " ");
        args[i] = arg;
        i++;
    }
	args[i] == 0;
    return args;
}

int main() {
	printf("Enter command:\n");
	char line[100];
    fgets(line, sizeof(line), stdin);
	line[strcspn(line, "\n")] = 0;
	
	printf("\nParsing args...\n");
	char ** args = parse_args(line);
	printf("Executing commands...\n");
	execvp(args[0], args);
	
	return 0;
}
