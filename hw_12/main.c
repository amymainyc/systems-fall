#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{

    DIR *dir;
    struct dirent *dent;
    struct stat sb;
    int dir_size = 0;
    int res = 0;
    
    char dir_name[100];
    if (argc > 1) {
        strcpy(dir_name, argv[1]);
    } else {
        printf("Please enter a directory to scan and use ctrl+D:\n");
        fgets(dir_name, sizeof(dir_name), stdin);
    }

    dir = opendir(dir_name);
    if (!dir) {
        printf("\n%s\n", strerror(errno));
        return -1;
    }

    dent = readdir(dir);
    if (!dent) {
        printf("\n%s\n", strerror(errno));
        return -1;
    }

    printf("\nStatistics for directory: %s\n", dir_name);

    printf("Directories:\n");
    while (dent) {
        stat(dent->d_name, &sb);
        if (S_ISREG(sb.st_mode)) break;
        printf("\t%s\n", dent->d_name);
        dir_size += sb.st_size;
        dent = readdir(dir);
    }

    printf("Regular Files:\n");
    while (dent) {
        printf("\t%s\n", dent->d_name);
        dir_size += sb.st_size;
        dent = readdir(dir);
    }

    printf("Total Directory Size: %d Bytes\n", dir_size);

    closedir(dir);

    return(0);
}