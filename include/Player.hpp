#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include <Windows.h>
#include <sstream>
#include <direct.h>

#include "Console.hpp"
#include "String.hpp"
#include "CryptoCurrency.hpp"
using namespace std;

#define STARTING_COIN 1000
#define STARTING_HEALTH 25

#define NUM_OF_FOOD 6
#define NUM_OF_BANK_OP 4
#define NUM_OF_MOBILE 3
#define NUM_OF_CRYPTO_CHOICE 3

#define EXTRACT_OF_ACCOUNT 1
#define DEPOSIT_MONEY 2
#define WITHDRAW_MONEY 3

#define EXCHANGE_SYSTEM 1
#define CRYPTO_SYSTEM 2

#define LOOK_CRYPTO 1
#define BUY_CRYPTO 2
#define SELL_CRYPTO 3

class Console;
class CryptoCurrency;

class Player
{
private:
	string id;
	string password;
	string name;
	int health;
	int day;
	bool status;
	double coin;
	bool newAccountControl(string &id, string &password);
	void getIdPassword(string &id, string &password);
	double money_bank;
	bool newDay;
public:
	CryptoCurrency* cryptoCurrency;
	Player();
	~Player();
	void setId(string id);
	void setPassword(string password);
	void setName(string name);
	void setCoin(double coin);
	void setStatus(bool new_status);
	void setHealth(int health);
	void setNewDay(bool day_information);
	void changeDay(int amount);
	void changeCoin(double amount);
	void changeHealth(int amount);
	string getID();
	string getName();
	bool getStatus();
	int getDay();
	int getHealth();
	double getCoin();
	bool getNewDay();
	void newAccount();
	void login();
	void saveGame();
	void loadGame();
	void goToRestaurant();
	void goToBank();
	void mobilePhone();
	void exchangeSystem();
	void cryptoSystem();
};

