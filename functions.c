/*
 * functions.c
 */

#include "init.h"

void show_options() {
	SHARP;
	printf("# Keep Pass Options:\n");
	printf("# kpass get [name]\n");
	printf("# kpass save [name] [password]\n");
	printf("# kpass rm [name]\n");
	printf("# kpass all\n");
	SHARP;
}

char* encrypt_caesar( char *text ) {

	int i;
	unsigned char h;

	for( i=0; i<strlen(text); i++ ) {
		
		h = text[i];
		h += 3;
		text[i] = h;
		 
	}

	return text;
}

char* decrypt_caesar( char *text ) {

	int i;
	unsigned char h;

	for( i=0; i<strlen(text); i++) {
		
		h = text[i];
		h -= 3;
		text[i] = h;

	}

	return text;
}

char* encrypt( char *text ) {

	if( strlen(text) <= 2 )
		return text;

	int i; //iterator
	unsigned char h; //helper
	unsigned char l; //last char

	l = 0;

	for( i=0; i<strlen(text); i++ ) {

		h = text[i];

		h += l;
		text[i] = h;

		l = h - l;

	}	

	return text;
}

char* decrypt( char *text ) {

	if( strlen(text) <= 2 )
		return text;

	int i;
	unsigned char h;
	unsigned char l;

	l = 0;

	for( i=0; i<strlen(text); i++ ) {

		h = text[i];

		h -= l;
		text[i] = h;

		l = h;

	}

	return text;
}

char* remove_end( char *text, int len ) {

	int size, i;
	
	size = strlen( text );

	for( i=(size - len)-1; i<size; i++ ) {
		
		text[i] = '\0';

	}

	return text;
}
