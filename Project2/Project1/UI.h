#pragma once
#include"IO.h"

enum MyChoice
{
	NEW_GAME = 1,
	FIND_PLAYER = 2,
	FIND_OPPONENT = 3,
	SHOW_ALL = 4,
	EXPORT_PLAYER = 5,
	EXPORT_ALL = 6,
	GUIDE = 7,
	EXIT = 0
};

class UI
{
private:
	bool run = true;
	IO view;
public:
	UI();
	~UI();
};