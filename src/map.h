#include <ncursesw/curses.h>
#include "snake.h"
#include "common.h"

#ifndef __MAP__
#define __MAP__

#define SYM_BLOCK_IMMUTABLE_WALL L"■"
#define SYM_BLOCK_WALL L"□"
#define SYM_BLOCK_GATE L"◇"
#define SYM_SNAKE_HEAD L"▣"
#define SYM_SNAKE_BODY L"▨"

enum BlockType {
    BLOCK_EMPTY = 0,
    BLOCK_IMMUTABLE_WALL = 1,
    BLOCK_WALL = 2,
    BLOCK_GATE_IN = 3,
    BLOCK_GATE_OUT = 4,
};

class Map {

    private:
        int size_x, size_y;
        int **map;
        void init_map(WINDOW *win = nullptr);
        const wchar_t *get_sym_by_type(int type) {
            switch (type) {
                case BLOCK_IMMUTABLE_WALL:
                    return SYM_BLOCK_IMMUTABLE_WALL;
                case BLOCK_WALL:
                    return SYM_BLOCK_WALL;
                case BLOCK_GATE_IN:
                case BLOCK_GATE_OUT:
                    return SYM_BLOCK_GATE;
                default:
                    return L" ";
            }
        }

    public:
        Map();
        void draw(WINDOW *win);
        void draw_snake(WINDOW *win, Snake *snake);
        BlockType get_block_type(POSITION pos);
        const BlockType operator[](int x);
        void reset(WINDOW *win);
        ~Map();
};

#endif
