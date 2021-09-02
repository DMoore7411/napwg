#!/bin/sh

cc -c -fPIC napwg.c -o napwg.o -Wall -lopenrk -O3
cc -c -fPIC subboxter.c -o subboxter.o -Wall -lopenrk -O3

cc napwg.o subboxter.o -o napwg -Wall -lopenrk -O3

rm napwg.o subboxter.o

exit 0


