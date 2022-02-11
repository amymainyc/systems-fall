struct song_node {
	char name[100];
	char artist[100];
	struct song_node *next;
};

struct song_node * make_node(char *name, char *artist);

struct song_node * insert_front(struct song_node *song_list, char *name, char *artist);

int compare_nodes(struct song_node *s1, struct song_node *s2);

struct song_node * insert_alpha(struct song_node *song_list, char *name, char *artist);

void print_node(struct song_node *a);

void print_list(struct song_node *a);

struct song_node * get_by_artist(struct song_node *song_list, char *artist);

struct song_node * get_by_song(struct song_node *song_list, char *name, char *artist);

struct song_node * get_random_song(struct song_node *song_list);

struct song_node * remove_node(struct song_node *song_list, char *name, char *artist);

struct song_node * free_list(struct song_node *song_list);
