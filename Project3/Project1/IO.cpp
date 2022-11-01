#include"IO.h"

void IO::newGame()
{
	SetConsoleTitle(L"New Game");
	int IDGame;
	cout << "Enter game ID: ";
	IDGame = inputValidNumber();
	while (controller.checkExistIDGame(IDGame))
	{
		cout << "ID game has been existed." << endl;
		cout << "Please enter ID again." << endl;
		IDGame = inputValidNumber();
	}

	string Name1, Name2;
	cout << "Enter name of player 1: " << endl;
	getline(cin >> ws, Name1);
	while (controller.checkExistName(Name1))
	{
		cout << "Player name has been existed." << endl;
		cout << "Please enter Name again." << endl;
		getline(cin >> ws, Name1);
	}

	shared_ptr<Player> tPlayer1(new Player(Name1));

	cout << "Enter name of player 2: " << endl;
	getline(cin >> ws, Name2);
	while (controller.checkExistName(Name2))
	{
		cout << "Player name has been existed." << endl;
		cout << "Please enter Name again." << endl;
		getline(cin >> ws, Name2);
	}

	shared_ptr<Player> tPlayer2(new Player(Name2));

	int Size;
	cout << "Enter size of Board: " << endl;
	Size = inputValidNumber();
	shared_ptr<GameProperties> tCaro(new GameProperties);
	tCaro->setIDGame(IDGame);
	tCaro->setSizeBoard(Size);
	tCaro->initializeDefaultBoard(Size);
	char Turn = 'X';
	bool IsEnd = false;
	// select mode point
	cout << "Select check point mode: " << endl;
	cout << "1. Check by keyboard." << endl;
	cout << "2. Check by mouse click." << endl;
	int choice = inputValidNumber();
	while (choice != 1 && choice != 2)
	{
		cout << "Faulty input. Try again: " << endl;
		int choice = inputValidNumber();
	}
	switch (choice)
	{
	case KEY_BOARD:
	{
		system("cls");
		displayBoard(Size, Name1, Name2);
		do
		{
			// Display turn
			SettingWindow::gotoXY(0, 2 * Size + 4);
			if (Turn == 'X')
			{
				SettingWindow::textColor(0, 14);
				cout << "Turn: Play 1 <X>";
			}
			else if (Turn == 'O')
			{
				SettingWindow::textColor(0, 14);
				cout << "Turn: Play 2 <O>";
			}
			
			// Replace console window
			for (int i = 0; i < 100; i++)
			{
				for (int j = 2 * Size + 5; j < 2 * Size + 10; j++)
				{
					SettingWindow::gotoXY(i, j);
					cout << " ";
				}
			}
			cout << endl;
			//
			SettingWindow::gotoXY(0, 2 * Size + 5);
			cout << "Enter position of checked point: " << endl;
			cout << "Row: " << endl;
			int rRow = inputValidIndex(Size);
			cout << "Col: " << endl;
			int rCol = inputValidIndex(Size);
			//
			if (checkInvalidPointFromKeyBoard(rRow, rCol, tCaro))
			{
				SettingWindow::textColor(0, 4);
				SettingWindow::gotoXY(4 * Size + 5, 5);
				cout << "Invalid checked." << endl;
			}
			else
			{
				tCaro->addCheckedPoint(rRow - 1, rCol - 1, Turn);
				shared_ptr<Record> tPointChecked(new Record(rRow - 1, rCol - 1, Turn));
				tCaro->addRecordPoint(tPointChecked);
				displayPointChecked(rRow - 1, rCol - 1, Turn);
				//Replace invalid checked message
				SettingWindow::gotoXY(4 * Size + 5, 5);
				cout << "                " << endl;
				// Replace console window
				for (int i = 0; i < 100; i++)
				{
					for (int j = 2 * Size + 5; j < 2 * Size + 10; j++)
					{
						SettingWindow::gotoXY(i, j);
						cout << " ";
					}
				}
				cout << endl;
				// check win
				if (controller.checkWin(rRow - 1, rCol - 1, Turn, tCaro) == 'X')
				{
					SettingWindow::textColor(0, 14);
					SettingWindow::gotoXY(0, 2 * Size + 5);
					cout << "Player 1: " << tPlayer1->getName() << " win." << endl;
					tPlayer1->setWin(tPlayer1->getWin() + 1);
					tPlayer2->setLose(tPlayer2->getLose() + 1);
					controller.addPlayer(tPlayer1);
					controller.addPlayer(tPlayer2);

					cout << "Game Over." << endl;
					IsEnd = true;
				}
				else if (controller.checkWin(rRow - 1, rCol - 1, Turn, tCaro) == 'O')
				{
					SettingWindow::textColor(0, 14);
					SettingWindow::gotoXY(0, 2 * Size + 5);
					cout << "Player 2: " << tPlayer2->getName() << " win." << endl;
					tPlayer2->setWin(tPlayer2->getWin() + 1);
					tPlayer1->setLose(tPlayer1->getLose() + 1);
					controller.addPlayer(tPlayer1);
					controller.addPlayer(tPlayer2);

					cout << "Game Over." << endl;
					IsEnd = true;
				}
				else if (controller.checkWin(rRow - 1, rCol - 1, Turn, tCaro) == 'D')
				{
					SettingWindow::textColor(0, 14);
					SettingWindow::gotoXY(0, 2 * Size + 5);
					cout << "Draw" << endl;
					tPlayer2->setDraw(tPlayer2->getDraw() + 1);
					tPlayer1->setDraw(tPlayer1->getDraw() + 1);
					controller.addPlayer(tPlayer1);
					controller.addPlayer(tPlayer2);

					cout << "Game Over." << endl;
					IsEnd = true;
				}

				changeTurn(Turn);
			}
		} while (!IsEnd);
		controller.addGame(tCaro);
		break;
	}
	case MOUSE_CLICK:
	{
		system("cls");
		displayBoard(Size, Name1, Name2);

		// get mouse click position
		INPUT_RECORD ir[128];
		HANDLE       hStdInput = NULL;
		HANDLE       hStdOutput = NULL;
		HANDLE       hEvent = NULL;
		DWORD        nRead;
		COORD        xy;

		hStdInput = GetStdHandle(STD_INPUT_HANDLE);
		hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleMode(hStdInput, ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
		FlushConsoleInputBuffer(hStdInput);
		hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		HANDLE handles[2] = { hEvent, hStdInput };
		while (WaitForMultipleObjects(2, handles, FALSE, INFINITE))
		{
			ReadConsoleInput(hStdInput, ir, 128, &nRead);
			for (size_t i = 0; i < nRead; i++)
			{
				// Display turn
				SettingWindow::gotoXY(0, 2 * Size + 4);
				if (Turn == 'X')
				{
					SettingWindow::textColor(0, 14);
					cout << "Turn: Play 1 <X>";
				}
				else if (Turn == 'O')
				{
					SettingWindow::textColor(0, 14);
					cout << "Turn: Play 2 <O>";
				}
				xy.X = 0;
				xy.Y = 2 * Size + 5;
				SetConsoleCursorPosition(hStdOutput, xy);

				// Checked point by mouse left click
				int Col = ir[i].Event.MouseEvent.dwMousePosition.X;
				int Row = ir[i].Event.MouseEvent.dwMousePosition.Y;
				if (ir[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
				{
					if (checkPointInvalid(Row, Col, tCaro))
					{
						SettingWindow::textColor(0, 4);
						SettingWindow::gotoXY(4 * Size + 5, 5);
						cout << "Invalid checked." << endl;
					}
					else
					{
						int realRow = (Row - 2) / 2;
						int realCol = (Col + 1) / 4;
						tCaro->addCheckedPoint(realRow, realCol, Turn);
						shared_ptr<Record> pPointChecked(new Record(realRow, realCol, Turn));
						tCaro->addRecordPoint(pPointChecked);
						//Replace invalid checked message
						SettingWindow::gotoXY(4 * Size + 5, 5);
						cout << "                " << endl;
						// display point
						displayPointChecked(realRow, realCol, Turn);
						// Check win when a point is checked in board chess
						if (controller.checkWin(realRow, realCol, Turn, tCaro) == 'X')
						{
							SettingWindow::textColor(0, 14);
							SettingWindow::gotoXY(0, 2 * Size + 5);
							cout << "Player 1: " << tPlayer1->getName() << " win." << endl;
							tPlayer1->setWin(tPlayer1->getWin() + 1);
							tPlayer2->setLose(tPlayer2->getLose() + 1);
							controller.addPlayer(tPlayer1);
							controller.addPlayer(tPlayer2);

							cout << "Game Over." << endl;
							IsEnd = true;
						}
						else if (controller.checkWin(realRow, realCol, Turn, tCaro) == 'O')
						{
							SettingWindow::textColor(0, 14);
							SettingWindow::gotoXY(0, 2 * Size + 5);
							cout << "Player 2: " << tPlayer2->getName() << " win." << endl;
							tPlayer2->setWin(tPlayer2->getWin() + 1);
							tPlayer1->setLose(tPlayer1->getLose() + 1);
							controller.addPlayer(tPlayer1);
							controller.addPlayer(tPlayer2);

							cout << "Game Over." << endl;
							IsEnd = true;
						}
						else if (controller.checkWin(realRow, realCol, Turn, tCaro) == 'D')
						{
							SettingWindow::textColor(0, 14);
							SettingWindow::gotoXY(0, 2 * Size + 5);
							cout << "Draw" << endl;
							tPlayer2->setDraw(tPlayer2->getDraw() + 1);
							tPlayer1->setDraw(tPlayer1->getDraw() + 1);
							controller.addPlayer(tPlayer1);
							controller.addPlayer(tPlayer2);

							cout << "Game Over." << endl;
							IsEnd = true;
						}
						if (IsEnd)
						{
							controller.addGame(tCaro);
							return;
						}
						changeTurn(Turn);
					}
				}
			}
		}
		break;
	}
	}
}

//void Continue();
void IO::showPlayerInfo()
{
	SetConsoleTitle(L"Player Information");
	/*SetConsoleOutputCP(65001);*/
	string Name;
	SetConsoleTitle(L"Information");
	cout << "Enter player name: " << endl;
	getline(cin >> ws, Name);
	if (controller.checkExistName(Name))
	{
		cout << "Fouded player: " << endl;
		shared_ptr<Player> tPlayer = controller.getListPlayer().find(Name)->second;
		cout << "Name " << tPlayer->getName() << endl;
		cout << "Win = " << tPlayer->getWin() << endl;
		cout << "Lose = " << tPlayer->getLose() << endl;
		cout << "Draw = " << tPlayer->getDraw() << endl;
	}
	else
	{
		cout << "Player does not exist." << endl;
	}
}
void IO::showAllPlayer()
{
	SetConsoleTitle(L"Player Information");
	/*SetConsoleOutputCP(65001);*/
	map<string, shared_ptr<Player>> tListPlayer = controller.getListPlayer();

	if (tListPlayer.size() == 0)
	{
		cout << "No player date yet." << endl;
	}
	else
	{
		cout << "All player info: " << endl;
		int tcount = 1;
		for (auto i = tListPlayer.begin(); i != tListPlayer.end(); i++)
		{
			cout << "* Player " << tcount << endl;
			cout << "Name: " << i->second->getName() << endl;
			cout << "Win = " << i->second->getWin() << endl;
			cout << "Lose = " << i->second->getLose() << endl;
			cout << "Draw = " << i->second->getDraw() << endl;
			tcount++;
		}
	}
}
void IO::guide()
{
	SetConsoleTitle(L"Caro Guide");
	SetConsoleOutputCP(65001);
	cout << "Instructions for playing chess game Caro: " << endl;
	cout << "1. New Game: start a new game." << endl;
	cout << "2. Search for player information through the username." << endl;
	cout << "3. Display all player information." << endl;
	cout << "* Rules: each player plays checkers that is to achieve a straight, diagonal, horizontal line with 5 cells fastest." <<endl;
}
void IO::findSuitableOpponent()
{
	SetConsoleTitle(L"Find Player");
	string Name;
	cout << "Enter player Name you want to find: " << endl;
	getline(cin >> ws, Name);
	if (controller.checkExistName(Name))
	{
		cout << "* Fouded player: " << endl;
		shared_ptr<Player> tPlayer = controller.getListPlayer().find(Name)->second;
		cout << "Name " << tPlayer->getName() << endl;
		cout << "Win = " << tPlayer->getWin() << endl;
		cout << "Lose = " << tPlayer->getLose() << endl;
		cout << "Draw = " << tPlayer->getDraw() << endl;

		shared_ptr<Player> tOpponent = controller.getSuitablePlayer(tPlayer);
		cout << "* Matches for this player: " << endl;
		cout << "Name " << tOpponent->getName() << endl;
		cout << "Win = " << tOpponent->getWin() << endl;
		cout << "Lose = " << tOpponent->getLose() << endl;
		cout << "Draw = " << tOpponent->getDraw() << endl;
	}
	else
	{
		cout << "Player does not exist." << endl;
	}
}
void IO::exportAllPlayerInfo()
{
	SetConsoleTitle(L"Export all Player Info");
	fstream file;                      
	file.open("AllPlayerInfo.ini", ios::out);
	map<string, shared_ptr<Player>> tListPlayer = controller.getListPlayer();

	if (tListPlayer.size() == 0)
	{
		cout << "No player date yet." << endl;
	}
	else
	{
		file << "All player info: " << endl;
		int tcount = 1;
		for (auto i = tListPlayer.begin(); i != tListPlayer.end(); i++)
		{
			file << "* Player " << tcount << endl;
			file << "Name: " << i->second->getName() << endl;
			file << "Win = " << i->second->getWin() << endl;
			file << "Lose = " << i->second->getLose() << endl;
			file << "Draw = " << i->second->getDraw() << endl;
			tcount++;
		}
		cout << "Successfully exported all player information to AllPlayerInfo.ini" << endl;
	}
	file.close();
}
void IO::exportPlayerInfo()
{
	SetConsoleTitle(L"Export Player Info");
	fstream file;
	file.open("PlayerInfo.ini", ios::out);
	string Name;
	cout << "Enter player Name you want to export infomation: " << endl;
	getline(cin >> ws, Name);
	if (controller.checkExistName(Name))
	{
		file << "* Fouded player: " << endl;
		shared_ptr<Player> tPlayer = controller.getListPlayer().find(Name)->second;
		file << "Name " << tPlayer->getName() << endl;
		file << "Win = " << tPlayer->getWin() << endl;
		file << "Lose = " << tPlayer->getLose() << endl;
		file << "Draw = " << tPlayer->getDraw() << endl;

		shared_ptr<Player> tOpponent = controller.getSuitablePlayer(tPlayer);
		file << "* Matches for this player: " << endl;
		file << "Name " << tOpponent->getName() << endl;
		file << "Win = " << tOpponent->getWin() << endl;
		file << "Lose = " << tOpponent->getLose() << endl;
		file << "Draw = " << tOpponent->getDraw() << endl;

		cout << "Successfully exported player information to PlayerInfo.ini" << endl;
	}
	else
	{
		cout << "Player does not exist." << endl;
	}
	file.close();
}
void IO::replay()
{
	SetConsoleTitle(L"Export Player Info");
	int ID;
	cout << "Enter game ID: ";
	cin >> ID;
	if (!controller.checkExistIDGame(ID))
	{
		std::cout << "Game ID is not existed.";
	}
	else
	{
		system("cls");
		shared_ptr<GameProperties> tPlayedCaro = controller.getListGameCaro().find(ID)->second;
		int Size = tPlayedCaro->getSizeBoard();
		displayReplayBoard(Size, ID);
		vector<shared_ptr<Record>> tRecordPoint = tPlayedCaro->getPointRecord();
		for (auto i : tRecordPoint)
		{
			displayPointChecked(i->getRow(), i->getCol(), i->getChecked());
			Sleep(1000);
		}
		SettingWindow::textColor(0, 7);
		SettingWindow::gotoXY(0, 2 * Size + 5);
	}
	
}

int IO::inputValidNumber()
{
	int num;
	cin >> setw(1) >> num;

	while (!cin.good() || num < 0)
	{
		cout << "Faulty input!. You must enter a positive integer." << endl;

		cin.clear();
		cin.ignore(INT_MAX, '\n');

		cout << "Try again: " << endl;
		cin >> setw(1) >> num;
	}
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	return num;
}
int IO::inputValidIndex(int SizeBoard)
{
	int num;
	cin >> setw(1) >> num;

	while (!cin.good() || num < 0)
	{
		cout << "Faulty input!. You must enter a positive integer." << endl;

		cin.clear();
		cin.ignore(INT_MAX, '\n');

		cout << "Try again: " << endl;
		cin >> setw(1) >> num;
	}
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	while (num < 1 || num > SizeBoard)
	{
		cout << "Faulty input!. You must enter a number from 0 to " << SizeBoard << endl;
		cout << "Try again: " << endl;
		cin >> setw(1) >> num;
	}
	return num;
}
bool IO::checkPointInvalid(int Row, int Col, shared_ptr<GameProperties> GamePlaying)
{
	int SizeBoard = GamePlaying->getSizeBoard();
	vector<vector<char>> BoardCheck = GamePlaying->getPointOfBoard();
	if (Row < 2 ||Row > ((2*SizeBoard) + 2) || (Col > ((4*SizeBoard) - 1)))
	{
		return true;
	}
	else if ((Col + 1) % 4 == 0)
	{
		return true;
	}
	else if (BoardCheck[(Row - 2)/2][(Col + 1)/4] != ' ')
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool IO::checkInvalidPointFromKeyBoard(int Row, int Col, shared_ptr<GameProperties> GamePlaying)
{
	vector<vector<char>> BoardCheck = GamePlaying->getPointOfBoard();
	if (BoardCheck[Row - 1][Col - 1] != ' ')
	{
		return true;
	}
	return false;
}
void IO::changeTurn(char& Turn)
{
	if (Turn == 'X')
	{
		Turn = 'O';
	}
	else if (Turn == 'O')
	{
		Turn = 'X';
	}
}


void IO::displayBoard(int SizeBoard, string Name1, string Name2)
{
	SettingWindow::textColor(0, 10); //Green
	SettingWindow::gotoXY(0, 0);
	cout << "Player 1 <X>: " << Name1 << " - Player 2 <O>: " << Name2;
	for (int i = 2; i < (2 * SizeBoard + 2); i++)
	{
		for (int j = 0; j < 4 * SizeBoard - 1; j++)
		{
			SettingWindow::gotoXY(j, i);
			if (i % 2 == 0)
			{
				if ((j + 1) % 4 == 0)
				{
					cout << "|";
				}
				else
				{
					cout << " ";
				}
			}
			else
			{
				cout << "-";
			}
		}
	}
}
void IO::displayReplayBoard(int SizeBoard, int ID)
{
	SettingWindow::textColor(0, 10); //Green
	SettingWindow::gotoXY(0, 0);
	cout << "Replay Game Caro - ID: " << ID;
	for (int i = 2; i < (2 * SizeBoard + 2); i++)
	{
		for (int j = 0; j < 4 * SizeBoard - 1; j++)
		{
			SettingWindow::gotoXY(j, i);
			if (i % 2 == 0)
			{
				if ((j + 1) % 4 == 0)
				{
					cout << "|";
				}
				else
				{
					cout << " ";
				}
			}
			else
			{
				cout << "-";
			}
		}
	}
}
void IO::displayPointChecked(int Row, int Col, char TypeChecked)
{
	int posXChecked = 4 * Col + 1;
	int posYChecked = 2 * Row  + 2;
	if (TypeChecked == 'X')
	{
		SettingWindow::textColor(0, 12); // Red
		SettingWindow::gotoXY(posXChecked, posYChecked);
		cout << TypeChecked;
	}
	else if (TypeChecked == 'O')
	{
		SettingWindow::textColor(0, 11); // Aqua
		SettingWindow::gotoXY(posXChecked, posYChecked);
		cout << TypeChecked;
	}

}