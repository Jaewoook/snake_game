CC = g++
CFLAGS = -std=c++11 -g -Wall -pthread -DLOGGING=1
SRCDIR = src/
OBJS = game.o context.o map.o snake.o log.o common.o
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
	$(CC) $(L_NCURSES) -o $@ $(OBJS) -lncursesw -lpthread

game.o: game.cpp game.h common.o log.o context.o
	$(CC) $(I_NCURSES) $(D_NCURSES) $(CFLAGS) -c game.cpp

map.o: map.cpp map.h common.o log.o snake.o
	$(CC) $(I_NCURSES) $(D_NCURSES) $(CFLAGS) -c $<

snake.o: snake.cpp snake.h common.o log.o
	$(CC) $(I_NCURSES) $(D_NCURSES) $(CFLAGS) -c $<

context.o: context.cpp context.h log.o snake.o map.o
	$(CC) $(I_NCURSES) $(D_NCURSES) $(CFLAGS) -c $<

log.o: log.cpp log.h
	$(CC) $(CFLAGS) -c $<

common.o: common.cpp common.h
	$(CC) $(CFLAGS) -c $<

%.o: %.c %.h
	$(CC) $(I_NCURSES) $(D_NCURSES) $(CFLAGS) -c $<

clean:
	rm -rf *.o $(TARGET)
