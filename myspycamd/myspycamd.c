/* C standard library headers. */
#include <stdlib.h>
#include <stdio.h>

/* OS specific headers. */
#include <unistd.h>

/* Program specific headers. */
#include "config.h"


/* Private function prototypes. */
void help( void );


/** Entry point.
 *
 * @param argc Number of arguments.
 * @param argv Array of arguments.
 *
 * @return Exit code.
 */
int main( int argc, char **argv )
{
	(void)argc;
	(void)argv;
	return EXIT_SUCCESS;
}


/** Show program help. */
void help( void )
{
	printf( "myspycamd - myspycam daemon\n"
		"usage: myspycamd\n" );
}
