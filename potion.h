#ifndef _POTION_H
#define _POTION_H

#include <string>
#include <iostream>

#include "item.h"
using namespace std;

class Potion : public Item {
private:
	string eff;
public:
	Potion(string eff);
	~Potion();
	string getEffect();
};

#endif
