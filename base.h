#ifndef _BASE_H
#define _BASE_H

#include <string>
using namespace std;

class Posn;

class Base {

protected:
	const char sym;
	const string tp;
	Posn* p;

public:

	Base(char symbol, string type);

	virtual ~Base() = 0;

	virtual string getrace();

	virtual char getsym();

	virtual string gettp();

	virtual Posn* getpos();

	virtual void setpos(Posn* p);
};

#endif 

