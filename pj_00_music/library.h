struct song_node ** make_library();

int get_index(char *str);

struct song_node ** add_library_song(struct song_node **library, char *name, char *artist);

struct song_node ** delete_library_song(struct song_node **library, char *name, char *artist);

struct song_node * get_by_library_song(struct song_node **library, char *name, char *artist);

struct song_node * get_by_library_artist(struct song_node **library, char *artist);

void shuffle_library(struct song_node ** library, int n);

void print_library_letter(struct song_node** library, char c);

void print_library_artist(struct song_node** library, char *artist);

void print_library(struct song_node** library);

struct song_node ** free_library(struct song_node** library);