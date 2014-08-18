#ifndef __LOG_H__
#define __LOG_H__


/* OS specific headers. */
#include <syslog.h>


/* Macro definitions. */
#define log_emergency( format, args... ) syslog( LOG_EMERG, "%s:%d: EMERGENCY: " format, __FILE__, __LINE__, ##args )
#define log_alert( format, args... ) syslog( LOG_ALERT, "%s:%d: ALERT: " format, __FILE__, __LINE__, ##args )
#define log_critical( format, args... ) syslog( LOG_CRIT, "%s:%d: CRITICAL: " format,__FILE__, __LINE__,  ##args )
#define log_error( format, args... ) syslog( LOG_ERR, "%s:%d: ERROR: " format, __FILE__, __LINE__, ##args )
#define log_warning( format, args... ) syslog( LOG_WARNING, "%s:%d: WARNING: " format, __FILE__, __LINE__, ##args )
#define log_notice( format, args... ) syslog( LOG_NOTICE, "%s:%d: NOTICE: " format, __FILE__, __LINE__, ##args )
#define log_info( format, args... ) syslog( LOG_INFO, "%s:%d: INFO: " format, __FILE__, __LINE__, ##args )
#define log_debug( format, args... ) syslog( LOG_DEBUG, "%s:%d: DEBUG: " format, __FILE__, __LINE__, ##args )


/* Function prototypes. */
void log_open( void );
void log_close( void );


#endif /* __LOG_H__ */
