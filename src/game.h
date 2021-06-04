#include <ncursesw/curses.h>
#include <thread>
#include <memory>
#include "common.h"

#ifndef __GAME__
#define __GAME__

class Game {

    private:
        bool playing, prepared;
        int score;
        std::unique_ptr<std::thread> tick_thread;

    public:
        WINDOW *win;
        Context *ctx;
        Game(WINDOW *map_win, Context *ctx);
        std::thread create_drawer();
        std::thread create_input_loop();
        void start();
        void pause();
        void resume();
        void stop();
        void reset();
        bool is_playing() { return playing; }
        int get_score() { return score; }
        int increase_score() { score++; }
        // ~Game();
};

#endif
