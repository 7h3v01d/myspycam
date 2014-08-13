/* C standard library headers. */
#include <stdlib.h>
#include <stdio.h>

/* OS specific headers. */
#include <unistd.h>

/* Program specific headers. */
#include "config.h"


/* Private variables. */
static int daemonize = !0;
static int port = 46004;


/** Parse command line parameters.
 *
 * @param argc Number of arguments.
 * @param argv Array of arguments.
 *
 * @return 0 if successful.
 * @return Non-zero if error occured.
 */
int config_parse_args( int argc, char *argv[] )
{
	int c;
	while( -1 != (c = getopt(argc, argv, "hDp:")) ) {
		switch( c ) {
		case 'D':
			daemonize = 0;
			break;

		case 'p':
			port = atoi( optarg );
			if( 1 > port ||
			    65536 < port ) {
				printf( "invalid argument value: '-p'\n" );
				return !0;
			}
			break;

		case 'h':
			return !0;

		default:
			printf( "invalid argument: '-%c'\n", c );
			return !0;
		}
	}

	return 0;
}

/** Get integer configuration option.
 *
 * @param option Option name.
 *
 * @return Configuration option.
 */
int config_get_int( int option )
{
	switch( option ) {
	case CONFIG_DAEMONIZE:
		return daemonize;

	case CONFIG_PORT:
		return port;
	}

	return 0;
}

/** Get string configuration option.
 *
 * @param option Option name.
 *
 * @return Configuration option.
 */
const char *config_get_str( int option )
{
	(void)option;
	return (void *)0;
}
