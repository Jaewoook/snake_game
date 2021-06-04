CC = g++
CFLAGS = -std=c++11 -g -Wall -pthread
SRCDIR = src/
OBJS = game.o context.o map.o snake.o log.o
TARGET = snake_game
I_NCURSES =
L_NCURSES =
D_NCURSES = -DLOGGING=1
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

game.o: game.cpp game.h common.h log.o context.o
	$(CC) $(I_NCURSES) $(D_NCURSES) $(CFLAGS) -c game.cpp

map.o: map.cpp map.h common.h log.o snake.o
	$(CC) $(I_NCURSES) $(D_NCURSES) $(CFLAGS) -c $<

snake.o: snake.cpp snake.h common.h log.o
	$(CC) $(I_NCURSES) $(D_NCURSES) $(CFLAGS) -c $<

context.o: context.cpp context.h log.o snake.o map.o
	$(CC) $(I_NCURSES) $(D_NCURSES) $(CFLAGS) -c $<

log.o: log.cpp log.h
	$(CC) $(CFLAGS) -c $<

%.o: %.c %.h
	$(CC) $(I_NCURSES) $(D_NCURSES) $(CFLAGS) -c $<

clean:
	rm -rf *.o $(TARGET)
