#include <ncursesw/curses.h>
#include "map.h"
#include "log.h"

Map::Map(): size_x(41), size_y(21) {
    log("Map", "Init");
    map = new int*[size_y];
    for (int i = 0; i < size_y; i++) {
        map[i] = new int[size_x];
    }
    init_map();
}

void Map::init_map(WINDOW *win) {
    if (map == nullptr) {
        log("Map", "map ptr does not assigned");
        return;
    }

    for (int i = 0; i < size_y; i++) {
        for (int j = 0; j < size_x; j++) {
            if (win != nullptr) {
                mvwdelch(win, i, j);
            }
            if (i == 0 || i == size_y - 1) {
                map[i][j] = BLOCK_IMMUTABLE_WALL;
            } else if (j == 0 || j == size_x - 1) {
                map[i][j] = BLOCK_IMMUTABLE_WALL;
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
        mvwaddwstr(win, (*iter).y, (*iter).x, is_head ? SYM_SNAKE_HEAD : SYM_SNAKE_BODY);
        if (is_head) {
            is_head = false;
        }
    }
}

BlockType Map::get_block_type(POSITION pos) {
    int type = map[pos.y][pos.x];
    return static_cast<BlockType>(type);
}

void Map::reset(WINDOW *win) {
    init_map(win);
}

Map::~Map() {
    log("Map", "Destruct map");

    for (int i = 0; i < size_y; i++) {
        delete[] map[i];
    }
    delete[] map;
}
