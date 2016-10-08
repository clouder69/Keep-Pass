/*
 *
 * Keep Pass [1.0]
 * core.c
 * clouder - 2016
 *
 */
#include "init.h"

int main(int argc, char *argv[]) {

	/* More than 1 and less or equal than 4 arguments */
	if(argc < 2 || argc > 4) {
		show_options();
		return 0;
	}

	if( access( PASS_DIR, F_OK ) != 0 ) {
		
		SHARP;
		printf( "# Directory [%s] for program doesn't exists.\n", PASS_DIR );
		printf( "# Create this directory!\n" );
		SHARP;
		return 0;
	}

	/* Get password option */
	if( strcmp( argv[1], "get" ) == 0 ) {
		
		if( argc != 3 ) {
			show_options();
			return 0;
		}

		FILE *get;
		char file_name[256];
		char file_content[256];

		sprintf( file_name, "%s%s%s", PASS_DIR, argv[2], PASS_SUFFIX );

		get = fopen( file_name, "r" );
		fgets( file_content, 256, get );
		fclose( get );

		/* Copy password to clipboard */
		sprintf( file_name, "echo \"%s\" | xclip -selection c", decrypt( file_content ) );
		system( file_name );

		SHARP;
		printf( "# Password [%s] was copied to your clipboard.\n", argv[2] );
		SHARP;

		return 0;
	}
	/* Save password option */
	else if( strcmp( argv[1], "save" ) == 0 ) {
		
		if( argc != 4 ) {
			show_options();
			return 0;
		}

		FILE *save;
		char file_name[256];

		sprintf( file_name, "%s%s%s", PASS_DIR, argv[2], PASS_SUFFIX );

		save = fopen( file_name, "w" );
		fprintf( save, "%s", encrypt( argv[3] ) );
		fclose( save );

		SHARP;
		printf( "# Password was saved with name: %s\n", argv[2] );
		SHARP;

		return 0;
	}
	/* Remove password option */
	else if( strcmp( argv[1], "rm" ) == 0 ) {
		
		if( argc != 3 ) {
			show_options();
			return 0;
		}

		char file_name[256];

		sprintf( file_name, "%s%s%s", PASS_DIR, argv[2], PASS_SUFFIX );

		if( remove( file_name ) == 0 ) {
			
			SHARP;
			printf("# Password [%s] was successfully deleted.\n", argv[2]);
			SHARP;

			return 0;
		}

		SHARP;
		printf("# Some error with deleting file has occured!\n");
		SHARP;

		return 0;
	}
	/* Shows` avaible password */
	else if( strcmp( argv[1], "all" ) == 0 ) {

		if( argc != 2 ) {
			show_options();
			return 0;
		}

		char name[50];

		tinydir_dir dir;
		tinydir_open(&dir, PASS_DIR);

		SHARP;
		printf("# List of avaible passwords:\n");
		SHARP;

		while (dir.has_next)
		{
			tinydir_file file;
			tinydir_readfile(&dir, &file);

			if( file.is_dir ) {
				tinydir_next(&dir);
				continue;
			}

			sprintf( name, "%s", file.name );

			printf("# %s\n", remove_end( name, 6 ) );
			
			tinydir_next(&dir);
		}

		tinydir_close(&dir);

		SHARP;

		return 0;
	}

	/* Wrong option! */
	show_options();

	return 0;
}
