#include"UI.h"

UI::UI()
{
	int chose = 0;
	while (run)
	{
		system("cls");
		cout << "1. New game" << endl;
		cout << "2. Find Player" << endl;
		cout << "3. Show all Player information" << endl;
		cout << "4. Caro guide." << endl;
		cout << "0. Exit." << endl;

		cout << "Enter your choice: " << endl;
		cin >> setw(1) >> chose;

		while (!cin.good())
		{
			cout << "Faulty input! Try again.." << endl;

			cin.clear();
			cin.ignore(INT_MAX, '\n');

			cout << "Enter your choice: " << endl;
			cin >> setw(1) >> chose;

		}
		cin.clear();
		cin.ignore(INT_MAX, '\n');

		switch (chose)
		{
		case NEW_GAME:
		{
			system("cls");
			view.newGame();
			system("pause");

			break;
		}
		case FIND_PLAYER:
		{
			system("cls");
			view.showPlayerInfo();
			system("pause");
			break;
		}
		case SHOW_ALL:
		{
			system("cls");
			view.showAllPlayer();
			system("pause");
			break;
		}
		case GUIDE:
		{
			system("cls");
			view.guide();
			system("pause");
			break;
		}
		case EXIT:
		{
			run = 0;
			break;
		}
		default:
		{
			cout << "Incorrect function selection. Please choose again..." << endl;
			break;
		}
		}
	}
}

UI::~UI()
{
	//
}