#include "pipe_networking.h"

int main() {

	int to_client;
	int from_client;

	while (1) {
		from_client = server_setup();

        int f = fork();
        if (f) {

        } else {
            char input[BUFFER_SIZE];
            to_client = server_connect(from_client);

            while (1) {
                if (!read(from_client, input, sizeof(input))) break;
				
                printf("Reversing string: %s\n", input);
				char output[100];
				int end = strlen(input) - 1;
				int start = 0;
				output[end] = 0;
				end--;
				while (end >= 0) {
					// printf("%c\n", line[end]);
					output[start] = input[end];
					end--;
					start++;
				}
				write(to_client, output, sizeof(output));
            }
        }
	}
	return 0;
}