all: gamba

gamba: gambaMachine.o gamba.cpp
	g++ -g -Wall gamba.cpp gambaMachine.o -o gamba

gambaMachine.o: gambaMachine.cpp gambaMachine.h
	g++ -g -Wall -c gambaMachine.cpp -o gambaMachine.o
