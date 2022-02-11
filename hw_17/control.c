#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#define SHM_KEY 23423
#define SEM_KEY 23424


union semun {
    int val;
    struct semid_ds *buf;
    unsigned short  *array;
    struct seminfo  *__buf;
};


int main(int argc, char **argv) {
    if (argc >= 2) {
        int shmd = shmget(SHM_KEY, sizeof(int), IPC_CREAT | 0644);
        int semd = semget(SEM_KEY, 1, IPC_CREAT | 0644);

        if (strcmp(argv[1], "-create") == 0) {
            if (semd == -1) {
                printf("Error: %s\n", strerror(errno));
            }
            
            union semun us;
            us.val = 1;
            int r = semctl(semd, 0, SETVAL, us);
            if (r == -1) {
                printf("Error: %s\n", strerror(errno));
                return 0;
            }

            int f = open("message.txt", O_CREAT | O_TRUNC, 0644);
            if (f == -1) {
                printf("Error: %s\n", strerror(errno));
                return 0;
            }

        } else if (strcmp(argv[1], "-remove") == 0) {
            shmctl(shmd, IPC_RMID, 0);
            semctl(semd, IPC_RMID, 0);

            int f = open("message.txt", O_RDONLY);
            struct stat st;
            stat("message.txt", &st);
            char * message = malloc(st.st_size + 1);
            int res = read(f, message, st.st_size);
            if (res == -1) {
                printf("Error: %s\n", strerror(errno));
                return 0;
            }
            printf("Story: %s\n", message);
            free(message);
        }

    } else {
        printf("Invalid arguments.\n");
    }
}