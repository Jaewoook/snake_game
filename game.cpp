#include <ncurses.h>

int main() {
    initscr();
    start_color();

    printw("Hello World!");
    refresh();
    getch();
    endwin();

    return 0;
}
