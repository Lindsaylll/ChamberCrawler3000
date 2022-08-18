#ifndef _ITEM_H
#define _ITEM_H

#include <string>
#include <iostream>

#include "base.h"

using namespace std;

class Item : public Base
{
public:
	Item(char symbol, string type);

	~Item();
};

#endif
