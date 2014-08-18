/* Program specific headers. */
#include "protocol.h"
#include "log.h"


/** Verify request header.
 *
 * @param data Request data.
 * @param size Request data size.
 *
 * @return 0 if header is correct.
 * @return Positive if error occurred.
 * @return Negative if there is not enough data.
 */
int protocol_verify_header( char *data, int size )
{
	if( (int)sizeof(protocol_header_t) > size ) {
		return -(!0);
	}

	protocol_header_t *h = (protocol_header_t *)data;
	if( PROTOCOL_BUFF_SIZE_MAX < h->size ||
	    0 > h->size ) {
		return !0;
	}

	switch( h->request ) {
	case PROTOCOL_REQUEST_IMAGE:
		return 0;

	default:
		log_debug( "invalid request" );
	}

	return !0;
}

int protocol_verify_request( char *data, int size )
{
	(void)data;
	(void)size;
	return 0;
}

void protocol_request_image( protocol_request_image_t *req )
{
	(void)req;
}
