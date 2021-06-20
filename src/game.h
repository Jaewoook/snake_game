#include <ncursesw/curses.h>
#include <thread>
#include <atomic>
#include "common.h"

#ifndef __GAME__
#define __GAME__

class Game {

    private:
        bool prepared;
        int score, level;
        std::atomic<bool> playing;

    public:
        WINDOW *map_win, *score_win;
        Context *ctx;
        Game(WINDOW *map_win, WINDOW *score_win, Context *ctx);
        std::thread create_draw_loop();
        std::thread create_input_loop();
        std::thread create_timer();
        void start();
        void pause();
        void resume();
        void stop();
        void reset();
        bool is_playing() { return playing; }
        int get_score() { return score; }
        void increase_score() { score++; }
        // ~Game();
};

#endif
