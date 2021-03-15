#include "CryptoCurrency.hpp"
CryptoCurrency::CryptoCurrency() {
	int i;
	srand((unsigned int)time(NULL));
	for (i = 0;i < NUM_OF_CRYPTO_CURRENCY;i++) {
		ownedCoin[i] = 0.0;
		coin[i] = 100;  // base
		coin[i] += (rand() % 100);
		coin[i] += (rand() % 1000) / 1000.0;
		lastChangeRate[i] = 0.0;
	}
}
string CryptoCurrency::getNameAt(int order) {
	switch (order) {
	case ACC:
		return "ACC";
	case EPT:
		return "EPT";
	case PLS:
		return "PLS";
	default:
		throw 2;
	}
}
double CryptoCurrency::getOwnedCoinAt(int order) {
	return ownedCoin[order];
}
double CryptoCurrency::getCoinAt(int order) {
	return coin[order];
}
double CryptoCurrency::getChangeRateAt(int order) {
	return lastChangeRate[order];
}
void CryptoCurrency::setCoinAt(int order, double value) {
	coin[order] = value;
}
void CryptoCurrency::setOwnedCoinAt(int order, double value) {
	ownedCoin[order] = value;
}
void CryptoCurrency::setChangeRateAt(int order, double value) {
	lastChangeRate[order] = value;
}
void CryptoCurrency::printCoins() {
	int i;
	cout << "\tCoin\t\tValue\t\tOwned\t\tChange Rate" << endl;
	for (i = 0;i < NUM_OF_CRYPTO_CURRENCY;i++) {
		cout << "\t" << getNameAt(i) << "\t\t" << coin[i] << "\t\t" << ownedCoin[i] << "\t\t" << lastChangeRate[i] << endl;
	}
}
void CryptoCurrency::look() {
	Console console;
	cout << "Coins which are available to buy are demonstrating." << endl << endl;
	printCoins();
	cout << endl << "You can press the ENTER to quit." << endl << endl;
	console.waitEnter();
}
void CryptoCurrency::buy(Player &player) {
	Console console;
	cout << "Coins which are available to buy are demonstrating." << endl << endl;
	printCoins();
	console.newScreen(3);
	buyCrypto(player, console.button(NUM_OF_CRYPTO_CURRENCY));
	Sleep(1000);
}
void CryptoCurrency::buyCrypto(Player &player, int choice) {
	double amount;
	Console console;
	console.clearScreen();
	cout << "Dear " << player.getName() << ", You have " << player.getCoin() << " coin." << endl;
	cout << "You want to buy " << getNameAt(choice) << endl;
	cout << "Its price is " << getCoinAt(choice) << endl << endl;
	cout << "How much do you want to buy:";
	cin >> amount;
	if (amount <= 0) {
		throw 1;
	}
	else {
		if (amount * getCoinAt(choice) <= player.getCoin()) {
			ownedCoin[choice] += amount;
			player.changeCoin(-(amount * getCoinAt(choice)));
			console.clearScreen();
			cout << "You bought " << amount << " " << getNameAt(choice) << "." << endl;
			Sleep(1000);
		}
		else {
			throw 3;
		}
	}
}
void CryptoCurrency::sell(Player &player) {
	Console console;
	cout << "Coins which are available to sell are demonstrating." << endl << endl;
	printCoins();
	console.newScreen(3);
	sellCrypto(player, console.button(NUM_OF_CRYPTO_CURRENCY));
	Sleep(1000);
}
void CryptoCurrency::sellCrypto(Player& player, int choice) {
	double amount;
	Console console;
	console.clearScreen();
	cout << "Dear " << player.getName() << ", You have " << player.getCoin() << " coin." << endl;
	cout << "You want to sell " << getNameAt(choice) << endl;
	cout << "Its price is " << getCoinAt(choice) << endl << endl;
	cout << "How much do you want to sell:";
	cin >> amount;
	if (amount <= 0) {
		throw 1;
	}
	else {
		if (getOwnedCoinAt(choice) >= amount) {
			ownedCoin[choice] -= amount;
			player.changeCoin((amount * getCoinAt(choice)));
			console.clearScreen();
			cout << "You sold " << amount << " " << getNameAt(choice) << "." << endl;
			Sleep(1000);
		}
		else {
			throw 2;
		}
	}
}
void CryptoCurrency::updateValues() {
	int i;
	srand(time(NULL));
	for (i = 0;i < NUM_OF_CRYPTO_CURRENCY;i++) {
		if (rand() % 2) {
			lastChangeRate[i] = rand() % 12;
			if (rand() % 2) {
				lastChangeRate[i] += (rand() % 1000) / 1000.0;
			}
			else {
				lastChangeRate[i] -= (rand() % 100) / 100.0;
			}
		}
		else {
			lastChangeRate[i] = -(rand() % 12);
			if (rand() % 2) {
				lastChangeRate[i] += (rand() % 1000) / 1000.0;
			}
			else {
				lastChangeRate[i] -= (rand() % 100) / 100.0;
			}
		}
		coin[i] *= 1.0 + lastChangeRate[i] / 100.0;
	}
}