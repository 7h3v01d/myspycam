/* Program specific headers. */
#include "protocol.h"


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
	if( (int)sizeof(protocol_header) > size ) {
		return -(!0);
	}

	protocol_header *h = (protocol_header *)data;
	if( PROTOCOL_BUFF_SIZE_MAX < h->size ||
	    0 > h->size ) {
		return !0;
	}

	switch( h->request ) {
	case PROTOCOL_REQUEST_IMAGE:
		return 0;
	}

	return !0;
}
