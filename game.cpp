#include <locale>
#include <ncursesw/curses.h>
#include "map.h"

const int DEFAULT_WIDTH = 42;
const int DEFAULT_HEIGHT = 42;

WINDOW *init_game();
void destroy_game(WINDOW *main_window);

int main() {
    WINDOW *main_window = init_game();
    Map map;
    // wprintw(main_window, "Snake Game\nPress Q to end program.\n\n");
    // wrefresh(main_window);
    // refresh();

    map.draw(main_window);
    // refresh();
    getch();
    // int key;
    // while (true) {
    //     key = getch();
    //     if (key == 'q' || key == 'Q') {
    //         break;
    //     }
    //     wprintw(main_window, "Input key: %c\n", key);
    //     wrefresh(main_window);
    // }

    destroy_game(main_window);
    return 0;
}

WINDOW *init_game() {
    initscr();
    // resize_term(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    cbreak();
    curs_set(0);
    noecho();
    start_color();
    keypad(stdscr, true);
    init_pair(1, COLOR_BLACK, COLOR_CYAN);
    refresh();

    WINDOW *win = newwin(DEFAULT_HEIGHT, DEFAULT_WIDTH, 2, 2);
    wbkgd(win, COLOR_PAIR(1));
    box(win, 0, 0);
    wrefresh(win);

    return win;
}

void destroy_game(WINDOW *main_window) {
    endwin();
    wborder(main_window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    delwin(main_window);
}
