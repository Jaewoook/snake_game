#!/usr/bin/env bash
echo "Command for starting docker in background mode"
echo "docker run --rm -dit -v $(pwd):/app --name cpp ubuntu:cpp"
echo ""
echo "Command for attaching docker shell"
echo "docker attach snake_game"
echo ""
echo "Command for terminating cpp docker"
echo "docker stop snake_game"
echo ""
echo "Starting docker in background mode.."
docker run --rm -dit -v $(pwd):/snake_game --name snake_game ubuntu:snake_game
