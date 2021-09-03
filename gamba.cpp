#include "gambaMachine.h"

using namespace std;


//STANFORDIAN STAMP OF APPROVAL** pending

int main(int argc, char* argv[]) {
	srand(time(0));

	string currentPlayer;
	string tempString;
	int bet = 1; //default bet is 1

	if (argc > 1) currentPlayer = argv[1];

	if (argc > 2) {
		tempString = argv[2];
		bet = stoi(tempString);
	}

	fstream fileDump;
	fileDump.open(currentPlayer + ".txt");
	string temp;
	getline(fileDump, temp);
	fileDump.close();
	
	gambaMachine gamba(0, bet);

	if (currentPlayer == "debug") {
		double repeats = 3000000; //default repeats
		if (argc > 3) {
			tempString = argv[3];
			repeats = stoi(tempString);
			repeats /= bet;
		}
		gamba.setDebug(true);
		gamba.setBalance(repeats * bet);
		gamba.bash((int) repeats);
	}

	else {
		if (temp == "") gamba.setBalance(5); //initial account creation means put $5 in
		else gamba.setBalance(stod(temp));
		//cout << endl << "Current Balance: " << balance << endl;
		if (gamba.getBalance() < 1) cout << "Please make a deposit soon" << endl;
		if (gamba.getBalance() < -499) {
			cout << "Your account has been frozen" << endl << endl;
			return -1;
		}
		cout << "Press Enter to start rollin the money..." << endl;
		cin.clear();
		cin.sync();
		cin.get();

		gamba.fullRoll();
	}

	fileDump.open(currentPlayer + ".txt", ios::out);
	fileDump << gamba.getBalance();
	if (currentPlayer == "debug") {
		for (int i = 0; i < 5; i++) {
			fileDump << endl << gamba.matchCounterAt(i);
		}
	}
	fileDump.close();

	return 0;
}



/*void matches(){
	for (int i = 0; i < BOARD_SIZE; i++){
		for (int j = 0; j < BOARD_SIZE; j++){
			string current = gambaBoard[i][j];
			if (i == BOARD_SIZE - 1){
				if (j == BOARD_SIZE - 1) return;
				if (matchesHelper(0, j + 1, current, 1)) return;
			}
			else{
				if (j == BOARD_SIZE - 1){
					if (matchesHelper(i + 1, 0, current, 1)) return;
				}
				if (matchesHelper(i + 1, j, current, 1)) return;
			}
		}
	}
}

bool matchesHelper(int row, int col, string current, int numRepeats){
	if 
}*/