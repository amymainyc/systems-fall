#include <stdio.h>
#include <stdlib.h>

int mystrlen( char *s ) {
	int length = 0;
	while (*s != 0) {
		s++;
		length++;
	}
	return length; 
}

char * mystrcpy( char *dest, char *source ) {
	int i = 0;
	while (source[i] != 0) {
		dest[i] = source[i];
		i++;
	}
	dest[i+1] = '\0';
	return dest; 
}

char * mystrncat( char *dest, char *source, int n) {
	int dest_len = mystrlen(dest);
	int i = dest_len;
	while (source[i - dest_len] != 0 && n != 0) {
		dest[i] = source[i - dest_len];
		i++;
		n--;
	}
	dest[i+1] = '\0';
	return dest; 
}

char * mystrchr( char *s, char c ) {
	while (*s != c && *s != '\0') {
		s++;
	}
	if (c != '\0' && *s == '\0') return '\0';
	return s; 
}

int mystrcmp( char *s1, char *s2 ) {
	int i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i]) {
		i++;
	}
	if (s1[i] == s2[i]) return 0;
	if (s1[i] == '\0') return -1;
	if (s2[i] == '\0') return 1;
}


