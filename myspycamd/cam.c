/* OS specific headers. */
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* Program specific headers. */
#include "log.h"


/* Private variables. */
static int fd = -1;


int cam_open( void )
{
	fd = open( "/dev/video0", O_RDWR );
	if( -1 == fd ) {
		log_error( "could not open camera: %m" );
		return !0;
	}

	return 0;
}

void cam_close( void )
{
	if( -1 != fd ) {
		close( fd );
		fd = -1;
	}
}
