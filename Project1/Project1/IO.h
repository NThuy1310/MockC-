#pragma once
#include"GameController.h"
#include"ConsoleSetting.h"
#include<iostream>
#include<iomanip>

enum ChoiceMode
{
	KEY_BOARD = 1,
	MOUSE_CLICK =2
};

class IO
{
private:
	GameController controller;
public:
	void newGame();
	/*void Continue();*/
	void showPlayerInfo();
	void showAllPlayer();
	void guide();

	int inputValidIndex(int);
	int inputValidNumber();
	bool checkPointInvalid(int, int, shared_ptr<GameProperties>);
	bool checkInvalidPointFromKeyBoard(int, int, shared_ptr<GameProperties>);
	void changeTurn(char&);
	

	void displayBoard(int, string, string);
	void displayPointChecked(int, int, char);
};