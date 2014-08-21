/* C standard library headers. */
#include <stdlib.h>

/* OS specific headers. */
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>

/* Program specific headers. */
#include "config.h"
#include "log.h"


/* Private variables. */
static int fd = -1;


/** Close camera. */
void cam_close( void )
{
	if( -1 != fd ) {
		close( fd );
		fd = -1;
	}
}

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

	struct v4l2_format fmt = {
		.type = V4L2_BUF_TYPE_VIDEO_CAPTURE,
		.fmt.pix = {
			.width = 640,
			.height = 480,
			.pixelformat = V4L2_PIX_FMT_JPEG,
			.field = V4L2_FIELD_NONE,
		},
	};

	if( -1 == ioctl(fd, VIDIOC_S_FMT, &fmt) ) {
		log_error( "could not initialize camera: %m" );
		cam_close();
		return !0;
	}
	if( 640 != fmt.fmt.pix.width ||
	    480 != fmt.fmt.pix.height ||
	    V4L2_PIX_FMT_JPEG != fmt.fmt.pix.pixelformat ) {
		log_error( "could not initialize camera" );
		cam_close();
		return !0;
	}

	return 0;
}

/** Get image from camera.
 *
 * @return Buffer with image data.
 * @return NULL if error occurred.
 */
const char *cam_image( void )
{
	
	return NULL;
}
