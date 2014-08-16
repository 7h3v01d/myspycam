/* C standard library headers. */
#include <stdlib.h>

/* OS specific headers. */
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

/* Program specific headers. */
#include "log.h"


/* Private variables. */
static int run = 0;
static int sd = -1;


/** Shut down client. */
void client_shutdown( void )
{
	if( -1 != sd ) {
		run = 0;
		shutdown( sd, SHUT_RDWR );
		close( sd );
		sd = -1;
	}
}

/** Terminate client program.
 *
 * @param sig Signal number.
 */
void client_terminate( int sig )
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
	client_shutdown();
	log_close();
}

/** Initialize client.
 *
 * @param fd Client socket.
 */
void client_init( int fd )
{
	sd = fd;
	run = !0;

	int flags = fcntl( sd, F_GETFL );
	if( -1 == flags ) {
		log_error( "could not get socket flags: %m" );
		flags = 0;
	}

	flags |= O_NONBLOCK;
	if( -1 == fcntl(sd, F_SETFL, flags) ) {
		log_error( "could not set socket flags: %m" );
	}

	signal( SIGTERM, client_terminate );
}

void client_handle( void )
{
}
