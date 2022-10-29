#pragma once
#include"Player.h"
#include"GameProperties.h"
#include<map>
#include<memory>

class GameController
{
protected:
	map<string, shared_ptr<Player>> ListPlayer;
	map<int, shared_ptr<GameProperties>> ListGamePlayed;
public:
	bool checkExistName(string);
	void addPlayer(shared_ptr<Player>);
	map<string, shared_ptr<Player>> getListPlayer();

	bool checkExistIDGame(int);
	void addGame(shared_ptr<GameProperties>);
	map<int, shared_ptr<GameProperties>> ListGameCaro();

	bool checkIsFullBoard(shared_ptr<GameProperties>);
	char checkWin(int ,int , char, shared_ptr<GameProperties>);
	void updatePlayerInfo();
	void changeTurn();
};