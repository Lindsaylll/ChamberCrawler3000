#ifndef _CHARACTER_H
#define _CHARACTER_H

#include <string>
#include <iostream>
#include "base.h"
using namespace std;

class Character : public Base
{

protected:
	int atk;
	int def;
	int hp;
	const string race;

public:
	Character(int Atk, int Def, int Hp, string race, char s, string t);

	virtual ~Character() = 0;

	virtual void setAtk(int n);

	virtual void setDef(int n);

	virtual void setHP(int n);

	virtual int getAtk();

	virtual int getDef();

	virtual int getHp();

	virtual string getRace();

	virtual void addhp(int n);

	virtual void buffAtk(int n);

	virtual void buffDef(int n);

	virtual string move(int d);

	virtual void damaged(int n);

	virtual string Damage(Character *defender);

	virtual void heal(int n);
};

#endif
