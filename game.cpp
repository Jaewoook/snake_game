#include <locale>
#include <cctype>
#include <ncursesw/curses.h>
#include "common.h"
#include "map.h"
#include "snake.cpp"

const int MAP_WIN_WIDTH = 42;
const int MAP_WIN_HEIGHT = 21;

WINDOW *init_window();
void destroy_game(WINDOW *map_window);
void start_game(WINDOW *win, Map *map, Snake *snake);

int main() {
    WINDOW *map_window = init_window();
    Context ctx(map_window);
    Map map(&ctx);
    Snake snake(&ctx);
    char input;
    mvprintw(2, 18, "Snake Game");
    mvprintw(4, 10, "Press S to start game");
    mvprintw(5, 10, "Press Q to exit");

    map.draw();
    while (!!(input = toupper(getch()))) {
        //  exit
        if (input == 'Q') {
            break;
        }

        //  start game
        if (input == 'S') {
            start_game(map_window, &map, &snake);
        }
    }

    destroy_game(map_window);
    return 0;
}

WINDOW *init_window() {
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    curs_set(0);
    noecho();
    start_color();
    keypad(stdscr, true);
    init_pair(1, COLOR_WHITE, COLOR_CYAN);
    refresh();

    WINDOW *win = newwin(MAP_WIN_HEIGHT, MAP_WIN_WIDTH, 7, 3);
    wbkgd(win, COLOR_PAIR(1));
    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(win);

    return win;
}

void destroy_game(WINDOW *win) {
    endwin();
    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    delwin(win);
}

void start_game(WINDOW *win, Map *map, Snake *snake) {
    //  TODO start game logic
}
