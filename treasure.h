#ifndef TREASURE_H
#define TREASURE_H

#include <string>
#include <iostream>

#include "item.h"
using namespace std;

class Dragon;

class Treasure : public Item {
private:
	const string size;
	const int val;
public:
	Treasure(char s, string tp, int val, string size);
	virtual ~Treasure() = 0;

	int getValue();
	std::string getSize();
	virtual Dragon* getDragon();
	virtual void deleteDragon();
};

class NormalHoard : public Treasure {
public:
	NormalHoard();
	~NormalHoard();
};

class SmallHoard : public Treasure {
public:
	SmallHoard();
	~SmallHoard();
};

class MerchantHoard : public Treasure {
public:
	MerchantHoard();
	~MerchantHoard();
};

class DragonHoard : public Treasure {
private:
	Dragon* d;
public:
	DragonHoard();
	DragonHoard(Dragon* dragon);
	~DragonHoard();
	Dragon* getDragon();
	void deleteDragon();
	void setDragon(Dragon* drag);
};

#endif

