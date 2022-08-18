#include <string>
#include <iostream>

#include "potion.h"

using namespace std;
const char c = 'P';
const string s = "potion";
Potion::Potion(string e) : Item(c, s), eff(e) {}

Potion::~Potion() {}

string Potion::getEffect() {
	return this->eff;
}

