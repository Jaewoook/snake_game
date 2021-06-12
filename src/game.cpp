#include <cstring>
#include <locale>
#include <cctype>
#include <ncursesw/curses.h>
#include <thread>
#include <chrono>
#include <functional>
#include "common.h"
#include "context.h"
#include "game.h"
#include "log.h"

const int MAP_WIN_WIDTH = 42;
const int MAP_WIN_HEIGHT = 21;
const int SCORE_WIN_WIDTH = 21;
const int SCORE_WIN_HEIGHT = 7;

Game::Game(WINDOW *map_win, Context *ctx): win(map_win), ctx(ctx) {
    prepared = true;
    playing = false;
    score = 0;
    ctx->refresh(win);
}

std::thread Game::create_input_loop() {
    log("Game", "Create input loop thread");
    return std::thread([&](std::function<void (LOOP_FINISH_REASON reason)> callback) {
        int ch;
        while ((ch = getch()) && ch != ERR) {
            ch = toupper(ch);
            switch (ch) {
            case KEY_UP:
                ctx->get_snake()->change_direction(UP);
                break;
            case KEY_RIGHT:
                ctx->get_snake()->change_direction(RIGHT);
                break;
            case KEY_DOWN:
                ctx->get_snake()->change_direction(DOWN);
                break;
            case KEY_LEFT:
                ctx->get_snake()->change_direction(LEFT);
                break;
            case 'S':
                log("input thread", "attempt to stop game");
                callback(LOOP_STOP_CMD);
                return;
            case 'P':
                log("input thread", "Attempt to pause game");
                callback(LOOP_PAUSE_CMD);
                return;
            }
        }
    }, [&](LOOP_FINISH_REASON reason) {
        log("input thread callback", (char *) &reason);
        switch (reason)
        {
        case LOOP_STOP_CMD:
            stop();
            break;
        case LOOP_PAUSE_CMD:
            pause();
            break;
        }
    });
}

std::thread Game::create_draw_loop() {
    log("Game", "Create drawer thread");
    return std::thread([&]() {
        while (true) {
            ctx->get_snake()->move();
            ctx->refresh(win);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    });
}

void Game::start() {
    if (!prepared) {
        return;
    }

    log("Game", "Start game");
    prepared = false;
    playing = true;
    std::thread t = create_input_loop();
    t.join();
}

void Game::pause() {
    if (!playing) {
        return;
    }

    log("Game", "Pause game");
    playing = false;
}

void Game::stop() {
    if (playing) {
        return;
    }

    log("Game", "Stop game");
}

void Game::reset() {
    if (playing) {
        return;
    }

    log("Game", "Reset game");
    ctx->reset();
    score = 0;
    prepared = true;
}

void init();
void cleanup();
WINDOW *init_window(int width, int height, int top, int left, bool border = false, int pair_num = 1);
void destroy_window(WINDOW *window);
void show_quit_warning();
void hide_quit_warning();

int main() {
    init();
    WINDOW *map_window = init_window(MAP_WIN_WIDTH, MAP_WIN_HEIGHT, 7, 3);
    WINDOW *score_window = init_window(SCORE_WIN_WIDTH, SCORE_WIN_HEIGHT, 7, 53, true, 2);
    WINDOW *mission_window = init_window(SCORE_WIN_WIDTH, SCORE_WIN_HEIGHT, 16, 53, true, 2);

    //  print score board window texts
    mvwprintw(score_window, 0, 4, " Score Board ");
    mvwprintw(score_window, 2, 2, "B: ");
    mvwprintw(score_window, 3, 2, "+: ");
    mvwprintw(score_window, 4, 2, "-: ");
    mvwprintw(score_window, 5, 2, "G: ");
    wrefresh(score_window);
    //  print mission window texts
    mvwprintw(mission_window, 0, 6, " Mission ");
    mvwprintw(mission_window, 2, 2, "B: ");
    mvwprintw(mission_window, 3, 2, "+: ");
    mvwprintw(mission_window, 4, 2, "-: ");
    mvwprintw(mission_window, 5, 2, "G: ");
    wrefresh(mission_window);

    Context ctx;
    Game game(map_window, &ctx);
    int input;

    while ((input = getch()) && input != ERR) {
        input = toupper(input);
        //  exit
        if (input == 'Q') {
            log("main", "Attempt to quit game");
            if (game.is_playing()) {
                show_quit_warning();
                continue;
            }
            break;
        }

        //  start game
        if (input == 'S') {
            log("main", "Attempt to start game");
            game.start();
        }
    }

    destroy_window(map_window);
    destroy_window(score_window);
    destroy_window(mission_window);
    cleanup();

    return 0;
}

void init() {
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    curs_set(0);
    noecho();
    start_color();
    keypad(stdscr, true);
    init_pair(1, COLOR_BLACK, COLOR_CYAN);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);

    //  print game text
    mvprintw(2, 14, "🐍 Snake Game");
    mvprintw(4, 10, "Press S to start game");
    mvprintw(5, 10, "Press Q to exit");
    refresh();

    log_open();
    log("main", "Init");
}

void cleanup() {
    endwin();
    log("main", "log close");
    log_close();
}

WINDOW *init_window(int width, int height, int top, int left, bool border, int pair_num) {
    WINDOW *win = newwin(height, width, top, left);
    wbkgd(win, COLOR_PAIR(pair_num));
    if (border) {
        box(win, 0, 0);
    }
    wrefresh(win);

    return win;
}

void destroy_window(WINDOW *window) {
    log("main", "Destroy window");
    wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    delwin(window);
}

void show_quit_warning() {
    mvprintw(30, 3, "Error: cannot quit because game is not finished yet.");
}

void hide_quit_warning() {
    mvdelch(30, 3);
}