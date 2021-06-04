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

void log(const char *module, const char *msg) {
    #ifndef LOGGING
        return;
    #endif

    if (log_stream.is_open()) {
        log_stream << "[" << get_time() << "] " << module << ": " << msg << "\n";
        log_stream.flush();
    }
}

void log_open() {
    #if LOGGING
        log_stream = ofstream(LOG_FILENAME);
        log("main", "log open");
    #endif
}

void log_close() {
    if (log_stream.is_open()) {
        log_stream.close();
    }
}
