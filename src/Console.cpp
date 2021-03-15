#include "Console.hpp"
Console::Console() {
	x = 0;
	y = 0;
	padding = 0;
}
Console::~Console(){

}
void Console::setX(short x){
	this->x = x;
}
void Console::setY(short y){
	this->y = y;
}
void Console::setPadding(short padding) {
	this->padding = padding;
	y += padding;
}
void Console::setXY(short x, short y) {
	this->x = x;
	this->y = y;
}
short Console::getX(){
	return x;
}
short Console::getY(){
	return y;
}
short Console::getPadding() {
	return padding;
}
void Console::changeX(short amount){
	x += amount;
}
void Console::changeY(short amount){
	y += amount;
}
void Console::gotoxy(short x, short y){
	COORD position = { this->x,this->y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}
void Console::clearScreen() {
	system("cls");
}
void Console::printArrow(){
	cout << "  -->";
}
void Console::clearArrow(){
	gotoxy(x, y);
	cout << "     ";
}
void Console::content(){
	cout << "\tLogin" << endl;
	cout << "\tRegister" << endl;
	cout << "\tExit" << endl;
}
void Console::showCursor(bool cursorStatus) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = cursorStatus;
	SetConsoleCursorInfo(out, &cursorInfo);
}
void Console::welcome(Player& player) {
	while (!(player.getStatus())) {
		showCursor(false);
		clearScreen();
		content();
		gotoxy(0, 0);
		printArrow();
		switch (button(NUM_OF_WELCOME)) {
		case LOGIN:
			clearScreen();
			player.login();
			break;
		case REGISTER:
			clearScreen();
			player.newAccount();
			break;
		case EXIT:
			clearScreen();
			return;
		}
	}
}
int Console::button(int numberOfOptions) {
	char ch = NULL;
	while (ch != ENTERKEY) {
		ch = _getch();
		switch (ch) {
		case UPKEY:
			if (getY() - getPadding() > 0) {
				gotoxy(getX(), getY());
				clearArrow();
				changeY(-1);
				gotoxy(getX(), getY());
				printArrow();
			}
			Sleep(200);
			break;
		case DOWNKEY:
			if (getY() - getPadding() < numberOfOptions - 1) {
				gotoxy(getX(), getY());
				clearArrow();
				changeY(+1);
				gotoxy(getX(), getY());
				printArrow();
			}
			Sleep(200);
			break;
		}
	}
	return getY() - getPadding();
}

void Console::game(Player& player) {
	clearScreen();
	static bool printControl = true;
	if (player.getDay() == 0 && printControl) {
		cout << "Welcome " << player.getName() << "," << endl << endl;
		cout << "Today, you woke up near the garbage dump." << endl;
		cout << "You do not know what happened you." << endl;
		cout << "The day will change your life." << endl;
		cout << "Today will be a milestone for the rest of your life." << endl << endl;
		cout << "You can press the ENTER to continue." << endl;
		waitEnter();
		printControl = false;
	}
	while (player.getHealth() > 0) {
		if (player.getNewDay()) {
			player.changeDay(1);
			player.cryptoCurrency->updateValues();
			player.setNewDay(false);
		}
		clearScreen();
		cout << "Day:" << player.getDay() << endl;
		cout << "Money:" << player.getCoin() << endl;
		cout << "Health:" << player.getHealth() << endl << endl;
		gameMenu();
		newScreen(NUM_OF_GAMEMENU);
		switch (button(NUM_OF_GAMEMENU)) {
		case RESTAURANT:
			player.goToRestaurant();
			break;
		case BANK:
			player.goToBank();
			break;

		case MOBILE_PHONE:
			player.mobilePhone();
			break;
		case SAVE_AND_QUIT:
			player.saveGame();
			player.setStatus(false);
			return;
		}
	}
	
}
void Console::gameMenu() {
	cout << "\tGo to restaurant" << endl;
	cout << "\tGo to bank" << endl;
	cout << "\tUse mobile phone" << endl;
	cout << "\tSave and Quit" << endl;
}
void Console::newScreen(int padding) {
	setXY(0, 0);
	setPadding(padding);
	gotoxy(getX(), getY());
	printArrow();
}
void Console::waitEnter() {
	while (true) {
		char ch = _getch();
		if (ch == ENTERKEY) break;
	}
}