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

Game::Game(WINDOW *map_win, Context *ctx): win(map_win), ctx(ctx) {
    ctx->get_map()->draw(win);
    ctx->get_map()->draw_snake(win, ctx->get_snake());
    prepared = true;
    playing = false;
    score = 0;
}

std::thread Game::create_input_loop() {
    log("Game", "Create input loop thread");
    return std::thread([&](std::function<void (LOOP_FINISH_REASON reason)> callback) {
        char ch;
        while ((ch = getch()) && ch != ERR) {
            ch = toupper(ch);
            log("input thread", "Key input: ");
            log("input thread", &ch);

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

std::thread Game::create_drawer() {
    log("Game", "Create drawer thread");
    return std::thread([&]() {
        while (true) {
            wrefresh(win);
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
WINDOW *init_window(int width, int height, int top, int left);
void destroy_window(WINDOW *map_window);

int main() {
    init();
    WINDOW *map_window = init_window(MAP_WIN_WIDTH, MAP_WIN_HEIGHT, 7, 3);
    Context ctx;
    Game game(map_window, &ctx);
    char input;

    while ((input = getch()) && input != ERR) {
        input = toupper(input);
        //  exit
        if (input == 'Q') {
            log("main", "Attempt to quit game");
            break;
        }

        //  start game
        if (input == 'S') {
            log("main", "Attempt to start game");
            game.start();
        }
    }

    destroy_window(map_window);
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

    //  print game text
    mvprintw(2, 18, "Snake Game");
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

WINDOW *init_window(int width, int height, int top, int left) {
    WINDOW *win = newwin(height, width, top, left);
    wbkgd(win, COLOR_PAIR(1));
    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(win);

    return win;
}

void destroy_window(WINDOW *win) {
    log("main", "Destroy window");
    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    delwin(win);
}
