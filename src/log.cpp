#include <fstream>
#include <ctime>

using namespace std;

#if defined(LOGGING)
const char *LOG_FILENAME = "log.txt";
#else
#define LOGGING 0
const char *LOG_FILENAME = "";
#endif

ofstream log_stream;

const char *get_time() {
    auto curr_time = time(NULL);
    return ctime(&curr_time);
}

void log(const char* msg) {
    if (log_stream.is_open()) {
        log_stream << get_time() << ": " << msg;
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
