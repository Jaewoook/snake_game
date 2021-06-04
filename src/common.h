#ifndef __COMMON__
#define __COMMON__

typedef struct Position_t {
    int x, y;
} POSITION;

enum DIRECTION {
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3,
};

enum LOOP_FINISH_REASON {
    LOOP_STOP_CMD,
    LOOP_PAUSE_CMD,
};

#endif
