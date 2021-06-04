#include <fstream>
#include <ctime>
#include "log.h"

using namespace std;

ofstream log_stream;

const char *get_time() {
    auto curr_time = time(NULL);
    return ctime(&curr_time);
}

void log(const char *msg, const char *module) {
    if (!LOGGING) {
        return;
    }

    if (log_stream.is_open()) {
        log_stream << "[" << get_time() << "] " << module << ": " << msg << "\n";
    }
}

void log_open() {
    if (LOGGING) {
        log_stream = ofstream(LOG_FILENAME);
        log("log open");
    }
}

void log_close() {
    if (log_stream.is_open()) {
        log_stream.close();
    }
}
