#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__


/* Macro definitions. */
#define PROTOCOL_BUFF_SIZE_MIN 64
#define PROTOCOL_BUFF_SIZE_MAX 512

#define PROTOCOL_REQUEST_IMAGE 0


typedef struct __attribute__ ((packed)) protocol_header {
	int size;
	int request;
} protocol_header;

typedef struct __attribute__ ((packed)) protocol_request_image {
	protocol_header header;
	int width;
	int height;
	int quality;
} protocol_request_image;


/* Function prototypes. */
int protocol_verify_header( char *data, int size );


#endif /* __PROTOCOL_H__ */
