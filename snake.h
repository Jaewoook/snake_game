#include "common.h"

#ifndef __SNAKE__
#define __SNAKE__

#define SYM_SNAKE_HEAD L"🟨"

class Snake {
    int head_pos_y, head_pos_x, size;
    public:
        Snake():
            head_pos_y(10),
            head_pos_x(10),
            size(1) {}
        void grow() {
            size++;
        }
        POSITION get_head_pos() {
            return POSITION { head_pos_y, head_pos_x };
        }
};

#endif
