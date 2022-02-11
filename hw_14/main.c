#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

static void sighandler(int signo) {
    if (signo == SIGINT) {
        char error[] = "Program exited due to SIGINT.\n";
        
        int file = open("logs.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (file < 0) {
            printf("%s\n", strerror(errno));
        }

        int res = 0;
        res = write(file, error, sizeof(error));
        if (res < 0) {
            printf("%s\n", strerror(errno));
        }

        close(file);
        exit(0);

    } else if (signo == SIGUSR1) {
        printf("ppid: %d\n", getppid());
    }
}

int main() {
	signal(SIGINT, sighandler);
    signal(SIGUSR1, sighandler);

    while (1) {
        printf("pid: %d\n", getpid());
        sleep(1);
    }
}