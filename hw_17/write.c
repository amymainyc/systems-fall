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

int main() {
    int semd = semget(SEM_KEY, 1, 0);
    int shmd = shmget(SHM_KEY, sizeof(int), 0644);

    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_flg = SEM_UNDO;
    sb.sem_op = -1;
    semop(semd, &sb, 1);
    
    // read the previous line
    int *size = shmat(shmd, 0, 0);
    // printf("%d", *size);
    int f = open("message.txt", O_RDONLY);
    lseek(f, *size, SEEK_SET);
    char line[1000];
    int res = read(f, line, *size);
    if (res == -1) {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }
    line[*size] = '\0';
    printf("Previous line: %s\n", line);

    // add a new line
    char new_line[100];
    printf("New line: ");
    fgets(new_line, sizeof(new_line), stdin);
    int new_size = strcspn(new_line, "\n");
    new_line[new_size] = '\0';

    close(f);
    f = open("message.txt", O_WRONLY | O_APPEND);
    res = write(f, new_line, new_size);
    if (res == -1) {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }
    close(f);

    sb.sem_op = 1;
    semop(semd, &sb, 1);
}