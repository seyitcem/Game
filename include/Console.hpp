#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Player.hpp"
#include "CryptoCurrency.hpp"
using namespace std;

#define UPKEY 72
#define DOWNKEY 80
#define ENTERKEY 13

#define LOGIN 0
#define REGISTER 1
#define EXIT 2

#define NUM_OF_WELCOME 3
#define NUM_OF_GAMEMENU 4

#define RESTAURANT 0
#define BANK 1
#define MOBILE_PHONE 2
#define SAVE_AND_QUIT 3

class Player;
class CryptoCurrency;

class Console{
private:
	short x;
	short y;
	short padding;
public:
	Console();
	~Console();
	void welcome(Player &player);
	void game(Player &player);
	void gameMenu();
	void setX(short x);
	void setY(short y);
	void setXY(short x, short y);
	void setPadding(short padding);
	short getX();
	short getY();
	short getPadding();
	void changeX(short amount);
	void changeY(short amount);
	void content();
	static void clearScreen();
	void printArrow();
	void clearArrow();
	void gotoxy(short x, short y);
	int button(int numberOfOptions);
	void showCursor(bool cursorStatus);
	void newScreen(int padding);
	static void waitEnter();
};