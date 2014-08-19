/* OS specific headers. */
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* Program specific headers. */
#include "config.h"
#include "log.h"


/* Private variables. */
static int fd = -1;


/** Open camera.
 *
 * @return 0 if success.
 * @return Non-zero if error occurred.
 */
int cam_open( void )
{
	fd = open( config_get_str(CONFIG_DEVICE), O_RDWR );
	if( -1 == fd ) {
		log_error( "could not open camera: %m" );
		return !0;
	}

	return 0;
}

/** Close camera. */
void cam_close( void )
{
	if( -1 != fd ) {
		close( fd );
		fd = -1;
	}
}
