#include <string>
#include <iostream>

#include "posn.h"
#include "enemy.h"
#include "treasure.h"

using namespace std;

Treasure::Treasure(char symbol, string type, int val, string size) : Item(symbol, type), size(size), val(val) {}

Treasure::~Treasure() {}

int Treasure::getValue()
{
	return this->val;
}

string Treasure::getSize()
{
	return this->size;
}

Dragon *Treasure::getDragon()
{
	return nullptr;
}

void Treasure::deleteDragon()
{
}
const char c = 'G';
NormalHoard::NormalHoard() : Treasure(c, "treasure", 2, "Normal") {}

NormalHoard::~NormalHoard() {}

SmallHoard::SmallHoard() : Treasure(c, "treasure", 1, "Small") {}

SmallHoard::~SmallHoard() {}

MerchantHoard::MerchantHoard() : Treasure(c, "treasure", 4, "Merchant") {}

MerchantHoard::~MerchantHoard() {}

DragonHoard::DragonHoard() : Treasure(c, "treasure", 6, "Dragon")
{
	d = new Dragon(this);
}

DragonHoard::DragonHoard(Dragon *drag) : Treasure(c, "treasure", 6, "Dragon"), d(drag) {}

DragonHoard::~DragonHoard()
{
	if (d != nullptr)
	{

		if (d->getpos())
		{
			d->getpos()->setbase(nullptr);
		}
	}
	delete d;
}

Dragon *DragonHoard::getDragon()
{
	return d;
}

void DragonHoard::deleteDragon()
{
	d->getpos()->setbase(nullptr);
	delete d;
	d = nullptr;
}

void DragonHoard::setDragon(Dragon *drag)
{
	d = drag;
}

