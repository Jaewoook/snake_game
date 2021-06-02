CC = g++
CFLAGS = -std=c++11 -g -Wall
SRCDIR = src/
OBJS = game.o map.o snake.o common.o
TARGET = snake_game
I_NCURSES =
L_NCURSES =
D_NCURSES =
UNAME := $(shell uname -s)

# Set options for macOS
ifeq ($(UNAME), Darwin)
	I_NCURSES += -I/usr/local/opt/ncurses/include
	L_NCURSES += -L/usr/local/opt/ncurses/lib
	D_NCURSES += -D_XOPEN_SOURCE_EXTENDED
endif


all: $(TARGET)
	@echo compiled binary target: $(UNAME)

$(TARGET): $(OBJS)
	$(CC) $(L_NCURSES) $(CFLAGS) -o $@ $(OBJS) -lncursesw

game.o: game.cpp map.o common.o
	$(CC) $(I_NCURSES) $(D_NCURSES) $(CFLAGS) -c game.cpp

map.o: map.cpp map.h common.o
	$(CC) $(I_NCURSES) $(D_NCURSES) $(CFLAGS) -c $<

snake.o: snake.cpp snake.h common.o
	$(CC) $(I_NCURSES) $(D_NCURSES) $(CFLAGS) -c $<

common.o: common.cpp common.h
	$(CC) $(I_NCURSES) $(D_NCURSES) $(CFLAGS) -c $<

%.o: %.c %.h
	$(CC) $(I_NCURSES) $(D_NCURSES) $(CFLAGS) -c $<

clean:
	rm -rf *.o $(TARGET)
