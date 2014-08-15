/* OS specific headers. */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


/** Detach from the terminal and run in the background.
 *
 * @param nochdir If 0, change PWD to "/".
 * @param noclose If 0, redirect stdin/out/err to "/dev/null".
 *
 * @return 0 if daemonized (child should continue).
 * @return Positive if daemonized (parent should exit).
 * @return Negative if error occured.
 */
int utils_daemonize( int nochdir, int noclose )
{
	pid_t parent = getpid(); /* XXX: must be called before fork() */


	switch( fork() ) {
	case -1:
		return -(!0);

	case 0:
		break;

	default:
		return !0;
	}

	while( 0 == kill(parent, 0) ) {
		usleep( 10 );
	}

	if( -1 == setsid() ) {
		return -(!0);
	}

	if( 0 == nochdir ) {
		if( -1 == chdir("/") ) {
			return -(!0);
		}
	}

	if( 0 == noclose ) {
		int fd = open( "/dev/null", O_RDWR );
		if( -1 == fd ) {
			return -(!0);
		}

		dup2( fd, STDIN_FILENO );
		dup2( fd, STDOUT_FILENO );
		dup2( fd, STDERR_FILENO );

		if( 2 < fd ) {
			close( fd );
		}
	}

	return 0;
}

/** Return IP address string.
 *
 * @param saddr Address structure.
 *
 * @return IP string.
 */
const char *utils_get_ip( struct sockaddr_in saddr )
{
	return inet_ntoa( saddr.sin_addr );
}
