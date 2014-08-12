/* C standard library headers. */
#include <stdlib.h>
#include <stdio.h>

/* OS specific headers. */
#include <unistd.h>
#include <signal.h>

/* Program specific headers. */
#include "config.h"
#include "utils.h"


/* Private function prototypes. */
static void help( void );
static void terminate( int sig );


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

	signal( SIGCHLD, SIG_IGN );
	signal( SIGTERM, terminate );

	/* XXX: free all resources here */

	return EXIT_SUCCESS;
}


/** Show program help. */
static void help( void )
{
	printf( "myspycamd - myspycam daemon\n"
		"built on " __DATE__ " at " __TIME__ "\n"
		"\n"
		"usage: myspycamd [-h] [-D]\n"
		"\n"
		"  -h   show help\n"
		"  -D   do not daemonize\n" );
}

/** Terminate program.
 *
 * @param sig Signal number.
 */
static void terminate( int sig )
{
	(void)sig;


	static int force = 0;


	if( 0 != force ) {
		/* XXX: forced to terminate */
		exit( EXIT_SUCCESS );
	}

	force = !0;

	/* XXX: free all resources here */
}
