#include "snake.h"
#include "common.h"

#ifndef __MAP__
#define __MAP__

#define SYM_BLOCK_IMMUTABLE_WALL L"⬛"
#define SYM_BLOCK_WALL L"🟦"
#define SYM_BLOCK_EMPTY L"⬜️"
// #define CHAR_BLOCK_EMPTY L"🟪"
#define SYM_BLOCK_GATE L"🟪"

enum BlockType {
    BLOCK_EMPTY = 0,
    BLOCK_IMMUTABLE_WALL = 1,
    BLOCK_WALL = 2,
    BLOCK_GATE_IN = 3,
    BLOCK_GATE_OUT = 4,
};

class Map {
    int size_x, size_y;
    int **map;
    private:
        const wchar_t *get_sym_by_type(int type) {
            switch (type) {
                case BLOCK_EMPTY:
                    return SYM_BLOCK_EMPTY;
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
        void draw_snake(Snake *snake);
        BlockType get_block_type(POSITION pos);
        const BlockType operator[](int x);
        ~Map();
};

#endif
