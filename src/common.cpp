#include "common.h"

void Context::update() {
    wrefresh(win);
}

void Context::start_game() {
    if (prepared) {
        return;
    }
    prepared = false;
    playing = true;
}

void Context::pause_game() {
    if (!playing) {
        return;
    }
    playing = false;
}

void Context::stop_game() {
    if (playing) {
        return;
    }
}

void Context::reset_game() {
    if (playing) {
        return;
    }
    score = 0;
    prepared = true;
}
