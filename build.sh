#!/bin/bash
echo "Starting compile Snake Game..."
cd src
make && mv ./snake_game ../snake_game
echo
echo "Run ./snake_game to play!"
