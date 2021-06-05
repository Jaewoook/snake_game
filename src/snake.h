#include <deque>
#include "common.h"

#ifndef __SNAKE__
#define __SNAKE__

class Snake {
    private:
        std::deque<POSITION> snake_pos;
        DIRECTION direction;
        DIRECTION get_tail_direction() {
            int size = snake_pos.size();
            auto last_first = snake_pos[size - 1];
            auto last_second = snake_pos[size - 2];

            int diff_x = last_first.x - last_second.x;
            int diff_y = last_first.y - last_second.y;
            if (diff_x == 0) {
                return diff_y == 1 ? DOWN : UP;
            } else {
                return diff_x == 1 ? RIGHT : LEFT;
            }
        }
        void init_snake_pos() {
            snake_pos.clear();
            snake_pos.push_back(POSITION { 10, 10 });
            // snake_pos.push_back(POSITION { 9, 10 });
        }

    public:
        Snake();
        void increase();
        std::deque<POSITION> get_snake_pos() { return snake_pos; }
        int get_snake_size() { return snake_pos.size(); }
        DIRECTION get_direction() { return direction; }
        void change_direction(DIRECTION direction) { this->direction = direction; }
        void reset();
};

#endif
