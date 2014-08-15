/* OS specific headers. */
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

/* Program specific headers. */
#include "log.h"
#include "config.h"


/* Private variables. */
static int run = 0;
static int sd = -1;


/** Shut down server. */
void server_shutdown( void )
{
	if( -1 != sd ) {
		run = 0;
		shutdown( sd, SHUT_RDWR );
		close( sd );
		sd = -1;
	}
}

/** Initialize server.
 *
 * @return 0 if server has been initialized.
 * @return Non-zero if error occurred.
 */
int server_init( void )
{
	sd = socket( AF_INET, SOCK_STREAM, 0 );
	if( -1 == sd ) {
		log_error( "could not create socket: %m" );
		return !0;
	}

	int reuseaddr = 1;
	if( -1 == setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (void *)&reuseaddr, sizeof(reuseaddr)) ) {
		log_error( "could not set socket options: %m" );
		server_shutdown();
		return !0;
	}

	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = INADDR_ANY;
	saddr.sin_port = htons( config_get_int(CONFIG_PORT) );
	if( -1 == bind(sd, (struct sockaddr *)&saddr, sizeof(saddr)) ) {
		log_error( "could not bind name to socket: %m" );
		server_shutdown();
		return !0;
	}

	if( -1 == listen(sd, 1) ) {
		log_error( "could not listen on socket: %m" );
		server_shutdown();
		return !0;
	}

	run = !0;

	return 0;
}

/** Listen for clients.
 *
 * @return 0 if server has stop listening.
 * @return Non-zero if error occurred.
 */
int server_listen( void )
{
	return 0;
}
