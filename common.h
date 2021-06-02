#ifndef __COMMON__
#define __COMMON__

typedef struct Position_t {
    const int x, y;
} POSITION;

class Context {
    public:
        WINDOW *win;
        Context(WINDOW *win): win(win) {}
        void update();
};


#endif
