struct address {
    int house_number;
    char street_name[100];
    char city[100];
    char state[100];
    int zip_code;
    struct address *next;
};

void print_address(struct address *a);

struct address * set_address(int house_number, char *street_name, char *city, char *state, int zip_code);

void print_list(struct address *a);

struct address * insert_front(struct address *a, int house_number, char *street_name, char *city, char *state, int zip_code);

struct address * free_list(struct address *a);

struct address * remove_node(struct address *a, char *street_name);