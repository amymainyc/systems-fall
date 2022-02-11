#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct address {
    int house_number;
    char street_name[100];
    char city[100];
    char state[100];
    int zip_code;
    struct address *next;
};

void print_address(struct address *a) {
    printf("\n%d %s\n%s, %s %d\n", a->house_number, a->street_name, a->city, a->state, a->zip_code);
}

struct address * set_address(int house_number, char *street_name, char *city, char *state, int zip_code) {
    struct address *a;
    a = malloc(sizeof(struct address));
    a->house_number = house_number;
    strcpy(a->street_name, street_name);
    strcpy(a->city, city);
    strcpy(a->state, state);
    a->zip_code = zip_code;

    return a;
}

void print_list(struct address *a) {
    while (a) {
        print_address(a);
        a = (a->next);
    }
}

struct address * insert_front(struct address *a, int house_number, char *street_name, char *city, char *state, int zip_code) {
    struct address *b = set_address(
        house_number,
        street_name,
        city,
        state,
        zip_code
    );

    b->next = a;
    return b;
}

struct address * free_list(struct address *a) {
    while (a->next) {
        free(a);
        a = (a->next);
    }
    return a;
}

struct address * remove_node(struct address *a, char *street_name) {
    struct address *previous = 0;
    struct address *current = a;
    while (current && strcmp(current->street_name, street_name) != 0) {
        previous = current;
        current = current->next;
    }
    if (current == 0) return a;
    if (previous) {
        previous->next = current->next;
    } else {
        previous = current->next;
    }
    free(current);
    return a;
}