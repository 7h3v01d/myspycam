#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__


/* Structure definitions. */
typedef struct __attribute__ ((packed)) protocol_header_t {
	int size;
	int request;
} protocol_header_t;

typedef struct __attribute__ ((packed)) protocol_request_image_t {
	protocol_header_t header;
	int quality;
} protocol_request_image_t;


/* Macro definitions. */
#define PROTOCOL_BUFF_SIZE_MIN 64
#define PROTOCOL_BUFF_SIZE_MAX 512
#define PROTOCOL_REQ_SIZE_MIN ( sizeof(protocol_header_t) )

#define PROTOCOL_REQUEST_IMAGE 0

#define PROTOCOL_IMAGE_QUALITY_MIN 1
#define PROTOCOL_IMAGE_QUALITY_MAX 100


/* Function prototypes. */
int protocol_verify_header( char *data, int size );
int protocol_verify_request( char *data, int size );
void protocol_request_image( protocol_request_image_t *req );


#endif /* __PROTOCOL_H__ */
