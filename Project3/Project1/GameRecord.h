#pragma once
#include<string>

class Record
{
private:
	int Row;
	int Col;
	char Checked;
public:
	Record();
	Record(int, int, char);
	~Record();

	void setRow(int);
	void setCol(int);
	void setChecked(char);

	int getRow();
	int getCol();
	char getChecked();
};