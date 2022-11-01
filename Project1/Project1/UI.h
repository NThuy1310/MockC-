#pragma once
#include"IO.h"

enum MyChoice
{
	NEW_GAME = 1,
	FIND_PLAYER = 2,
	SHOW_ALL = 3,
	GUIDE = 4,
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