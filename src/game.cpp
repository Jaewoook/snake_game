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
}

std::thread Game::create_input_loop() {
    return std::thread([&](std::function<void (LOOP_FINISH_REASON reason)> callback) {
        char ch;
        while (true) {
            ch = toupper(getch());
            log(std::strcat("Key input: ", &ch), "input thread");

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
                log("attempt to stop game", "input thread");
                callback(LOOP_STOP_CMD);
                return;
            case 'P':
                log("Attempt to pause game", "input thread");
                callback(LOOP_PAUSE_CMD);
                return;
            }
        }
    }, [&](LOOP_FINISH_REASON reason) {
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

    prepared = false;
    playing = true;
    std::thread t = create_input_loop();
}

void Game::pause() {
    if (!playing) {
        return;
    }
    playing = false;
}

void Game::stop() {
    if (playing) {
        return;
    }
}

void Game::reset() {
    if (playing) {
        return;
    }
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

    while (input = toupper(getch())) {
        //  exit
        if (input == 'Q') {
            log("Quit game");
            break;
        }

        //  start game
        if (input == 'S') {
            log("Start game");
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
    log("Init");
}

void cleanup() {
    log("Cleanup");
    endwin();
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
    log("Destroy window");
    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    delwin(win);
}
