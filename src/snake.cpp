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

void Snake::move() {
    log("Snake", "move to next block");
    auto old_head_pos = snake_pos.front();
    POSITION head_pos { old_head_pos.x, old_head_pos.y };

    switch (direction) {
    case UP:
        head_pos.y -= 1;
        break;
    case DOWN:
        head_pos.y += 1;
        break;
    case LEFT:
        head_pos.x -= 1;
        break;
    case RIGHT:
        head_pos.x += 1;
        break;
    }
    snake_pos.push_front(head_pos);
    snake_pos.pop_back();
}

void Snake::change_direction(DIRECTION direction) {
    log("Snake", "Change direction:");
    log("Snake", (char *) &direction);
    this->direction = direction;
}

void Snake::reset() {
    log("Snake", "reset");
    direction = RIGHT;
    init_snake_pos();
}
