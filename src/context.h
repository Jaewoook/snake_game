#include "snake.h"
#include "map.h"

#ifndef __CONTEXT__
#define __CONTEXT__

class Context {

    private:
        Map map;
        Snake snake;

    public:
        Context();
        Map *get_map() { return &map; }
        Snake *get_snake() { return &snake; }
        void refresh(WINDOW *win);
        void reset();
        ~Context();
};

#endif
