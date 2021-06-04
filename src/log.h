#ifndef __LOG__
#define __LOG__

#if defined(LOGGING) && LOGGING == 1
#define LOG_FILENAME "log.txt"
#elif not defined(LOGGING)
#define LOGGING 0
#define LOG_FILENAME ""
#else
#define LOG_FILENAME ""
#endif

#define DEFAULT_MODULE "snake_game"

void log(const char *msg, const char *module = DEFAULT_MODULE);
void log_open();
void log_close();

#endif
