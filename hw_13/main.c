#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

#define READ_FILE_NAME "nyc_pop.csv"
#define WRITE_FILE_NAME "nyc_pop_data"

struct pop_entry {
    int year;
    int population;
    char boro[15];
};

struct pop_entry * make_entry(int year, int pop, char * boro) {
    struct pop_entry * entry = malloc(sizeof(struct pop_entry *));
    entry->year = year;
    entry->population = pop;
    strcpy(entry->boro, boro);
    return entry;
}

void print_data(struct pop_entry ** entries) {
    printf("\nPrinting entries...\n");
    int i = 0;
    while (entries[i]) {
        printf("#%-4d   Year: %-10d Boro: %-20s Pop: %-20d\n", i, entries[i]->year, entries[i]->boro, entries[i]->population);
        i++;
    }
}

struct pop_entry ** read_data() {

    // open the write file and parse the data
    struct stat file;
    stat(WRITE_FILE_NAME, &file);
    int size_to_read = file.st_size;

    struct pop_entry ** entries = calloc(2, file.st_size);
    int i;

    int write_file = open(WRITE_FILE_NAME, O_RDONLY);
    if (write_file < 0) {
        printf("%s\n", strerror(errno));
        return NULL;
    }

    struct pop_entry * entry = malloc(sizeof(struct pop_entry *));
    int res = read(write_file, entry, sizeof(struct pop_entry));
    if (res < 0) {
        printf("%s\n", strerror(errno));
    }
    i = 0;
    while (size_to_read > 0) {
        struct pop_entry * new_entry = make_entry(entry->year, entry->population, entry->boro);
        entries[i] = new_entry;
        size_to_read -= sizeof(struct pop_entry);
        res = read(write_file, entry, sizeof(struct pop_entry));
        if (res < 0) {
            printf("%s\n", strerror(errno));
        }
        i++;
    }
    close(write_file);

    return entries;
}

void add_data(int year, int pop, char * boro) {
    printf("\nAdding new data...\n");

    // append the data to the file
    struct pop_entry entry;
    entry.year = year;
    entry.population = pop;
    strcpy(entry.boro, boro);

    int write_file = open(WRITE_FILE_NAME, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (write_file < 0) {
        printf("%s\n", strerror(errno));
        return;
    }

    int res = write(write_file, &entry, sizeof(entry));
    if (res < 0) {
        printf("%s\n", strerror(errno));
        return;
    }

    close(write_file);
}

void update_data(int i, int year, int pop, char * boro) {

    // update entry
    struct pop_entry ** entries = read_data();
    entries[i]->year = year;
    entries[i]->population = pop;
    strcpy(entries[i]->boro, boro);

    // write data to file
    int write_file = open(WRITE_FILE_NAME, O_WRONLY | O_CREAT, 0644);
    if (write_file < 0) {
        printf("%s\n", strerror(errno));
        return;
    }
    write(write_file, entries, sizeof(entries));

    close(write_file);
}

void read_csv() {
    printf("\nReading contents...\n");

    // open the read file and parse the data
    int read_file = open(READ_FILE_NAME, O_RDONLY);
    if (read_file < 0) {
        printf("%s\n", strerror(errno));
        return;
    }

    struct stat file;
    stat(READ_FILE_NAME, &file);
    int res = 0;
    char data[file.st_size];
    res = read(read_file, data, sizeof(data));
    if (res < 0) {
        printf("%s\n", strerror(errno));
        return;
    }
    
    // split the data by \n
    char * lines[50];
    char * line = strtok(data, "\n");
    lines[0] = strtok(NULL, "\n");
    int i = 1;

    while (line != NULL) {
        line = strtok(NULL, "\n");
        lines[i] = line;
        i++;
    }

    // split the data by , and store data
    int year, pop;
    char *boro;
    i = 0;

    while (lines[i] != NULL) {
        line = lines[i];
        i++;

        char *num = strtok(line, ",");

        year = atoi(num);

        boro = "Manhattan";
        num = strtok(NULL, ",");
        pop = atoi(num);
        add_data(year, pop, boro);

        boro = "Brooklyn";
        num = strtok(NULL, ",");
        pop = atoi(num);
        add_data(year, pop, boro);

        boro = "Queens";
        num = strtok(NULL, ",");
        pop = atoi(num);
        add_data(year, pop, boro);

        boro = "Bronx";
        num = strtok(NULL, ",");
        pop = atoi(num);
        add_data(year, pop, boro);

        boro = "Staten Island";
        num = strtok(NULL, ",");
        pop = atoi(num);
        add_data(year, pop, boro);
    }

    close(read_file);
}

int main(int argc, char * argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "-read_csv") == 0) {
            read_csv();

        } else if (strcmp(argv[1], "-add_data") == 0) {
            printf("Please enter these fields (year,population,borough) separated by commas:\n");
    
            char args[100];
            fgets(args, sizeof(args), stdin);

            int year = 0;
            int pop = 0;
            char boro[15];
            sscanf(args, "%d,%d,%s", &year, &pop, boro);

            add_data(year, pop, boro);

        } else if (strcmp(argv[1], "-read_data") == 0) {
            struct pop_entry ** entries = read_data();
            print_data(entries);

        } else if (strcmp(argv[1], "-update_data") == 0) {
            printf("Please enter the number for the entry you would like to update:\n");
            char num[10];
            fgets(num, sizeof(num), stdin);
            int i;
            sscanf(num, "%d", &i);

            printf("Please enter these fields (year,population,borough) separated by commas:\n");
    
            char args2[100];
            fgets(args2, sizeof(args2), stdin);

            int year = 0;
            int pop = 0;
            char boro[15];
            sscanf(args2, "%d,%d,%s", &year, &pop, boro);

            update_data(i, year, pop, boro);
        }
    }
}

