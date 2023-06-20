CXX=g++
CFLAGS=-Wall -Wextra -ggdb -pedantic -std=c++17
LIBS=-lsfml-graphics -lsfml-window -lsfml-system

all: compile link

compile:
	$(CXX) -Isrc/include -std=c++17 -c main.cpp
link:			
	$(CXX) main.o -o main -Lsrc/lib $(LIBS)