#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

    printf("Forking process...\n");
    srand(time(NULL));
    int pid1, pid2;

    pid1 = fork();
    if (pid1 > 0) pid2 = fork();

    if (pid1 && pid2) {
        int status;
        int pid = wait(&status);
        printf("Child %d asleep for %d seconds.\n", pid, WEXITSTATUS(status));
        printf("Parent done.\n");

    } else {
        printf("Child %d started.\n", getpid());
        int time = rand() % 4 + 2;
        sleep(time);
        printf("Child %d done.\n", getpid());
        return time;
    }    

    return 0;
}