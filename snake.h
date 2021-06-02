#ifndef __SNAKE__
#define __SNAKE__

class Snake {
    int len;
    public:
        Snake(): len(1) {}
        int get_length() {
            return len;
        }
        void increase() {
            len++;
        }
        void decrease() {

        }
};

#endif
