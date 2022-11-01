#include"GameController.h"

bool GameController::checkExistName(string Name)
{
	if (ListPlayer.count(Name) == 1)
	{
		return true;
	}
	return false;
}
void GameController::addPlayer(shared_ptr<Player> NewPlayer)
{
	ListPlayer.insert({ NewPlayer->getName(), NewPlayer });
}
map<string, shared_ptr<Player>> GameController::getListPlayer()
{
	return ListPlayer;
}

bool GameController::checkExistIDGame(int IDGame)
{
	if (ListGamePlayed.count(IDGame) == 1)
	{
		return true;
	}
	return false;
}
void GameController::addGame(shared_ptr<GameProperties> PlayedGame)
{
	ListGamePlayed.insert({ PlayedGame->getIDGame(), PlayedGame });
}
map<int, shared_ptr<GameProperties>> GameController::getListGameCaro()
{
	return ListGamePlayed;
}

bool GameController::checkIsFullBoard(shared_ptr<GameProperties> GamePlaying)
{
	if (GamePlaying->getSizeBoard()*GamePlaying->getSizeBoard() == GamePlaying->getNumOfTurn())
	{
		return true;
	}
	return false;
}
char GameController::checkWin(int Row, int Col, char Checked, shared_ptr<GameProperties> GamePlaying)
{
	if (!checkIsFullBoard(GamePlaying))
	{
        // Check Win
        vector<vector<char>> BoardCheck = GamePlaying->getPointOfBoard();
        int SizeBoard = GamePlaying->getSizeBoard();
		
		int Count = 1;
		int Step = 1;

        // Check by row
            //Check Right
        while (Col + Step < SizeBoard)
        {
            if (BoardCheck[Row][Col + Step] == Checked)
            {
                Count++;
                if (Count == 4)
                {
                    return Checked;
                }
                Step++;
            }
            else
            {
                Step = 1;
                break;
            }
        }
            //Check Left
        while (Col - Step >= 0)
        {
            if (BoardCheck[Row][Col - Step] == Checked)
            {
                Count++;
                if (Count == 4)
                {
                    return Checked;
                }
                Step++;
            }
            else
            {
                Step = 1;
                Count = 1;
                break;
            }
        }
        // Check by column
            //Check Down
        while (Row + Step < SizeBoard)
        {
            if (BoardCheck[Row + Step][Col] == Checked)
            {
                Count++;
                if (Count == 4)
                {
                    return Checked;
                }
                Step++;
            }
            else
            {
                Step = 1;
                break;
            }
        }
            //Check Up
        while (Row - Step >= 0)
        {
            if (BoardCheck[Row - Step][Col] == Checked)
            {
                Count++;
                if (Count == 4)
                {
                    return Checked;
                }
                Step++;
            }
            else
            {
                Step = 1;
                Count = 1;
                break;
            }
        }
        // Check by right diagonal
            //Check Down
        while (((Row + Step) < SizeBoard) && ((Col + Step) < SizeBoard))
        {
            if (BoardCheck[Row + Step][Col + Step] == Checked)
            {
                Count++;
                if (Count == 4)
                {
                    return Checked;
                }
                Step++;
            }
            else
            {
                Step = 1;
                break;
            }

        }
            //Check Up
        while (((Row - Step) >= 0) && ((Col - Step) >= 0))
        {
            if (BoardCheck[Row - Step][Col - Step] == Checked)
            {
                Count++;
                if (Count == 4)
                {
                    return Checked;
                }
                Step++;
            }
            else
            {
                Step = 1;
                Count = 1;
                break;
            }
        }
        // Check by Left diagonal
            //Check Down
        while (((Row + Step) < SizeBoard) && ((Col - Step) >= 0))
        {
            if (BoardCheck[Row + Step][Col - Step] == Checked)
            {
                Count++;
                if (Count == 4)
                {
                    return Checked;
                }
                Step++;
            }
            else
            {
                Step = 1;
                break;
            }
        }
            //Check Up
        while (((Row - Step) >= 0) && ((Col + Step) < SizeBoard))
        {
            if (BoardCheck[Row - Step][Col + Step] == Checked)
            {
                Count++;
                if (Count == 4)
                {
                    return Checked;
                }
                Step++;
            }
            else
            {
                Step = 1;
                Count = 1;
                break;
            }
        }
	}
    else if (checkIsFullBoard(GamePlaying))
    {
    //Case: Draw
    return 'D';
    }
}

shared_ptr<Player> GameController::findPlayer(string PlayerName)
{
    return ListPlayer.find(PlayerName)->second;
}

shared_ptr<Player> GameController::getSuitablePlayer(shared_ptr<Player> FoundedPlayer)
{
    shared_ptr<Player> tSuitablePlayer = ListPlayer.begin()->second;
    map<string, shared_ptr<Player>> tListPlayer = ListPlayer;
    tListPlayer.erase(ListPlayer.begin()->second->getName());
    tListPlayer.erase(FoundedPlayer->getName());
    // Founded Player
    double fWinRate = (double)(FoundedPlayer->getWin() / (FoundedPlayer->getWin() + FoundedPlayer->getLose() + FoundedPlayer->getDraw()));
    // First player
    double sWinRate = (double)(tSuitablePlayer->getWin() / (tSuitablePlayer->getWin() + tSuitablePlayer->getLose() + tSuitablePlayer->getDraw()));
    //
    double nearestDistWin = abs(sWinRate - fWinRate);
    // Find player by win rate
    for (auto i = tListPlayer.begin(); i != tListPlayer.end(); i++)
    {
        double tWinRate = (double)(i->second->getWin() / (i->second->getWin() + i->second->getLose() + i->second->getDraw()));
        double tDistWin = abs(tWinRate - fWinRate);
        if (nearestDistWin > tDistWin)
        {
            nearestDistWin = tDistWin;
            tSuitablePlayer = i->second;
        }
    }
    return tSuitablePlayer;
}