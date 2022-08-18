#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <sstream>
#include "treasure.h"
#include "player.h"
#include "posn.h"
#include "enemy.h"
#include "character.h"

using namespace std;

bool samestr(string sa, string sb);
bool samechar(char ca, char cb);

Character::Character(int a, int d, int Hp, string r, char s, string t) : Base(s, t), atk(a), def(d), hp(Hp), race(r)
{
}

Character::~Character() {}

void Character::setAtk(int n)
{
    this->atk = n;
}

void Character::setDef(int n)
{
    this->def = n;
}

void Character::setHP(int n)
{
    this->hp = n;
}

int Character::getAtk()
{
    return this->atk;
}

int Character::getDef()
{
    return this->def;
}

int Character::getHp()
{
    return this->hp;
}

string Character::getRace()
{
    return this->race;
}
void Character::addhp(int n)
{
}

void Character::buffAtk(int n)
{
    this->atk += n;
}

void Character::buffDef(int n)
{
    this->def += n;
}
bool isnull(Base *ba)
{
    bool signal = (ba == nullptr);
    return signal;
}

bool samestr(string s1, string s2)
{
    return s1 == s2;
}

bool samechar(char c1, char c2)
{
    return c1 == c2;
}

string findrace(Base *bb)
{
    char cc = bb->getsym();
    if (samechar(cc, 'H'))
    {
        return "HUMAN";
    }
    if (samechar(cc, 'W'))
    {
        return "DWARF";
    }
    if (samechar(cc, 'E'))
    {
        return "ELF";
    }
    if (samechar(cc, 'O'))
    {
        return "ORC";
    }
    if (samechar(cc, 'M'))
    {
        return "MERCHANT";
    }
    if (samechar(cc, 'L'))
    {
        return "HALFING";
    }
    if (samechar(cc, 'D'))
    {
        return "DRAGON";
    }
    return "SOMETHING";
}

string Character::move(int d)
{
    Posn *curr = p;
    Posn *dest = p->getNber(d);
    char destCh = dest->getCh();

    Base *destObj = dest->getbase();
    string s;

    if ((!samestr(tp, "player")) && (!samechar(destCh, '.') || (!isnull(destObj))))
    {
        s = "nomove";
        return s;
    }
    else if (samestr(tp, "player") && ((samechar(destCh, '-')) || (samechar(destCh, '|')) || (samechar(destCh, ' '))))
    {
        s = "You can't move to ";
        return s;
    }
    else if ((!isnull(destObj)) && samestr(destObj->gettp(), "stair"))
    {
        s = "nextFloor";
        return s;
    }
    else if ((!isnull(destObj)) && samestr(destObj->gettp(), "potion"))
    {
        s = "You cant't move to there. There is a mysterious potion on ";
        return s;
    }
    else if ((!isnull(destObj)) && samestr(destObj->gettp(), "treasure"))
    {
        if (dynamic_cast<Treasure *>(destObj)->getDragon())
        {
            s = "A dragon is guarding its hoard. You can't take the treasure on ";
            return s;
        }
        else
        {
            Player *player = dynamic_cast<Player *>(this);
            int value = dynamic_cast<Treasure *>(destObj)->getValue();
            player->addgold(value);
            stringstream ss;
            ss << value;
            s = ss.str();
            delete destObj;
        }
    }
    else if (!isnull(destObj))
    {
        string tmp = findrace(destObj);
        s = "A " + tmp + " blocked the way. You can't move to ";
        return s;
    }
    else if (samestr(tp, "player"))
    {
        s = "You moved to ";
    }

    dest->setbase(this);
    setpos(dest);
    curr->setbase(nullptr);
    return s;
}

void Character::damaged(int n)
{

    int tmp = this->hp;
    tmp -= n;

    if (tmp < 0)
    {
        tmp = 0;
    }
    this->hp = tmp;
}

string Character::Damage(Character *defender)
{
    string updRc, upgive, uprecv;
    string aTp = gettp();
    string dTp = defender->gettp();
    string aRc = getRace();
    string dRc = defender->getRace();
    string give;
    string recv;
    if (samestr(aTp, "player"))
    {
        give = "player";
        recv = dRc;
    }
    else
    {
        give = aRc;
        recv = "player";
    }

    string s;

    bool cmplt = false;

    double Atk = getAtk();
    double Def = defender->getDef();

    int realdmg = ceil((100 / (100 + Def)) * Atk);

    int hp;

firststage:
    int dmg = realdmg;
    if (samestr(dRc, "Halfling") || samestr(dTp, "player"))
    {
        int poss = rand() % 2;
        if (poss < 1)
        {
            upgive.resize(give.size());
            uprecv.resize(recv.size());

            transform(give.begin(), give.end(), upgive.begin(), ::toupper);
            transform(recv.begin(), recv.end(), uprecv.begin(), ::toupper);
            // generate miss attack message
            s += upgive + " ATTACKED " + uprecv + " BUT MISSED. ";
            goto secondstage;
        }
    }
    if (samestr(aRc, "Orc") && samestr(dRc, "Goblin"))
    {

        dmg = ceil(dmg * 1.5);
    }


    defender->damaged(dmg);

    hp = defender->getHp();

    upgive.resize(give.size());
    uprecv.resize(recv.size());

    transform(give.begin(), give.end(), upgive.begin(), ::toupper);
    transform(recv.begin(), recv.end(), uprecv.begin(), ::toupper);
    s = s = upgive + " ATTACKED " + uprecv + ", DELT " + to_string(dmg) + " DAMAGE. ";
    if (hp <= 0)
    {
        s += uprecv + " IS " + "DEAD. ";
    }
    if (samestr(aRc, "Vampire"))
    {
        if (samestr(dRc, "Dwarf"))
        {
            damaged(5);
            s += "IT IS DWARF, YOU LOSE 5 HP. ";
        }
        else
        {
            heal(5);
            updRc.resize(dRc.size());

            transform(dRc.begin(), dRc.end(), updRc.begin(), ::toupper);
            s += "GAINS 5 HP FROM " + updRc + ". ";
        }
    }

    if (samestr(dRc, "Merchant"))
    {
        Merchant::hostile = true;
    }

secondstage:
    if (samestr(aRc, "Elf") && !samestr(dRc, "Drow") && !cmplt)
    {
        cmplt = true;
        goto firststage;
    }

    return s;
}

void Character::heal(int n)
{
    addhp(n);
}

