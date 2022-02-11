#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlist.h"
#include "library.h"
#include <time.h>

int main() {
    struct song_node *song_list;
    srand(time(NULL));
    song_list = NULL;
    song_list = insert_front(song_list, "Orion", "Kupla");

    printf("LINKED LIST TESTS -------------------------------------------- \n");

    printf("====================================\nTesting print_node: \n");
    print_node(song_list);

    printf("\n====================================\nTesting print_list: \n");
    print_list(song_list);

    printf("====================================\nTesting insert_front: \n");
    song_list = insert_front(song_list, "Fresh Air", "Maasho");
    song_list = insert_front(song_list, "From The Garden", "Lil Uzi Vert");
    song_list = insert_front(song_list, "ATTENTION!", "XXXTENTACION");
    song_list = insert_front(song_list, "Remote Control", "Kanye West");
    song_list = insert_front(song_list, "Pure Souls", "Kanye West");
    print_list(song_list);
    free_list(song_list);


    printf("====================================\nTesting compare_nodes (helper function): \n");
    struct song_node *a = make_node("Fresh Air", "Maasho");
    struct song_node *b = make_node("Remote Control", "Kanye West");
    struct song_node *c = make_node("Pure Souls", "Kanye West");
    printf("%d\n", compare_nodes(a, b));
    printf("%d\n", compare_nodes(b, c));
    printf("%d\n", compare_nodes(a, c));

    printf("====================================\nTesting insert_alpha: \n");
    struct song_node *song_list2;
    song_list2 = NULL;
    song_list2 = insert_alpha(song_list2, "Fresh Air", "Maasho");
    song_list2 = insert_alpha(song_list2, "From The Garden", "Lil Uzi Vert");
    song_list2 = insert_alpha(song_list2, "ATTENTION!", "XXXTENTACION");
    song_list2 = insert_alpha(song_list2, "Remote Control", "Kanye West");
    song_list2 = insert_alpha(song_list2, "Pure Souls", "Kanye West");
    song_list2 = insert_alpha(song_list2, "Why Am I Waiting", "Papithbk");
    song_list2 = insert_alpha(song_list2, "Moonflowers", "softy");
    song_list2 = insert_alpha(song_list2, "Nevada", "Vicetone");
    song_list2 = insert_alpha(song_list2, "Fast Flow", "Ty Noam Frankel");
    print_list(song_list2);

    printf("====================================\nTesting get_by_song: \n");
    print_node(get_by_song(song_list2, "Moonflowers", "softy"));
    printf("\n");

    printf("====================================\nTesting get_by_artist: \n");
    print_node(get_by_artist(song_list2, "Kanye West"));
    printf("\n");

    printf("====================================\nTesting get_random_song: \n");
    print_node(get_random_song(song_list2));
    printf("\n");

    printf("====================================\nTesting remove_node: \n");
    print_list(song_list2);
    song_list2 = remove_node(song_list2, "Orion", "Kupla");
    print_list(song_list2);
    song_list2 = remove_node(song_list2, "Fast Flow", "Ty Noam Frankel");
    print_list(song_list2);
    song_list2 = remove_node(song_list2, "Nevada", "Vicetone");
    print_list(song_list2);
    song_list2 = remove_node(song_list2, "ATTENTION!", "XXXTENTACION");
    print_list(song_list2);

    printf("====================================\nTesting free_list: \n");
    song_list2 = free_list(song_list2);
    print_list(song_list2);
    
    printf("====================================\n");


    printf("MUSIC LIBRARY TESTS -------------------------------------------- \n");
    struct song_node **library = make_library();

    printf("====================================\nTesting add_library_song: \n");
    add_library_song(library, "Brightside", "mike.");
    add_library_song(library, "to the grave", "Bea Miller");
    add_library_song(library, "God's Work", "IAMDDB");
    add_library_song(library, "So Pretty", "Reyanna Maria");
    add_library_song(library, "These Days", "mike.");
    add_library_song(library, "Revenge", "XXXTENTACION");
    add_library_song(library, "NDA", "Billie Eilish");
    add_library_song(library, "Something Big", "Shawn Mendes");
    add_library_song(library, "if this is the last time", "LANY");
    add_library_song(library, "Perfectly Wrong", "Shawn Mendes");
    add_library_song(library, "morbid mind", "Jack Keys");
    add_library_song(library, "TROLLZ", "6ix9ine");
    add_library_song(library, "Groundhog Day", "Em Beihold");
    add_library_song(library, "I Hear a Symphony", "Cody Fry");
    add_library_song(library, "Lost Me", "mike.");
    add_library_song(library, "Bb", "MØ");
    add_library_song(library, "good 4 u", "Olivia Rodrigo");
    add_library_song(library, "Fault", "mike.");
    add_library_song(library, "so sick", "mike.");
    add_library_song(library, "Purple Like the Summer Rain", "MØ");
    print_library(library);

    printf("====================================\nTesting delete_library_song: \n");
    printf("\nDeleting good 4 u - Olivia Rodrigo\n");
    delete_library_song(library, "good 4 u", "Olivia Rodrigo");
    print_library(library);
    printf("\nDeleting NDA - Billie Eilish\n");
    delete_library_song(library, "NDA", "Billie Eilish");
    print_library(library); 
    printf("\nDeleting I Hear a Symphony - Cody Fry\n");
    delete_library_song(library, "I Hear a Symphony", "Cody Fry");
    print_library(library); 

    printf("====================================\nTesting get_by_library_song: \n");
    print_node(get_by_library_song(library, "TROLLZ", "6ix9ine"));

    printf("\n====================================\nTesting get_by_library_artist: \n");
    print_node(get_by_library_artist(library, "Reyanna Maria"));

    printf("\n====================================\nTesting shuffle_library: \n");
    shuffle_library(library, 6);

    printf("====================================\nTesting print_library_letter: \n");
    print_library_letter(library, 'm');

    printf("====================================\nTesting print_library_artist: \n");
    print_library_artist(library, "mike.");

    printf("====================================\nTesting print_library: \n");
    print_library(library);

    printf("====================================\nTesting free_library: \n");
    free_library(library);
    print_library(library);

    return 0;
}