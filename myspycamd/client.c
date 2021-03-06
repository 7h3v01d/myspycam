/* C standard library headers. */
#include <stdlib.h>

/* OS specific headers. */
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

/* Program specific headers. */
#include "log.h"
#include "utils.h"
#include "protocol.h"
#include "cam.h"


/* Private function prototypes. */
static void client_request( char *data, int size );


/* Private variables. */
static int run = 0;
static int sd = -1;
static char *data_buff = NULL;
static int data_len = 0;
static int data_size = 0;


/** Shut down client. */
void client_shutdown( void )
{
	if( -1 != sd ) {
		run = 0;
		shutdown( sd, SHUT_RDWR );
		close( sd );
		sd = -1;
	}

	if( data_buff != NULL ) {
		free( data_buff );
		data_buff = NULL;
		data_len = 0;
		data_size = 0;
	}

	cam_close();
}

/** Terminate client program.
 *
 * @param sig Signal number.
 */
void client_terminate( int sig )
{
	static int force = 0;


	if( 0 != sig ) {
		log_info( "SIGTERM received" );

		if( 0 != force ) {
			/* XXX: forced to terminate */
			log_warning( "forced to terminate" );
			exit( EXIT_SUCCESS );
		}

		force = !0;
	}

	/* XXX: free all resources here */
	client_shutdown();
	log_close();
}

/** Initialize client.
 *
 * @param fd Client socket.
 */
void client_init( int fd )
{
	sd = fd;
	run = !0;

	int flags = fcntl( sd, F_GETFL );
	if( -1 == flags ) {
		log_error( "could not get socket flags: %m" );
		flags = 0;
	}

	flags |= O_NONBLOCK;
	if( -1 == fcntl(sd, F_SETFL, flags) ) {
		log_error( "could not set socket flags: %m" );
	}

	signal( SIGTERM, client_terminate );

	if( 0 != cam_open() ) {
		log_error( "could not open camera" );
		client_shutdown();
	}
}

void client_handle( void )
{
	log_debug( "awaiting data from client" );

	int request_size = 0;

	while( 0 != run ) {
		if( data_size+PROTOCOL_BUFF_SIZE_MIN >= data_len ) {
			if( PROTOCOL_BUFF_SIZE_MAX < data_len+PROTOCOL_BUFF_SIZE_MIN ) {
				log_error( "client sent too much data" );
				break;
			}

			char *data_tmp = realloc( data_buff, data_len+PROTOCOL_BUFF_SIZE_MIN );
			if( NULL == data_tmp ) {
				log_critical( "not enough memory for client data" );
				break;
			}
			data_buff = data_tmp;
			data_len += PROTOCOL_BUFF_SIZE_MIN;
		}

		int max = ( 0 == request_size ) ? (int)PROTOCOL_REQ_SIZE_MIN : (request_size-data_size)%PROTOCOL_BUFF_SIZE_MIN;
		ssize_t size = read( sd, data_buff+data_size, max );
		if( 0 == size ) {
			log_info( "client closed connection" );
			break;
		}
		else
		if( -1 == size ) {
			if( EAGAIN == errno ) {
				if( 0 == data_size ||
				    data_size < request_size) {
					usleep( 1000 );
					continue;
				}
			}
			else {
				break;
			}
		}
		else {
			data_size += size;

			if( 0 == request_size ) {
				int ret = protocol_verify_header( data_buff, data_size );
				if( 0 == ret ) {
					request_size = *(int *)data_buff;
					log_debug( "request header verified" );
				}
				else
				if( 0 < ret ) {
					log_error( "invalid request header" );
					client_shutdown();
				}
			}

			continue;
		}

		log_debug( "%d bytes read from client", data_size );

		utils_dump_bytes( data_buff, data_size );

		client_request( data_buff, data_size );

		if( NULL != data_buff &&
		    PROTOCOL_BUFF_SIZE_MIN < data_len ) {
			free( data_buff );
			data_buff = NULL;
			data_len = 0;
		}
		data_size = 0;
		request_size = 0;

		log_debug( "awaiting data from client" );
	}

	client_shutdown();
}

static void client_request( char *data, int size )
{
	if( 0 != protocol_verify_request(data, size) ) {
		log_error( "invalid request data" );
		client_shutdown();
		return;
	}

	protocol_header_t *h = (protocol_header_t *)data;
	switch( h->request ) {
	case PROTOCOL_REQUEST_IMAGE:
		protocol_request_image( (protocol_request_image_t *)data );
		break;
	}
}
