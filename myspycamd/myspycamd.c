/* C standard library headers. */
#include <stdlib.h>
#include <stdio.h>

/* OS specific headers. */
#include <unistd.h>

/* Program specific headers. */
#include "config.h"
#include "utils.h"


/* Private function prototypes. */
void help( void );


/** Entry point.
 *
 * @param argc Number of arguments.
 * @param argv Array of arguments.
 *
 * @return Exit code.
 */
int main( int argc, char *argv[] )
{
	if( 0 != config_parse_args(argc, argv) ) {
		help();
		return EXIT_FAILURE;
	}

	if( 0 != config_get_int(CONFIG_DAEMONIZE) ) {
		int ret = daemonize( 0, 0 );
		if( 0 < ret ) {
			/* XXX: free all resources here */
			return EXIT_SUCCESS;
		}
		else
		if( 0 > ret ) {
			printf( "could not daemonize: %m\n" );
		}
	}

	return EXIT_SUCCESS;
}


/** Show program help. */
void help( void )
{
	printf( "myspycamd - myspycam daemon\n"
		"usage: myspycamd [-h] [-D]\n"
		"options: -h  show help\n"
		"         -D  do not daemonize\n" );
}
