#pragma once
#include<string>
#include<vector>

using namespace std;

class GameProperties
{
private:
	int IDGame;
	int SizeBoard;
	int NumOfTurn;
	vector<vector<char>> PointOfBoard;

public:
	GameProperties();
	GameProperties(int, int, vector<vector<char>>);
	~GameProperties();

	void setIDGame(int);
	void setSizeBoard(int);
	void initializeDefaultBoard(int);
	void addCheckedPoint(int, int, char);

	int getIDGame();
	int getSizeBoard();
	int getNumOfTurn();
	vector<vector<char>> getPointOfBoard();
};