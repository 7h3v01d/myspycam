/* C standard library headers. */
#include <stdlib.h>
#include <stdio.h>

/* OS specific headers. */
#include <unistd.h>
#include <signal.h>
#include <syslog.h>

/* Program specific headers. */
#include "config.h"
#include "utils.h"
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
		int ret = daemonize( 0, 0 );
		if( 0 < ret ) {
			/* XXX: free all resources here */
			return EXIT_SUCCESS;
		}
		else
		if( 0 > ret ) {
			printf( "WARNING: could not daemonize: %m\n" );
		}
	}

	openlog( "myspycamd", LOG_NDELAY | LOG_PID, LOG_DAEMON );
	setlogmask( LOG_UPTO(config_get_int(CONFIG_DEBUG)) );

	signal( SIGCHLD, SIG_IGN );
	signal( SIGTERM, terminate );

	if( 0 != server_init() ) {
		syslog( LOG_ERR, "ERROR: could not initialize server" );
		server_shutdown();
		closelog();
		return EXIT_FAILURE;
	}

	if( 0 != server_listen() ) {
		syslog( LOG_ERR, "ERROR: could not listen on socket" );
		server_shutdown();
		closelog();
		return EXIT_FAILURE;
	}

	/* XXX: free all resources here */
	server_shutdown();

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
		"  -d   debug priority" );
}

/** Terminate program.
 *
 * @param sig Signal number.
 */
static void terminate( int sig )
{
	(void)sig;


	static int force = 0;


	syslog( LOG_INFO, "INFO: SIGTERM received" );

	if( 0 != force ) {
		/* XXX: forced to terminate */
		syslog( LOG_WARNING, "WARNING: forced to terminate" );
		exit( EXIT_SUCCESS );
	}

	force = !0;

	/* XXX: free all resources here */
	server_shutdown();
}
