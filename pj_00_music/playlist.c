#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stddef.h>

struct song_node {
	char name[100];
	char artist[100];
	struct song_node *next;
};

struct song_node * make_node(char *name, char *artist) {
	struct song_node * a; 
	a = malloc(sizeof(struct song_node));
	strcpy(a->name, name);
	strcpy(a->artist, artist);
	a->next = NULL;
	return a;
}

struct song_node * insert_front(struct song_node *song_list, char *name, char *artist) {
    struct song_node *a = make_node(name, artist);
    a->next = song_list;
    return a;
}

int compare_nodes(struct song_node *s1, struct song_node *s2) {
	if (strcasecmp(s1->artist, s2->artist)) return strcasecmp(s1->artist, s2->artist);
	else {
		if (strcasecmp(s1->name, s2->name)) return strcasecmp(s1->name, s2->name);
		else return 0;
  	}
}

struct song_node * insert_alpha(struct song_node *song_list, char *name, char *artist) {
	struct song_node *song = make_node(name, artist);
	if (song_list == 0) return song;
	struct song_node *previous = 0;
    struct song_node *current = song_list;
	while (current) {
		if (compare_nodes(current, song) > 0) {
			break;
		}
		previous = current;
		current = current->next;
	}
	song->next = current;
	if (previous) previous->next = song;
	else song_list = song;
	return song_list;
}

struct song_node * remove_node(struct song_node *song_list, char *name, char *artist) {
	if (song_list == NULL) return song_list;
	if (song_list->next == NULL) {
		if (strcasecmp(song_list->name, name) == 0 && strcasecmp(song_list->artist, artist) == 0) {
			free(song_list);
			return NULL;
		} else return song_list;
	}

	struct song_node *previous = 0;
    struct song_node *current = song_list;
    while (current && (strcasecmp(current->name, name) || strcasecmp(current->artist, artist))) {
        previous = current;
        current = current->next;
    }
    if (current == NULL) return song_list;
    if (previous) {
        previous->next = current->next;
    } else {
        previous = current->next;
    }
    free(current);
    return song_list;
}

void print_node(struct song_node *a) {
    if (a) printf("{ %s, %s } ", a->name, a->artist);
	else printf("\nNo song found.\n");
}

void print_list(struct song_node *song_list) {
	printf("[ ");
    while (song_list) {
        print_node(song_list);
        song_list = song_list->next;
    }
	printf("]\n");
}

struct song_node * get_by_artist(struct song_node *song_list, char *artist) {
	struct song_node *temp = song_list;
	while (temp) {
		if (strcmp(temp->artist, artist) == 0) break;
		temp = temp->next;
	}
	return temp;
}

struct song_node * get_by_song(struct song_node *song_list, char *name, char *artist) {
	struct song_node *temp = song_list;
	while (temp) {
		if (strcmp(temp->name, name) == 0 && strcmp(temp->artist, artist) == 0) break;
		temp = temp->next;
	}
	return temp;
}

struct song_node * get_random_song(struct song_node *song_list) {
	int size = 0;
	struct song_node *temp = song_list;
	while (temp) {
		size++;
		temp = temp->next;
	}
	int song_index = rand() % size;
	temp = song_list;
	while (song_index) {
		temp = temp->next;
		song_index--;
	}
	return temp;
}

struct song_node * free_list(struct song_node *song_list) {
    struct song_node *temp = song_list;
	while (song_list) {
		song_list = song_list->next;
		free(temp);
		temp = NULL;
		temp = song_list;
	}
	return NULL;
}
