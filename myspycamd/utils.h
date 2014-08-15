#ifndef __UTILS_H__
#define __UTILS_H__


/* OS specific headers. */
#include <netinet/in.h>


/* Function prototypes. */
int utils_daemonize( int nochdir, int noclose );
const char *utils_get_ip( struct sockaddr_in saddr );


#endif /* __UTILS_H__ */
