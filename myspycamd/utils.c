/* C standard library headers. */
#include <stdlib.h>
#include <ctype.h>

/* OS specific headers. */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* Program specific headers. */
#include "log.h"


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

/** Print data in human readable format.
 *
 * @param data Data buffer.
 * @param size Data buffer size.
 */
void utils_dump_bytes( char *data, int size )
{
	if( NULL == data ) {
		log_debug( "size: %d data: NULL", size );
		return;
	}
	else
	if( 0 == size ) {
		log_debug( "size: 0 data: ?" );
		return;
	}

	char *ptr1;
	int count;
	for( count = 0, ptr1 = data;
	     data+size > ptr1;
	     ptr1++ ) {
		if( 0 == isprint(ptr1[0]) ||
		    0 != isspace(ptr1[0]) ||
		    '<' == ptr1[0] ||
		    '>' == ptr1[0] ) {
			count += 4;
		}
		else {
			count++;
		}
	}

	char *buf = malloc( count+1 );
	if( NULL == buf ) {
		log_error( "could not allocate %d bytes for buffer", count+1 );
		return;
	}

	char *ptr2;
	for( count = 0, ptr1 = data, ptr2 = buf;
	     data+size > ptr1;
	     ptr1++ ) {
		if( 0 == isprint(ptr1[0]) ||
		     0 != isspace(ptr1[0]) ||
		    '<' == ptr1[0] ||
		    '>' == ptr1[0] ) {
			ptr2[0] = '<';
			ptr2[1] = ( (unsigned char)ptr1[0] & 0xF0 ) >> 4;
			ptr2[1] += ptr2[1] < 10 ? '0' : '7';
			ptr2[2] = (unsigned char)ptr1[0] & 0x0F;
                        ptr2[2] += ptr2[2] < 10 ? '0' : '7';
			ptr2[3] = '>';
			ptr2 += 4;
		}
		else {
			ptr2[0] = ptr1[0];
			ptr2++;
		}
	}
	ptr2[0] = '\0';

	log_debug( "size: %d data: %s", size, buf );

	free( buf );
}
