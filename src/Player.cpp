#include "Player.hpp"
Player::Player() {
	coin = STARTING_COIN;
	health = STARTING_HEALTH;
	status = false;
	newDay = false;
	day = 0;
	money_bank = 0;
	cryptoCurrency = new CryptoCurrency();
}
Player::~Player() {
	delete cryptoCurrency;
}
void Player::setId(string id) {
	this->id = id;
}
void Player::setPassword(string password) {
	this->password = String::hash(password);
}
void Player::setName(string name) {
	this->name = name;
}
void Player::setCoin(double coin) {
	this->coin = coin;
}
void Player::setStatus(bool new_status) {
	this->status = new_status;
}
void Player::setHealth(int health) {
	this->health = health;
}
string Player::getID() {
	return id;
}
string Player::getName() {
	return name;
}
int Player::getDay() {
	return day;
}
int Player::getHealth() {
	return health;
}
double Player::getCoin() {
	return coin;
}
bool Player::getStatus() {
	return status;
}
bool Player::getNewDay() {
	return newDay;
}
void Player::changeCoin(double amount) {
	this->coin += amount;
}
void Player::changeDay(int amount) {
	day += amount;
}
void Player::changeHealth(int amount) {
	health += amount;
}
void Player::setNewDay(bool day_information) {
	newDay = day_information;
}
void Player::newAccount() {
	string id;
	string password;
	string name;
	while (getStatus() == false) {
		cout << "#### NEW ACCOUNT ####" << endl;
		getIdPassword(id,password);
		Console::clearScreen();
		if (String::isIdValid(id) && String::isPasswordValid(password)) {
			if (newAccountControl(id, password) == true) {
				Console::clearScreen();
				while (true) {
					cout << "Enter name:";
					cin >> name;
					if (String::isNameValid(name)) 
					{
						setName(name);
						break;
					}
					else {
						Console::clearScreen();
						cout << "Invalid name. Please try another name." << endl;
					}
				}
				saveGame();
				setStatus(true);
			}
			else {
				newAccount();
			}
		}
	}

}
bool Player::newAccountControl(string &id, string &password) {
	string id_temp;
	string pass_temp;
	ifstream ifs("accounts.txt");
	ofstream ofs("accounts.txt", fstream::app);

	while (ifs >> id_temp >> pass_temp) {
		if (id_temp == id) {
			cout << "The ID is already used." << endl;
			return false;
		}
	}

	this->id = id;

	ofs << id << " " << String::hash(password) << endl;
	ifs.close();
	ofs.close();
	return true;
}
void Player::login() {
	string id;
	string password;
	string id_temp;
	string pass_temp;
	ifstream ifs("accounts.txt");
	getIdPassword(id,password);
	while (ifs >> id_temp >> pass_temp) {
		if (id_temp == id) {
			if (String::hash(password) == pass_temp) {
				Console::clearScreen();
				setStatus(true);
				setId(id);
				setPassword(password);
				loadGame();
				cout << "Login successful." << endl;
				Sleep(1000);
				return;
			}
		}
	}
	cout << "Wrong ID or password." << endl;
	ifs.close();
	Sleep(1000);
}
void Player::saveGame() {
	if(_mkdir("database"));
	int i;
	stringstream location;
	location << "database/" << getID() << ".txt";
	ofstream ofs(location.str().c_str());

	ofs << name << endl;
	ofs << health << endl;
	ofs << day << endl;
	ofs << coin << endl; 
	ofs << money_bank << endl;

	for (i = 0;i < NUM_OF_CRYPTO_CURRENCY;i++) {
		ofs << cryptoCurrency->getCoinAt(i) << endl;
	}
	for (i = 0;i < NUM_OF_CRYPTO_CURRENCY;i++) {
		ofs << cryptoCurrency->getOwnedCoinAt(i) << endl;
	}
	for (i = 0;i < NUM_OF_CRYPTO_CURRENCY;i++) {
		ofs << cryptoCurrency->getChangeRateAt(i) << endl;
	}

	Console::clearScreen();
	cout << "The game is saved." << endl;
	Sleep(1000);
	ofs.close();
}
void Player::loadGame() {
	int i;
	double value;
	string str_val;
	stringstream location;
	location << "database/" << getID().c_str() << ".txt";
	ifstream ifs(location.str().c_str());
	ifs >> name;
	ifs >> health;
	ifs >> day;
	ifs >> coin;
	ifs >> money_bank;
	for (i = 0;i < NUM_OF_CRYPTO_CURRENCY;i++) {
		ifs >> value;
		cryptoCurrency->setCoinAt(i,value);
	}
	for (i = 0;i < NUM_OF_CRYPTO_CURRENCY;i++) {
		ifs >> value;
		cryptoCurrency->setOwnedCoinAt(i,value);
	}
	for (i = 0;i < NUM_OF_CRYPTO_CURRENCY;i++) {
		ifs >> value;
		cryptoCurrency->setChangeRateAt(i, value);
	}
	ifs.close();
}
void Player::getIdPassword(string &id, string &password) {
	char ch = NULL;
	cout << "ID:";
	cin >> id;
	String::lowerCase(id);
	cout << "Password:";
	password = "";
	while (ch != 13) {
		ch = _getch();
		if (ch == 8) {
			if (password.length() > 0) {
				cout << "\b \b";
				password.erase(password.end() - 1, password.end());
			}
		}
		else if (ch == 13){
			cout << endl;
			break;
		}
		else {
			cout << "*";
			password += ch;
		}
	}
}
void Player::goToRestaurant() {
	Console console;
	console.clearScreen();

	cout << "Welcome " << name << "," << endl;
	cout << "What you want to eat?" << endl << endl;
	cout << "\tSalad			+10 health		20$" << endl;
	cout << "\tFrench Fries		+20 health		30$" << endl;
	cout << "\tSchnitzel		+30 health		40$" << endl;
	cout << "\tHamburger		+40 health		50$" << endl;
	cout << "\tPizza			+50 health		60$" << endl;
	cout << "\tExit" << endl;

	console.newScreen(3);

	int choice = console.button(NUM_OF_FOOD) + 1;

	if (choice != NUM_OF_FOOD) {
		console.clearScreen();
		int healthAmount = choice * 10;
		if (getHealth() == 100) {
			cout << "You are full." << endl;
			Sleep(1000);
		}
		else {
			if (coin - (10 + healthAmount) < 0) {
				throw 3;
			}
			if (getHealth() + healthAmount > 100) {
				cout << "You gain " << 100 - getHealth() << " health." << endl;
				cout << "You lose " << 10 + healthAmount << " coin." << endl;
				setHealth(100);
				changeCoin(-(10 + healthAmount));
				Sleep(1000);
			}
			else {
				cout << "You gain " << healthAmount << " health." << endl;
				cout << "You lose " << 10 + healthAmount << " coin." << endl;
				changeCoin(-(10 + healthAmount));
				changeHealth(+healthAmount);
				Sleep(1000);
			}
			setNewDay(true);
		}
	}
}
void Player::goToBank() {
	double amount;
	Console console;
	console.clearScreen();

	cout << "Welcome " << name << "," << endl;
	cout << "What you want to do?" << endl << endl;
	cout << "\tExtract of account" << endl;
	cout << "\tDeposit money" << endl;
	cout << "\tWithdraw money" << endl;
	cout << "\tExit" << endl;

	console.newScreen(3);

	int choice = console.button(NUM_OF_BANK_OP) + 1;
	console.clearScreen();
	cout << "You have " << money_bank << " coin in your bank account." << endl << endl;
	switch (choice) {
	case EXTRACT_OF_ACCOUNT:
		Sleep(1000);
		break;
	case DEPOSIT_MONEY:
		cout << "How much money do you want to deposit:";
		cin >> amount;
		if (amount < 0) {
			throw 1;
		}
		else if (getCoin() >= amount) {
			changeCoin(-amount);
			money_bank += amount;
			console.clearScreen();
			cout << amount << " coin has been transferred to your bank account." << endl;
			setNewDay(true);
			Sleep(1000);
		}
		else {
			throw 3;
		}
		break;
	case WITHDRAW_MONEY:
		cout << "How much money do you want to withdraw:";
		cin >> amount;
		if (amount <= 0) {
			throw 1;
		}
		else if (money_bank >= amount) {
			changeCoin(+amount);
			money_bank -= amount;
			console.clearScreen();
			cout << "You take " << amount << " coin from your bank account." << endl;
			setNewDay(true);
			Sleep(1000);
		}
		else {
			throw 3;
		}
		break;
	}
}
void Player::mobilePhone() {
	Console console;
	console.clearScreen();
	cout << "You opened your phone." << endl;
	cout << "What you want to do?" << endl << endl;

	cout << "\tCheck the exchange" << endl;
	cout << "\tCheck the crypto currency exchange" << endl;
	cout << "\tExit" << endl;

	console.newScreen(3);

	int choice = console.button(NUM_OF_MOBILE) + 1;
	console.clearScreen();

	switch (choice) {
	case EXCHANGE_SYSTEM:
		exchangeSystem();
		break;
	case CRYPTO_SYSTEM:
		cryptoSystem();
		break;
	}
}
void Player::cryptoSystem() {
	Console console;
	console.clearScreen();
	cout << "Welcome to crypto currency exchange." << endl;
	cout << "Do not forget that when you trade crypto currency you can lose or earn money." << endl << endl;
	
	cout << "\tLook at the crypto currencies" << endl;
	cout << "\tBuy crypto currency" << endl;
	cout << "\tSell crypto currency" << endl;

	console.newScreen(3);

	int choice = console.button(NUM_OF_CRYPTO_CHOICE) + 1;
	console.clearScreen();

	switch (choice) {
	case LOOK_CRYPTO:
		cryptoCurrency->look();
		break;
	case BUY_CRYPTO:
		cryptoCurrency->buy(*this);
		break;
	case SELL_CRYPTO:
		cryptoCurrency->sell(*this);
		break;
	}
}
void Player::exchangeSystem() {

}