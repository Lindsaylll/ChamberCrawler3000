#include <iostream>

#include "character.h"
#include "posn.h"
#include "treasure.h"
#include "enemy.h"

using namespace std;

bool samechar(char c1, char c2);
Enemy::Enemy(int a, int d, int hp, string r, char s, string tp)
	: Character(a, d, hp, r, s, tp), isactive(false) {}

Enemy::~Enemy() {}

bool Enemy::isActive()
{
	return this->isactive;
}

void Enemy::activate()
{
	this->isactive = true;
}

void Enemy::inactivate()
{
	this->isactive = false;
}

void Enemy::dropgold()
{
	int poss = rand() % 2;
	Treasure *tt = nullptr;
	if (poss == 0)
	{
		tt = new NormalHoard();
	}
	if (poss == 1)
	{
		tt = new SmallHoard();
	}
	tt->setpos(p);
	p->setbase(tt);
}
const char c_h = 'H';

Human::Human() : Enemy(20, 20, 140, "Human", c_h, "enemy") {}

Human::~Human() {}

void Human::dropGold()
{
	Treasure *tt = new NormalHoard();
	Treasure *ts = new NormalHoard();

	tt->setpos(p);
	p->setbase(tt);
	int i = 0;
	while (i < 8)
	{
		Posn *des = p->getNber(i);
		if (des)
		{

			if (samechar(des->getCh(), '.') && !des->getbase())
			{
				ts->setpos(des);
				des->setbase(ts);
			}
		}
		++i;
	}
	delete ts;
}
const char c_w = 'W';
Dwarf::Dwarf() : Enemy(20, 30, 100, "Dwarf", c_w, "enemy") {}

Dwarf::~Dwarf() {}
const char c_e = 'E';
Elf::Elf() : Enemy(30, 10, 140, "Elf", c_e, "enemy") {}

Elf::~Elf() {}
const char c_o = 'O';
Orc::Orc() : Enemy(30, 25, 180, "Orc", c_o, "enemy") {}

Orc::~Orc() {}

bool Merchant::hostile = false;
const char c_m = 'M';
Merchant::Merchant() : Enemy(70, 5, 30, "Merchant", c_m, "enemy") {}

Merchant::~Merchant() {}

void Merchant::dropGold()
{
	MerchantHoard *tt = new MerchantHoard();
	tt->setpos(p);
	p->setbase(tt);
}
const char c_ha= 'L';
Halfling::Halfling() : Enemy(15, 20, 100, "Halfling", c_ha, "enemy") {}

Halfling::~Halfling() {}
const char c_d = 'D';
Dragon::Dragon() : Enemy(20, 20, 150, "Dragon", c_d, "enemy"), hoard(nullptr) {}

Dragon::Dragon(DragonHoard *hoard) : Enemy(20, 20, 150, "Dragon", c_d, "enemy"), hoard(hoard) {}

Dragon::~Dragon() {}

void Dragon::dropGold()
{
}

DragonHoard *Dragon::getHoard()
{
	return this->hoard;
}

void Dragon::setHoard(DragonHoard *hd)
{
	this->hoard = hd;
}

