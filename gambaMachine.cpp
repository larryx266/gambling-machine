#include "gambaMachine.h"

using namespace std;

gambaMachine::gambaMachine() {
	initialBalance = 0;
	balance = 0;
	betSize = 1;
	debug = false;
}

gambaMachine::gambaMachine(double balance) {
	initialBalance = balance;
	this->balance = balance;
	betSize = 1;
	debug = false;
}

gambaMachine::gambaMachine(double balance, int betSize) {
	initialBalance = balance;
	this->balance = balance;
	this->betSize = betSize;
	debug = false;
}

gambaMachine::gambaMachine(double balance, bool debug) {
	initialBalance = balance;
	this->balance = balance;
	betSize = 1;
	this->debug = debug;
}

gambaMachine::gambaMachine(double balance, int betSize, bool debug) {
	initialBalance = balance;
	this->balance = balance;
	this->betSize = betSize;
	this->debug = debug;
}

char gambaMachine::roll(){
	int r = rand() % 100 + 1;
	char result;

	if (r < 6) result = 'A';
	else if (r < 21) result = 'K';
	else if (r < 41) result = 'Q';
	else if (r < 66) result = 'J';
	/*else {
		r %= 8; // currently no 10, change this to 9 to include 10
		r += 2;
		if (r == 10) result = "10";
		else result = r + 48;
	}*/
	else result = '1';

	return result;
}

void gambaMachine::swipe(int col){
	for (int i = BOARD_SIZE - 1; i > 0; i--){
		gambaBoard[i][col] = gambaBoard[i - 1][col];
	}
	gambaBoard[0][col] = roll();
}

void gambaMachine::print(){
	if (debug) return;

	for (int i = 0; i < BOARD_SIZE; i++){
		for (int j = 0; j < BOARD_SIZE; j++){
			cout << gambaBoard[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void gambaMachine::matches(char matchTypes[BOARD_SIZE * 2]){
	bool noWin = true;
	for (int i = 0; i < BOARD_SIZE; i++){
		if (gambaBoard[i][0] == gambaBoard[i][1] && gambaBoard[i][0] == gambaBoard[i][2]){
			if (!debug) cout << "BIG WIN on Row " << i + 1 << "!!: " << gambaBoard[i][0] << endl;
			matchTypes[i] = gambaBoard[i][0]; //slap [0] at end to convert string to char
			noWin = false;
		}
		if (gambaBoard[0][i] == gambaBoard[1][i] && gambaBoard[0][i] == gambaBoard[2][i]){
			if (!debug) cout << "BIG WIN on Column " << i + 1 << "!!: " << gambaBoard[0][i] << endl;
			matchTypes[i + BOARD_SIZE] = gambaBoard[0][i]; 
			noWin = false;
		}
	}

	if (noWin){
		if (!debug) cout << "Try Again!!" << endl;
	}
}

void gambaMachine::updateBalance(char matchType[BOARD_SIZE * 2]){
	balance -= betSize;
	if (!debug) cout << betSize << " has been deducted from your account" << endl;

	for (int i = 0; i < BOARD_SIZE * 2; i++){
		if (matchType[i] == 'A') {
			balance += (betSize * 100);
			if (!debug) cout << betSize * 100 << " has been added to your account" << endl;
			else matchCounter[0]++;
		}
		else if (matchType[i] == 'K') {
			balance += (betSize * 10);
			if (!debug) cout << betSize * 10 << " has been added to your account" << endl;
			else matchCounter[1]++;
		}
		else if (matchType[i] == 'Q') {
			balance += (betSize * 5);
			if (!debug) cout << betSize * 5 << " has been added to your account" << endl; 
			else matchCounter[2]++;
		} 
		else if (matchType[i] == 'J') {
			balance += (betSize * 2);
			if (!debug) cout << betSize * 2 << " has been added to your account" << endl;
			else matchCounter[3]++;
		}
		else if (matchType[i] == '1') {
			balance += (betSize * 1);
			if (!debug) cout << betSize << " has been added to your account" << endl;
			else matchCounter[4]++;
		}
	}
}

void gambaMachine::bash(int repeats) {
	double initialBalance = balance;
	for (int i = 0; i < repeats; i++){
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				gambaBoard[i][j] = roll();
			}
		}
		char matchTypes[BOARD_SIZE * 2] = {' '};
		matches(matchTypes);
		updateBalance(matchTypes);
	}

	cout << fixed << endl << "Total payout after " << repeats << " rolls: " << 100 * balance / initialBalance;
	cout << "% across a total balance of $" << setprecision(2) << initialBalance << " at $" << betSize;
	cout << " per bet" << endl << endl;

}

void gambaMachine::setBalance(double balance) {
	initialBalance = balance;
	this->balance = balance;
}

double gambaMachine::getBalance(){
	return balance;
}

double gambaMachine::getInitialBalance() {
	return initialBalance;
}

void gambaMachine::fullRoll() {
	//generates initial board (v1)
	//generates one column at a time (v2)
	for (int i = 0; i < BOARD_SIZE; i++){
		char result = roll();
		gambaBoard[0][i] = result;
		print();

		for (int j = 1; j < 20; j++){
			usleep(10000 + j * 12000);
			swipe(i);
			print();
		}
		usleep(200000);
	}

	char matchTypes[BOARD_SIZE * 2] = {' '};
	matches(matchTypes);

	if (!debug) cout << "Starting Balance: " << balance << endl;
	updateBalance(matchTypes);
	if (!debug) cout << "Current Balance: " << balance << endl << endl;
}

void gambaMachine::setDebug(bool debug) {
	this->debug = debug;
}

string gambaMachine::matchCounterAt(int index) {
	string result = "# of ";
	if (index == 0) result += "A";
	else if (index == 1) result += "K";
	else if (index == 2) result += "Q";
	else if (index == 3) result += "J";
	else if (index == 4) result += "1";
	result += " matches: ";
	result += to_string(matchCounter[index]);
	result += " (";
	result += to_string(100 * matchCounter[index] / (initialBalance * betSize));
	result += "%)";
	return result;
}
