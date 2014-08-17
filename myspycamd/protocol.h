#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__


/* Macro definitions. */
#define PROTOCOL_BUFF_SIZE_MIN 64
#define PROTOCOL_BUFF_SIZE_MAX 512


/* Function prototypes. */
int protocol_verify_header( char *data, int size );


#endif /* __PROTOCOL_H__ */
