#include"Player.h"

Player::Player()
{
	//
}
Player::Player(string Name)
{
	this->Name = Name;
	Win = 0;
	Lose = 0;
	Draw = 0;
}
Player::~Player()
{
	//
}

void Player::setName(string Name)
{
	this->Name = Name;
}
void Player::setWin(int Win)
{
	this->Win = Win;
}
void Player::setLose(int Lose)
{
	this->Lose = Lose;
}
void Player::setDraw(int Draw)
{
	this->Draw = Draw;
}

string Player::getName()
{
	return Name;
}
int Player::getWin()
{
	return Win;
}
int Player::getLose()
{
	return Lose;
}
int Player::getDraw()
{
	return Draw;
}
float Player::getWinRate()
{
	float WinRate = ((float)Win) / ((float)Win + (float)Lose + (float)Draw);
	return WinRate;
}