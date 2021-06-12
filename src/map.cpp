#include <ncursesw/curses.h>
#include "map.h"
#include "log.h"

// const int DEFAULT_MAP[21][21] = {
//     {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
//     {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
//     {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
//     {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
//     {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
//     {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
//     {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
//     {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
//     {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
//     {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
//     {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
//     {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
//     {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
//     {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
//     {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
//     {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
//     {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
//     {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
//     {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
//     {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
//     {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
// };

Map::Map(): size_x(21), size_y(21) {
    log("Map", "Init");
    map = new int*[size_y];
    for (int i = 0; i < size_y; i++) {
        map[i] = new int[size_x];
    }
    init_map();
}

void Map::init_map() {
    if (map == nullptr) {
        log("Map", "map ptr does not assigned");
        return;
    }

    for (int i = 0; i < size_y; i++) {
        for (int j = 0; j < size_x; j++) {
            if (i == 0 || i == size_y - 1) {
                if (j == 0 || j == size_x - 1) {
                    map[i][j] = BLOCK_IMMUTABLE_WALL;
                } else {
                    map[i][j] = BLOCK_WALL;
                }
            } else if (j == 0 || j == size_x - 1) {
                map[i][j] = BLOCK_WALL;
            } else {
                map[i][j] = BLOCK_EMPTY;
            }
        }
    }
}

void Map::draw(WINDOW *win) {
    log("Map", "Draw");
    for (int i = 0; i < size_y; i++) {
        for (int j = 0; j < size_x; j++) {
            mvwaddwstr(win, i, j, get_sym_by_type(map[i][j]));
        }
    }
}

void Map::draw_snake(WINDOW *win, Snake *snake) {
    log("Map", "Draw snake");
    auto pos = snake->get_snake_pos();
    bool is_head = true;
    for (auto iter = pos.begin(); iter != pos.end(); iter++) {
        // old code for displaying snake at specific position
        // this code does not seem to be working becuase the second position of X block is not properly overwritten
        // mvwaddwstr(win, (*iter).y, (*iter).x + 2, is_head ? SYM_SNAKE_HEAD : SYM_SNAKE_BODY);

        mvwdelch(win, (*iter).y, (*iter).x + 2);
        mvwins_wstr(win, (*iter).y, (*iter).x + 2, is_head ? SYM_SNAKE_HEAD : SYM_SNAKE_BODY);
        if (is_head) {
            is_head = false;
        }
    }
}

BlockType Map::get_block_type(POSITION pos) {
    int type = map[pos.y][pos.x];
    return static_cast<BlockType>(type);
}

void Map::reset() {
    init_map();
}

Map::~Map() {
    log("Map", "Destruct map");

    for (int i = 0; i < size_y; i++) {
        delete[] map[i];
    }
    delete[] map;
}

// class Block {
//     BlockType type;
//     public:
//         Block(BlockType type): type(type) {}
// };
