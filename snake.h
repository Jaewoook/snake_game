#include <queue>
#include "common.h"

#ifndef __SNAKE__
#define __SNAKE__

#define SYM_SNAKE_HEAD L"🟨"

enum SnakeDirection {
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3,
};

class Snake {
    private:
        std::queue<POSITION> snake_pos;
        POSITION head_pos;
        SnakeDirection direction;
        int size;
    public:
        Snake():
            head_pos { 10, 10 },
            direction(RIGHT),
            size(2) {}
        void increase();
        void decrease();
        POSITION get_head_pos() { return head_pos; }
        void update_head_pos(int y, int x) {
            head_pos = POSITION { x, y };
        }
        SnakeDirection get_direction() { return direction; }
        void change_direction(SnakeDirection direction);
};

#endif
