#include <cstring>

#ifndef __COMMON__
#define __COMMON__

#define GAME_TICK 500
#define ITEM_LIFETICK 20

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
    LOOP_END_CMD,
    LOOP_PAUSE_CMD,
};

extern const char *DIRECTION_LABEL[];
extern const char *LOOP_FINISH_REASON_LABEL[];

#endif
