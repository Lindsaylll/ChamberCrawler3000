#include <iostream>

#include "base.h"
#include "posn.h"

using namespace std;

Base::Base(char s, string type) : sym(s), tp(type)
{
    this->p = nullptr;
}

Base::~Base() {}

string Base::getrace()
{
    return "";
}

char Base::getsym()
{
    return this->sym;
}

string Base::gettp()
{
    return this->tp;
}

Posn *Base::getpos()
{
    return this->p;
}

void Base::setpos(Posn *pos)
{
    this->p = pos;
}

