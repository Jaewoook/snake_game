#include "snake.h"
#include "log.h"

Snake::Snake(): direction(RIGHT), snake_pos(std::deque<POSITION>()) {
    log("Snake", "Init");
    init_snake_pos();
}

void Snake::increase() {
    log("Snake", "Increase snake");
    DIRECTION tail_direction = get_tail_direction();
    auto old_tail_pos = snake_pos[get_snake_size() - 1];
    POSITION tail_pos { old_tail_pos.x, old_tail_pos.y };
    switch (tail_direction) {
    case UP:
        tail_pos.y -= 1;
        break;
    case DOWN:
        tail_pos.y += 1;
        break;
    case RIGHT:
        tail_pos.x += 1;
        break;
    case LEFT:
        tail_pos.x -= 1;
        break;
    }
    snake_pos.push_back(tail_pos);
}

void Snake::reset() {
    direction = RIGHT;
    init_snake_pos();
}
