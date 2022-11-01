#include"GameProperties.h"

GameProperties::GameProperties()
{
	NumOfTurn = 0;
}
GameProperties::GameProperties(int IDGame, int SizeBoard, vector<vector<char>> PointOfBoard)
{
	this->IDGame = IDGame;
	this->SizeBoard = SizeBoard;
	this->PointOfBoard = PointOfBoard;
	NumOfTurn = 0;
}
GameProperties::~GameProperties()
{
	//
}

void GameProperties::setIDGame(int IDGame)
{
	this->IDGame = IDGame;
}
void GameProperties::setSizeBoard(int SizeBoard)
{
	this->SizeBoard = SizeBoard;
}
void GameProperties::initializeDefaultBoard(int SizeBoard)
{
	vector<vector<char>> DefaultBoard(SizeBoard, vector<char>(SizeBoard, ' '));
	PointOfBoard = DefaultBoard;
}
void GameProperties::addCheckedPoint(int Row, int Col, char Checked)
{
	PointOfBoard[Row][Col] = Checked;
	NumOfTurn++;
}
void GameProperties::addRecordPoint(shared_ptr<Record> CheckedRecord)
{
	PointRecord.push_back(CheckedRecord);
}

int GameProperties::getIDGame()
{
	return IDGame;
}
int GameProperties::getSizeBoard()
{
	return SizeBoard;
}
int GameProperties::getNumOfTurn()
{
	return NumOfTurn;
}
vector<vector<char>> GameProperties::getPointOfBoard()
{
	return PointOfBoard;
}
vector<shared_ptr<Record>> GameProperties::getPointRecord()
{
	return PointRecord;
}