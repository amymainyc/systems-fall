#include "pipe_networking.h"

int main() {

    int to_server;
    int from_server;

    from_server = client_handshake( &to_server );
    char input[100];

	while(1) {
		printf("Input: ");
		fgets(input, sizeof(input), stdin);
		input[strcspn(input, "\n")] = '\0';
		write(to_server, input, sizeof(input));
		read(from_server, input, sizeof(input));
		printf("Output: %s\n", input);
	}
}