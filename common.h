#include <ncursesw/curses.h>

#ifndef __COMMON__
#define __COMMON__

class Map;
class Snake;
typedef struct Position_t {
    int x, y;
} POSITION;

class Context {
    private:
        bool playing, prepared;
        int score;

    public:
        WINDOW *win;
        Map *map;
        Snake *snake;
        Context(WINDOW *win, Map *map, Snake *snake): win(win), map(map), snake(snake) {
            playing = false;
            prepared = true;
            score = 0;
        }
        void update();
        void start_game();
        void pause_game();
        void stop_game();
        void reset_game();
        bool is_playing() { return playing; }
        int get_score() { return score; }
};


#endif
