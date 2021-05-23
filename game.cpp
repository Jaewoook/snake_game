#include <locale>
#include <ncursesw/curses.h>
#include "map.h"

const int MAP_WIN_WIDTH = 42;
const int MAP_WIN_HEIGHT = 21;

WINDOW *init_game();
void destroy_game(WINDOW *main_window);

int main() {
    WINDOW *map_window = init_game();
    Map map;
    mvprintw(2, 16, "Snake Game");
    mvprintw(3, 10, "Press Q to end program.");

    map.draw(map_window);
    getch();

    destroy_game(map_window);
    return 0;
}

WINDOW *init_game() {
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    curs_set(0);
    noecho();
    start_color();
    keypad(stdscr, true);
    init_pair(1, COLOR_WHITE, COLOR_CYAN);
    refresh();

    WINDOW *win = newwin(MAP_WIN_HEIGHT, MAP_WIN_WIDTH, 5, 3);
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
