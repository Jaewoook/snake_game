#include <ncursesw/curses.h>
#include "context.h"

Context::Context(): map(Map()), snake(Snake()) {}

void Context::refresh(WINDOW *win) {
    map.draw(win);
    map.draw_snake(win, &snake);
    wrefresh(win);
}

void Context::reset() {
    map.reset();
    snake.reset();
}

Context::~Context() {

}
