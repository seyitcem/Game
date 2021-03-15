#include "main.hpp"

int main()
{
	Player player;
	Console console;
	console.welcome(player);
	while (player.getStatus() == true) {
		try {
			console.game(player);
		}
		catch (int exception) {
			if (exception == 1) {
				console.clearScreen();
				cerr << "The amount which is entered should be more than 0." << endl;
				Sleep(1000);
			}
			else if (exception == 2) {
				console.clearScreen();
				cerr << "Please check coins." << endl;
				Sleep(1000);
			}
			else if (exception == 3) {
				console.clearScreen();
				cerr << "Operation failed. Insufficient balance." << endl;
				Sleep(1000);
			}
		}
	}
	if(player.getStatus() == false) {
		console.clearScreen();
		cout << "Exit process completed." << endl;
	}
	return 0;
}