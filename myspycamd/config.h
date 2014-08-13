#ifndef __CONFIG_H__
#define __CONFIG_H__


/* Configuration options. */
#define CONFIG_DAEMONIZE 1
#define CONFIG_DEBUG     2
#define CONFIG_PORT      3


/* Function prototypes. */
int config_parse_args( int argc, char *args[] );
int config_get_int( int option );
const char *config_get_str( int option );


#endif /* __CONFIG_H__ */
