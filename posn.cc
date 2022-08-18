#include <iostream>
#include <vector>
#include <string>

#include "posn.h"
#include "base.h"


using namespace std;

Posn::Posn()
{
	row = 0;
	col = 0;
	ch = '0';
	chamber = 0;
	floor = nullptr;
	base = nullptr;
	neighbours.resize(20);
	int i = 0;
	while(i < 8){
		neighbours[i] = nullptr;
		++i;
	}
}

Posn::~Posn() {}

void Posn::setPosn(int x, int y, char c, int cb, Floor *f)
{
	row = x;
	col = y;
	ch = c;
	chamber = cb;
	floor = f;
	notify(row, col, ch);
}

Base *Posn::getbase()
{
	return base;
}

int Posn::getRow()
{
	return row;
}

int Posn::getCol()
{
	return col;
}

char Posn::getCh()
{
	return ch;
}

int Posn::getChamber()
{
	return chamber;
}

Posn *Posn::getNber(int n)
{
	return neighbours[n];
}

vector<Posn *> Posn::getNbers()
{
	return neighbours;
}

void Posn::setbase(Base *obj)
{
	base = obj;
	if (base != nullptr){
		notify(row, col, base->getsym());
	}else {
		notify(row, col, ch);
	}
}

void Posn::setNbers()
{
	if (!(row <= 0 || row >= 24 || col <= 0 || col >= 79))
	{
		int x;
		int y;
		for(int i = 0; i < 8; i++){
			if (i == 0){
				x = row - 1;
				y = col;
			}else if (i == 1){
				x = row;
				y = col - 1;
			}else if (i == 2){
				x = row + 1;
				y = col;
			}else if (i == 3){
				x = row;
				y = col+1;
			}else if (i == 4){
				x = row-1;
				y = col-1;
			}else if (i == 5){
				x = row-1;
				y = col+1;
			}else if (i == 6){
				x = row + 1;
				y = col - 1;
			}else{
				x = row + 1;
				y = col + 1;
			}
			neighbours[i] = floor->getPosn(x, y);
		}
	}
}

void Posn::notify(int row, int column, char ch)
{
	floor->notify(row, column, ch);
}

