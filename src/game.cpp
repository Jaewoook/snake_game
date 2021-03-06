#include <cstring>
#include <locale>
#include <string>
#include <ncursesw/curses.h>
#include <thread>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <atomic>
#include <functional>
#include "context.h"
#include "game.h"
#include "log.h"

const int MAP_WIN_WIDTH = 42;
const int MAP_WIN_HEIGHT = 21;
const int SCORE_WIN_WIDTH = 24;
const int SCORE_WIN_HEIGHT = 9;
const int HELP_WIN_WIDTH = 42;
const int HELP_WIN_HEIGHT = 9;

const int INFO_MSG_X = 3;
const int INFO_MSG_Y = 27;

int prev_msg_len = 0;

void show_info_msg(const char *msg) {
    for (int i = 0; i < prev_msg_len; i++) {
        mvdelch(INFO_MSG_Y, INFO_MSG_X + i);
    }

    mvprintw(INFO_MSG_Y, INFO_MSG_X, "> ");
    prev_msg_len = strlen(msg);
    mvprintw(INFO_MSG_Y, INFO_MSG_X + 2, msg);
}

Game::Game(WINDOW *map_win, WINDOW *score_win, Context *ctx): map_win(map_win), score_win(score_win), ctx(ctx) {
    prepared = true;
    playing = false;
    score = 0;
    show_info_msg("Are you ready?");
    ctx->refresh(map_win);
}

std::thread Game::create_input_loop() {
    log("Game", "Create input loop thread");
    return std::thread([&](std::function<void (LOOP_FINISH_REASON reason)> callback) {
        int ch;
        bool exit_flag = false;
        LOOP_FINISH_REASON reason;
        std::string log_msg;
        while (!exit_flag && (ch = getch()) && ch != ERR) {
            log_msg = std::string("input captured - ");
            log_msg += std::to_string(ch);
            log("input thread", log_msg.c_str());
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
            case 'E':
                log("input thread", "attempt to end game");
                reason = LOOP_END_CMD;
                exit_flag = true;
                break;
            case 'P':
                log("input thread", "Attempt to pause game");
                reason = LOOP_PAUSE_CMD;
                exit_flag = true;
                break;
            }
        }
        callback(reason);
    }, [&](LOOP_FINISH_REASON reason) {
        log("input thread callback", LOOP_FINISH_REASON_LABEL[reason]);
        switch (reason) {
        case LOOP_END_CMD:
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
        while (playing) {
            ctx->get_snake()->move();
            ctx->refresh(map_win);
            std::this_thread::sleep_for(std::chrono::milliseconds(GAME_TICK));
        }
    });
}

std::thread Game::create_timer() {
    using namespace std::chrono;

    log("Game", "Create timer thread");
    return std::thread([&]() {
        double elapsed = 0;
        auto start_time = system_clock::now().time_since_epoch();
        while (playing) {
            auto curr_time = system_clock::now().time_since_epoch();
            elapsed = std::round(duration<double>(curr_time - start_time).count() * 100) / 100;
            std::stringstream sstream;
            sstream << std::fixed << std::setprecision(2) << elapsed;
            mvwprintw(score_win, 6, 7, std::string(sstream.str()).c_str());
            wrefresh(score_win);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    });
}

void Game::start() {
    if (!prepared) {
        return;
    }

    prepared = false;
    playing = true;
    std::thread input = create_input_loop();
    std::thread tick = create_draw_loop();
    std::thread timer = create_timer();
    log("Game", "Start game");
    show_info_msg("Game started");
    input.join();
    tick.join();
    timer.join();
}

void Game::pause() {
    if (!playing) {
        return;
    }

    playing = false;
    log("Game", "Pause game");
    show_info_msg("Game paused");
}

void Game::stop() {
    if (!playing) {
        return;
    }

    playing = false;
    log("Game", "End game");
    show_info_msg("Game ended");
}

void Game::reset() {
    if (playing) {
        return;
    }

    ctx->reset(map_win);
    score = 0;
    prepared = true;
    log("Game", "Reset game");
    show_info_msg("Game reset");
    ctx->refresh(map_win);
}

void init();
void cleanup();
WINDOW *init_window(int width, int height, int top, int left, bool border = false, int pair_num = 1);
void destroy_window(WINDOW *window);
void show_quit_warning();
void hide_quit_warning();

int main() {
    init();
    WINDOW *map_window = init_window(MAP_WIN_WIDTH, MAP_WIN_HEIGHT, 5, 3);
    WINDOW *score_window = init_window(SCORE_WIN_WIDTH, SCORE_WIN_HEIGHT, 5, 50, true, 2);
    WINDOW *mission_window = init_window(SCORE_WIN_WIDTH, SCORE_WIN_HEIGHT - 1, 14, 50, true, 2);
    WINDOW *help_window = init_window(HELP_WIN_WIDTH, HELP_WIN_HEIGHT, 29, 3, true, 2);

    //  print score board window texts
    mvwprintw(score_window, 0, 3, " Score Board ");
    mvwprintw(score_window, 2, 4, "B: ");
    mvwprintw(score_window, 3, 4, "+: ");
    mvwprintw(score_window, 4, 4, "-: ");
    mvwprintw(score_window, 5, 4, "G: ");
    mvwprintw(score_window, 6, 4, "T: 0.0");
    wrefresh(score_window);
    //  print mission window texts
    mvwprintw(mission_window, 0, 3, " Mission ");
    mvwprintw(mission_window, 2, 4, "B: ");
    mvwprintw(mission_window, 3, 4, "+: ");
    mvwprintw(mission_window, 4, 4, "-: ");
    mvwprintw(mission_window, 5, 4, "G: ");
    wrefresh(mission_window);
    //  print help window
    mvwprintw(help_window, 0, 3, " How to play? ");
    mvwprintw(help_window, 2, 4, "Press S to start game");
    mvwprintw(help_window, 3, 4, "Press E to end game");
    mvwprintw(help_window, 4, 4, "Press P to pause game");
    mvwprintw(help_window, 5, 4, "Press R to reset game");
    mvwprintw(help_window, 6, 4, "Press Q to exit");
    wrefresh(help_window);

    Context ctx;
    Game game(map_window, score_window, &ctx);
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
        } else if (input == 'R') {
            log("main", "Attempt to reset game");
            game.reset();
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
    mvprintw(2, 14, "???? Snake Game");
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
    mvprintw(27, 3, "Error: cannot quit because game is not finished yet.");
}

void hide_quit_warning() {
    mvdelch(30, 3);
}
