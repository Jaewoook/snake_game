#include "context.h"

Context::Context(): map(Map()), snake(Snake()) {}

Map *Context::get_map() {
    return &map;
}

Snake *Context::get_snake() {
    return &snake;
}

void Context::reset() {
    map.reset();
    snake.reset();
}

Context::~Context() {

}
