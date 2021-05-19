CC = g++
CCFLAGS = -g
SRCDIR = src/
OBJS = game.o map.o
TARGET = snake_game

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CCFLAGS) -o $@ game.o map.o -lncurses

game.o: game.cpp
	$(CC) $(CCFLAGS) -c game.cpp -lncurses

map.o: map.cpp
	$(CC) $(CCFLAGS) -c map.cpp

%.o: %.c
	$(CC) $(CCFLAGS) -c $<

clean:
	rm -rf *.o $(TARGET)
