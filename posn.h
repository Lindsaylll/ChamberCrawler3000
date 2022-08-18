#ifndef _POSN_H
#define _POSN_H

#include <vector>
#include <string>
#include <iostream>

#include "floor.h"
using namespace std;

class Base;
class Floor;

class Posn {
	int row;
	int col;
	char ch;
	int chamber;
	Floor* floor;
	Base* base;
	vector<Posn *> neighbours;

public:
	Posn();

	~Posn();

	Base* getbase();

	int getRow();

	int getCol();

	char getCh();

	int getChamber();

	Posn* getNber(int n);

	vector<Posn *> getNbers();

	void setPosn(int x, int y, char c, int cb, Floor* g);

	void setbase(Base* obj);

	void setNbers();

	void notify(int row, int column, char ch);

};

#endif 

