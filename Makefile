CC = g++
CXXFLAGS = -std=c++11 -g
SRCDIR = src/
OBJS = game.o map.o snake.o
TARGET = snake_game

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -lncursesw

game.o: game.cpp
	$(CC) $(CXXFLAGS) -c game.cpp

map.o: map.cpp map.h snake.h
	$(CC) $(CXXFLAGS) -c map.cpp

snake.o: snake.cpp snake.h
	$(CC) $(CXXFLAGS) -c snake.cpp

%.o: %.c %.h common.h
	$(CC) $(CXXFLAGS) -c $<

clean:
	rm -rf *.o $(TARGET)
