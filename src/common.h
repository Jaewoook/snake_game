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

extern const char *DIRECTION_LABEL[];

enum LOOP_FINISH_REASON {
    LOOP_END_CMD,
    LOOP_PAUSE_CMD,
};

extern const char *LOOP_FINISH_REASON_LABEL[];

#endif
