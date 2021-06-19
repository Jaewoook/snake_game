#include <ncursesw/curses.h>
#include "context.h"

Context::Context(): map(Map()), snake(Snake()) {}

void Context::refresh(WINDOW *win) {
    map.draw(win);
    map.draw_snake(win, &snake);
    wrefresh(win);
}

void Context::reset(WINDOW *win) {
    map.reset(win);
    snake.reset();
}

Context::~Context() {

}
