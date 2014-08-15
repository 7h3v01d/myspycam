/* C standard library headers. */
#include <stdlib.h>
#include <stdio.h>

/* OS specific headers. */
#include <unistd.h>
#include <signal.h>

/* Program specific headers. */
#include "config.h"
#include "utils.h"
#include "log.h"
#include "server.h"


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
		int ret = utils_daemonize( 0, 0 );
		if( 0 < ret ) {
			/* XXX: free all resources here */
			return EXIT_SUCCESS;
		}
		else
		if( 0 > ret ) {
			printf( "WARNING: could not daemonize: %m\n" );
		}
	}

	log_open();

	signal( SIGCHLD, SIG_IGN );
	signal( SIGTERM, terminate );

	if( 0 != server_init() ) {
		log_error( "could not initialize server" );
		terminate( 0 );
		return EXIT_FAILURE;
	}

	if( 0 != server_listen() ) {
		log_error( "could not listen on socket" );
		terminate( 0 );
		return EXIT_FAILURE;
	}

	/* XXX: free all resources here */
	terminate( 0 );

	return EXIT_SUCCESS;
}


/** Show program help. */
static void help( void )
{
	printf( "myspycamd - myspycam daemon\n"
		"built on " __DATE__ " at " __TIME__ "\n"
		"\n"
		"usage: myspycamd [-h] [-D] [-p port] [-d priority]\n"
		"\n"
		"  -h   show help\n"
		"  -D   do not daemonize\n"
		"  -p   port number\n"
		"  -d   debug priority\n" );
}

/** Terminate program.
 *
 * @param sig Signal number.
 */
static void terminate( int sig )
{
	static int force = 0;


	if( 0 != sig ) {
		log_info( "SIGTERM received" );
	}

	if( 0 != force ) {
		/* XXX: forced to terminate */
		log_warning( "forced to terminate" );
		exit( EXIT_SUCCESS );
	}

	force = !0;

	/* XXX: free all resources here */
	server_shutdown();
	log_close();
}
