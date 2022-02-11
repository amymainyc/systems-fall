#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "address.h"


int main() {
    srand(time(NULL));
    int house_number = rand() % 1000;
    char street_name[100] = "Chambers St";
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

    house_number = rand() % 1000;
    char street_name2[100] = "Reade St";

    a = insert_front(
        a, 
        house_number,
        street_name2,
        city,
        state,
        zip_code
    );

    house_number = rand() % 1000;
    char street_name3[100] = "Nevins St";

    a = insert_front(
        a, 
        house_number,
        street_name3,
        city,
        state,
        zip_code
    );

    printf("----Addresses:");
    print_list(a);
    printf("----Addresses after removing node:");
    a = remove_node(a, street_name2);
    print_list(a);
    free_list(a);

}
