/* C standard library headers. */
#include <stdio.h>

/* OS specific headers. */
#include <unistd.h>


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
	(void)argc;
	(void)argv;

	int c;
	while( -1 != (c = getopt(argc, argv, "hD")) ) {
		switch( c ) {
		case 'D':
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

