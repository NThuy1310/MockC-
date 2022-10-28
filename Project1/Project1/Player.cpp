#include"Player.h"

Player::Player()
{
	Name = ' ';
	Win = 0;
	Lose = 0;
	Draw = 0;
}
Player::Player(string Name, int Win, int Lose, int Draw)
{
	this->Name = Name;
	this->Win = Win;
	this->Lose = Lose;
	this->Draw = Draw;
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