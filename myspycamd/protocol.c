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

/** Verify request data.
 *
 * @param data Request data.
 * @param size Request data size.
 *
 * @return 0 if request data is correct.
 * @return Non-zero if error occurred.
 */
int protocol_verify_request( char *data, int size )
{
	protocol_header_t *h = (protocol_header_t *)data;
	if( PROTOCOL_REQUEST_IMAGE == h->request ) {
		if( (int)sizeof(protocol_request_image_t) != size ||
		    (int)sizeof(protocol_request_image_t) != h->size ) {
			log_debug( "invalid request data" );
			return !0;
		}

		protocol_request_image_t *req = (protocol_request_image_t *)data;
		if( PROTOCOL_IMAGE_QUALITY_MIN > req->quality ||
		    PROTOCOL_IMAGE_QUALITY_MAX < req->quality ) {
			log_debug( "invalid request data" );
			return !0;
		}
	}

	return 0;
}

/** Handle image request.
 *
 * @param req Request.
 */
void protocol_request_image( protocol_request_image_t *req )
{
	(void)req;
}
