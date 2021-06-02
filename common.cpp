#include <ncursesw/curses.h>
#include "common.h"

void Context::update() {
    wrefresh(win);
}
