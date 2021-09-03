#include <iostream>
#include <iomanip>
#include <random>
#include "time.h"
#include <unistd.h>
#include <fstream>
#include <string>

const int BOARD_SIZE = 3;

class gambaMachine {
public:
	gambaMachine();
	gambaMachine(double balance);
	gambaMachine(double balance, int betSize);
	gambaMachine(double balance, bool debug);
	gambaMachine(double balance, int betSize, bool debug);
	char roll();
	void swipe(int col);
	void print();
	void matches(char matchTypes[BOARD_SIZE * 2]);
	void updateBalance(char matchTypes[BOARD_SIZE * 2]);
	void bash(int repeats);
	void setBalance(double balance);
	double getBalance();
	double getInitialBalance();
	void fullRoll();
	void setDebug(bool debug);
	std::string matchCounterAt(int index);

private:
	bool debug;
	double initialBalance;
	double balance;
	int betSize;
	//[row][col]
	char gambaBoard[BOARD_SIZE][BOARD_SIZE] = {" "}; //could change to string, redefine 10 as 0... save space? edit: done did it
	int matchCounter[5] = {0}; //Index 0 - A, 1 - K, 2 - Q, 3 - J, 4 - 1 (only counts in debug mode)
};
