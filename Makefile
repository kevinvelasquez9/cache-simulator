#
# Christian Helgeson and Kevin Velasquez
# CSF Fall 2020
# Assignment 3: Cache Simulator
#

FLAGS = -g -Wall -Wextra --pedantic

csim: main.o cache.o
	g++ -o csim $(FLAGS) main.o cache.o

main.o: main.cpp cache.h 
	g++ -c $(FLAGS) main.cpp