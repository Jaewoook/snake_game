#include <fstream>
#include <ctime>
#include <cstring>
#include "log.h"

using namespace std;

ofstream log_stream;

char *get_time() {
    auto curr_time = time(NULL);
    return strtok(ctime(&curr_time), "\n");
}

void log(const char *msg, const char *module) {
    #ifndef LOGGING
        return;
    #endif

    if (log_stream.is_open()) {
        log_stream << "[" << get_time() << "] " << module << ": " << msg << "\n";
    }
}

void log_open() {
    #if LOGGING
        log_stream = ofstream(LOG_FILENAME);
        log("log open");
    #endif
}

void log_close() {
    if (log_stream.is_open()) {
        log_stream.close();
    }
}
