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
    for (int i = 0; i < size_y; i++) {
        for (int j = 0; j < size_x; j++) {
            mvwaddwstr(win, i, j, get_sym_by_type(map[i][j]));
        }
    }
    wrefresh(win);
}

void Map::draw_snake(WINDOW *win, Snake *snake) {
    POSITION head_pos = snake->get_head_pos();
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
