#ifndef __LOG_H__
#define __LOG_H__


/* OS specific headers. */
#include <syslog.h>


/* Macro definitions. */
#define log_emergency( format, args... ) syslog( LOG_EMERG, "EMERGENCY: " format, ##args )
#define log_alert( format, args... ) syslog( LOG_ALERT, "ALERT: " format, ##args )
#define log_critical( format, args... ) syslog( LOG_CRIT, "CRITICAL: " format, ##args )
#define log_error( format, args... ) syslog( LOG_ERR, "ERROR: " format, ##args )
#define log_warning( format, args... ) syslog( LOG_WARNING, "WARNING: " format, ##args )
#define log_notice( format, args... ) syslog( LOG_NOTICE, "NOTICE: " format, ##args )
#define log_info( format, args... ) syslog( LOG_INFO, "INFO: " format, ##args )
#define log_debug( format, args... ) syslog( LOG_DEBUG, "DEBUG: " format, ##args )


/* Function prototypes. */
void log_open( void );
void log_close( void );


#endif /* __LOG_H__ */
