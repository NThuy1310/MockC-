#pragma once
#include<string>

using namespace std;

class Player
{
private:
	string Name;
	int Win;
	int Lose;
	int Draw;
public:
	Player();
	Player(string, int, int, int);
	~Player();

	void setName(string);
	void setWin(int);
	void setLose(int);
	void setDraw(int);

	string getName();
	int getWin();
	int getLose();
	int getDraw();

};