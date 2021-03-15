#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Console.hpp"
#include "Player.hpp"
using namespace std;

#define NUM_OF_CRYPTO_CURRENCY 3

class Player;
class Console;

enum eCryptoName{
	ACC,
	EPT,
	PLS,
};

class CryptoCurrency
{
private:
	double coin[NUM_OF_CRYPTO_CURRENCY];
	double ownedCoin[NUM_OF_CRYPTO_CURRENCY];
	double lastChangeRate[NUM_OF_CRYPTO_CURRENCY];
	void buyCrypto(Player &player, int choice);
	void sellCrypto(Player& player, int choice);
public:
	CryptoCurrency();
	string getNameAt(int order);
	double getOwnedCoinAt(int order);
	double getCoinAt(int order);
	double getChangeRateAt(int order);
	void setCoinAt(int order, double value);
	void setOwnedCoinAt(int order, double value);
	void setChangeRateAt(int order,double value);
	void printCoins();
	void look();
	void buy(Player &player);
	void sell(Player& player);
	void updateValues();
};

