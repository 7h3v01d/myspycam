/* OS specific headers. */
#include <syslog.h>

/* Program specific headers. */
#include "config.h"


/** Open log. */
void log_open( void )
{
	openlog( "myspycamd", LOG_NDELAY | LOG_PID, LOG_DAEMON );
	setlogmask( LOG_UPTO(config_get_int(CONFIG_DEBUG)) );
}

/** Close log. */
void log_close( void )
{
	closelog();
}
