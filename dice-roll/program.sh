#!/bin/bash

FILE=program.out
if [ ! -f "$FILE" ]; then
    gcc -std=c99 -o program.out main.c player.c printer.c 
fi
./program.out

