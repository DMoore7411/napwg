
#/*******************************************************************************
#*                                                                              *
#* NAPWG - Not Another PassWord Generator                                       *
#* Makefile - napwg component                                                   *
#*                                                                              *
#* Copyright (C) 2021-2022 David Moore                                          *
#*                                                                              *
#* This program is free software: you can redistribute it and/or modify it      *
#* under the terms of the GNU General Public License as published by the Free   *
#* Software Foundation, either version 3 of the License, or (at your option)    *
#* any later version.                                                           *
#*                                                                              *
#* This program is distributed in the hope that it will be useful, but WITHOUT  *
#* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or        *
#* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for     *
#* more details.                                                                *
#*                                                                              *
#* You should have received a copy of the GNU General Public License along with *
#* this program. If not, see <https://www.gnu.org/licenses/>.                   *
#*                                                                              *
#* Any feedback is very welcome.                                                *
#* https://github.com/DMoore7411/napwg                                          *
#* email: davidmoore7411 @ gmail.com (remove spaces)                            *
#*                                                                              *
#*******************************************************************************/

CC = cc

CFLAGS = -Wall -lopenrk -lm -O3 

all: 
	$(CC) -c -fPIC napwg.c -o napwg.o $(CFLAGS)
	$(CC) -c -fPIC subboxter.c -o subboxter.o $(CFLAGS)
	$(CC) napwg.o subboxter.o -o napwg $(CFLAGS)

clean: 
	rm -f *.o

install: 
	cp napwg /usr/bin/napwg

uninstall: 
	rm /usr/bin/napwg

