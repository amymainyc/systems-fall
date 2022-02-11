#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct address {
    int house_number;
    char *street_name;
    char *city;
    char *state;
    int zip_code;
};

void print_address(struct address *a) {
    printf("Address:\n%d %s\n%s, %s %d\n", a->house_number, a->street_name, a->city, a->state, a->zip_code);
}

struct address * set_address(int house_number, char *street_name, char *city, char *state, int zip_code) {
    struct address *a;
    a = malloc(sizeof(struct address));
    a->house_number = house_number;
    a->street_name = street_name;
    a->city = city;
    a->state = state;
    a->zip_code = zip_code;

    return a;
}

int main() {
    srand(time(NULL));
    int house_number = rand() % 1000;
    char street_name[] = "Chambers St";
    char city[] = "New York";
    char state[] = "NY";
    int zip_code = 10282;

    struct address *a = set_address(
        house_number,
        street_name,
        city,
        state,
        zip_code
    );

    print_address(a);

}