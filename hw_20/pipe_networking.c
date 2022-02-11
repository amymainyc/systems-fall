#include "pipe_networking.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

/*=========================
	server_handshake
	args: int * to_client
	Performs the server side pipe 3 way handshake.
	Sets *to_client to the file descriptor to the downstream pipe.
	returns the file descriptor for the upstream pipe.
	=========================*/
int server_handshake(int *to_client) {
	printf("Creating known pipe...\n");

	int res = mkfifo(WKP, 0644);
	if (res < 0) {
		printf("Couldn't create known pipe. (Error %d: %s)\n", errno, strerror(errno));
		exit(EXIT_FAILURE);
	}

    int from_client = open(WKP, O_RDONLY);
	if (from_client < 0) {
		printf("Couldn't open known pipe. (Error %d: %s)\n", errno, strerror(errno));
		exit(EXIT_FAILURE);
	}

    char handshake[HANDSHAKE_BUFFER_SIZE];
    res = read(from_client, handshake, HANDSHAKE_BUFFER_SIZE);
	if (res < 0) {
		printf("Couldn't read known pipe. (Error %d: %s)\n", errno, strerror(errno));
		exit(EXIT_FAILURE);
	}
    printf("Handshake: %s\n", handshake);
    remove(WKP);

    *to_client = open(handshake, O_WRONLY);
	if (*to_client < 0) {
		printf("Couldn't open secret pipe. (Error %d: %s)\n", errno, strerror(errno));
		exit(EXIT_FAILURE);
	}

    res = write(*to_client, ACK, sizeof(ACK));
	if (res != sizeof(ACK)) {
		printf("Couldn't write to secret pipe. (Error %d: %s)\n", errno, strerror(errno));
		exit(EXIT_FAILURE);
	}

    read(from_client, handshake, sizeof(handshake));
	if (strcmp(handshake, ACK) != 0) {
		printf("Error: Expected: %s\n Recieved: %s\n", ACK, handshake);		
		exit(EXIT_FAILURE);
	}

	printf("Expected: %s\n Recieved: %s\n", ACK, handshake);	
    remove(handshake);
    return from_client;
}


/*=========================
	client_handshake
	args: int * to_server
	Performs the client side pipe 3 way handshake.
	Sets *to_server to the file descriptor for the upstream pipe.
	returns the file descriptor for the downstream pipe.
	=========================*/
int client_handshake(int *to_server) {
	printf("Creating secret pipe...\n");

	int pid = getpid();
    char handshake[100];
    sprintf(handshake, "%d", pid);
    int res = mkfifo(handshake, 0644);
	if (res < 0) {
		printf("Couldn't create secret pipe. (Error %d: %s)\n", errno, strerror(errno));
		exit(EXIT_FAILURE);
	}

    *to_server = open(WKP, O_WRONLY);
	if (*to_server < 0) {
		printf("Couldn't open known pipe. (Error %d: %s)\n", errno, strerror(errno));
		exit(EXIT_FAILURE);
	}

    res = write(*to_server, handshake, sizeof(handshake));
	if (res != sizeof(pid)) {
		printf("Couldn't write to known pipe. (Error %d: %s)\n", errno, strerror(errno));
		exit(EXIT_FAILURE);
	}

    int from_server = open(handshake, O_RDONLY);
	if (from_server < 0) {
		printf("Couldn't open secret pipe. (Error %d: %s)\n", errno, strerror(errno));
		exit(EXIT_FAILURE);
	}

    read(from_server, handshake, sizeof(handshake));
	if (strcmp(handshake, ACK) != 0) {
		printf("Error: Expected: %s\n Recieved: %s\n", ACK, handshake);		
		exit(EXIT_FAILURE);
	}

    printf("Expected: %s\n Recieved: %s\n", ACK, handshake);	
	remove(handshake);
	char * response = "Success";
	printf("%s\n", response);

	res = write(*to_server, response, sizeof(response));
	if (res != sizeof(ACK)) {
		printf("Couldn't write final ACK. (Error %d: %s)\n", errno, strerror(errno));
		exit(EXIT_FAILURE);
	}

    return from_server;
}