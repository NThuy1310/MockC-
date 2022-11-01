#include"GameRecord.h"

Record::Record()
{
	//
}
Record::Record(int Row, int Col, char Checked)
{
	this->Row = Row;
	this->Col = Col;
	this->Checked = Checked;
}
Record::~Record()
{
	//
}

void Record::setRow(int Row)
{
	this->Row = Row;
}
void Record::setCol(int Col)
{
	this->Col = Col;
}
void Record::setChecked(char Checked)
{
	this->Checked = Checked;
}

int Record::getRow()
{
	return Row;
}
int Record::getCol()
{
	return Col;
}
char Record::getChecked()
{
	return Checked;
}