#pragma once
#include"GameRecord.h"
#include<string>
#include<vector>
#include<memory>

using namespace std;

class GameProperties
{
private:
	int IDGame;
	int SizeBoard;
	int NumOfTurn;
	vector<vector<char>> PointOfBoard;
	vector<shared_ptr<Record>> PointRecord;
public:
	GameProperties();
	GameProperties(int, int, vector<vector<char>>);
	~GameProperties();

	void setIDGame(int);
	void setSizeBoard(int);
	void initializeDefaultBoard(int);
	void addCheckedPoint(int, int, char);
	void addRecordPoint(shared_ptr<Record>);

	int getIDGame();
	int getSizeBoard();
	int getNumOfTurn();
	vector<vector<char>> getPointOfBoard();
	vector<shared_ptr<Record>> getPointRecord();
};