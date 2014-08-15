/* OS specific headers. */
#include <unistd.h>

/* Private variables. */
static int sd = -1;


/** Initialize server. */
int server_init( void )
{
	return 0;
}

/** Listen for incoming connections.
 *
 * @return 0 if server has been stopped.
 * @return Non-zero if error occurred.
 */
int server_listen( void )
{
	return 0;
}

/** Shut down server. */
void server_shutdown( void )
{
	if( -1 != sd ) {
		close( sd );
		sd = -1;
	}
}
