#ifndef __MAP__
#define __MAP__
#define CHAR_BLOCK_IMMUTABLE_WALL L"⬛"
#define CHAR_BLOCK_WALL L"🟦"
#define CHAR_BLOCK_EMPTY L"⬜️"
// #define CHAR_BLOCK_EMPTY L"🟪"
#define CHAR_BLOCK_GATE L"🟪"

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
        const wchar_t *getCharByType(int type) {
            switch (type) {
                case BLOCK_EMPTY:
                    return CHAR_BLOCK_EMPTY;
                case BLOCK_IMMUTABLE_WALL:
                    return CHAR_BLOCK_IMMUTABLE_WALL;
                case BLOCK_WALL:
                    return CHAR_BLOCK_WALL;
                case BLOCK_GATE_IN:
                case BLOCK_GATE_OUT:
                    return CHAR_BLOCK_GATE;
                default:
                    return L" ";
            }
        }
    public:
        Map();
        void draw(WINDOW *win);
        ~Map();
};

#endif
