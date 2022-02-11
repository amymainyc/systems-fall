#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlist.h"
#include "library.h"
#include <ctype.h>
#include <time.h>

struct song_node ** make_library() {
    struct song_node** library = calloc(27, sizeof(struct song_node*));
    int index = 0;
    for (index = 0; index < 27; index++) {
        library[index] = NULL;
    }
    return library;
}

int get_index(char *str) {
    int index = (int) tolower(str[0]) - 97;
    if (index < 0 || index > 25) index = 26;
    return index;
}

struct song_node ** add_library_song(struct song_node **library, char *name, char *artist) {
    int index = get_index(artist);
    library[index] = insert_alpha(library[index], name, artist);
    return library;
}

struct song_node ** delete_library_song(struct song_node **library, char *name, char *artist) {
    int index = get_index(artist);
    library[index] = remove_node(library[index], name, artist);
    return library;
}

struct song_node * get_by_library_song(struct song_node **library, char *name, char *artist) {
    int index = get_index(artist);
    return get_by_song(library[index], name, artist);
}

struct song_node * get_by_library_artist(struct song_node **library, char *artist) {
    int index = get_index(artist);
    return library[index];
}

void shuffle_library(struct song_node ** library, int n) {
    int i;
    printf("[ ");
    for (i = 0; i < n; i++) {
        int index = rand() % 27;
        while (library[index] == 0) {
            index = rand() % 27;
        }
        print_node(get_random_song(library[index]));
    }
    printf("]\n");
}

void print_library_letter(struct song_node** library, char c) {
    int index = (int) tolower(c) - 97;
    if (index < 0 || index > 25) index = 26;
    print_list(library[index]);
}

void print_library_artist(struct song_node** library, char *artist) {
    int index = get_index(artist);
    struct song_node *temp = library[index];
    printf("[ ");
    while (temp) {
        if (strcasecmp(temp->artist, artist)) print_node(temp);
        temp = (temp->next);
    }
	printf("]\n");
}

void print_library(struct song_node** library) {
    int index;
    int printed = 0;
    for (index = 0; index < 27; index++) {
        if (library[index]) {
            if (index == 26) printf("N/A: ");
            else printf("%c: ", 65+index);
            print_list(library[index]);
            printed = 1;
        }
    }
    if (printed == 0) printf("Library is empty.\n");
}

struct song_node ** free_library(struct song_node** library) {
    int index;
    for (index = 0; index < 27; index++) {
        library[index] = free_list(library[index]);
    }
    free(library);
    library = NULL;
    return library;
}