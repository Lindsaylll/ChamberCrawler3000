#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "base.h"
#include "posn.h"
#include "potion.h"
#include "stair.h"
#include "treasure.h"
#include "player.h"
#include "enemy.h"
#include "floor.h"
#include "game.h"

using namespace std;

bool samestr(string sa, string sb);

Floor::Floor(int row, int column) : row(row), col(column), level(0), player(nullptr),
									game(nullptr)
{
	for (int i = 0; i < 20; i++)
	{
		enemies[i] = nullptr;
	}
}

Floor::~Floor()
{
	clearFloor();
	theFloor.clear();
	delete player;
}

int destStrToInt(string s)
{ 
	int d = 0;
	if (samestr(s, "no"))
		d = 0;
	else if (samestr(s, "we"))
		d = 1;
	else if (samestr(s, "so"))
		d = 2;
	else if (samestr(s, "ea"))
		d = 3;
	else if (samestr(s, "nw"))
		d = 4;
	else if (samestr(s, "ne"))
		d = 5;
	else if (samestr(s, "sw"))
		d = 6;
	else if (samestr(s, "se"))
		d = 7;
	return d;
}

string Floor::playerAttack(string dir)
{								 
	int dest = destStrToInt(dir); 

	Base *cur = player->getpos()->getNber(dest)->getbase();

	string s;
	if (cur && samestr(cur->gettp(), "enemy"))
	{
		Enemy *e = dynamic_cast<Enemy *>(cur);
		s = player->Damage(e);
		if (samestr(e->getRace(), "Dragon") && e->getHp() == 0)
		{
			dynamic_cast<Dragon *>(e)->getHoard()->deleteDragon();
		}
	}
	else
	{
		s = "noenemy";
	}
	return s;
}

const int R_olayer = 5;
void Floor::generatePlayer()
{
	int cberidx = rand() % R_olayer + 1;
	Posn *posn;
	int i = 0;
	while (i != 5)
	{
		int c = rand() % col;
		int r = rand() % row;

		Posn *tmpPosn = getPosn(r, c);
		if (tmpPosn)
		{
			if ((cberidx == tmpPosn->getChamber()) && (tmpPosn->getCh() == '.'))
			{
				posn = tmpPosn;
				i = 5;
			}
		}
	}
	player->setpos(posn);
	posn->setbase(player);
}

string Floor::consumePotion(string dir)
{ 
	int dest = destStrToInt(dir);
	cout << "welcom consumePotion" << endl;
	Base *cur = player->getpos()->getNber(dest)->getbase();
	string s;

	if (cur && samestr(cur->gettp(), "potion"))
	{
		Potion *p = dynamic_cast<Potion *>(cur);
		if (samestr(p->getEffect(), "BD"))
		{
			int n = 5;
			if (!samestr(player->getRace(), "Drow"))
			{
				player->buffDef(n);
			}
			else
			{
				n *= 1.5;
				player->buffDef(n);
			}
			s = "PC uses BD. ";
		}

		if (samestr(p->getEffect(), "RH"))
		{
			int n = 10;
			if (!samestr(player->getRace(), "Drow"))
			{
				player->addhp(n);
			}
			else
			{
				n *= 1.5;
				player->addhp(n);
			}
			s = "PC uses RH. ";
		}
		if (samestr(p->getEffect(), "PH"))
		{ 
			int n = 10;
			if (!samestr(player->getRace(), "Drow"))
			{
				player->damaged(n);
			}
			else
			{
				n *= 1.5;
				player->damaged(n);
			}
			s = "PC uses PH. ";
		}

		if (samestr(p->getEffect(), "WA"))
		{
			int n = 5;
			if (!samestr(player->getRace(), "Drow"))
			{
				player->buffAtk(-n);
			}
			else
			{
				n *= 1.5;
				player->buffAtk(-n);
			}

			s = "PC uses WA. ";
		}

		if (samestr(p->getEffect(), "WD"))
		{
			int n = 5;
			if (!samestr(player->getRace(), "Drow"))
			{
				player->buffDef(-n);
			}
			else
			{
				n *= 1.5;
				player->buffDef(-n);
			}

			s = "PC uses WD. ";
		}

		if (samestr(p->getEffect(), "BA"))
		{
			int n = 5;
			if (!samestr(player->getRace(), "Drow"))
			{
				player->buffAtk(n);
			}
			else
			{
				n *= 1.5;
				player->buffAtk(n);
			}
			s = "PC uses BA. ";
		}
		p->getpos()->setbase(nullptr);
		delete p;
		return s;
	}
	else
	{
		s = "NO POTION HERE. ";
		return s;
	}
}

void Floor::generateStair()
{
	int r;
	int c;
	Posn *posn;
	int i = 0;
	while (i != 5)
	{
		c = rand() % col;
		r = rand() % row;

		Posn *tmpPosn = getPosn(r, c);
		if (tmpPosn)
		{
			if ((tmpPosn->getChamber() != player->getpos()->getChamber()) && (tmpPosn->getCh() == '.'))
			{
				i = 5;
				posn = tmpPosn;
			}
		}
	}
	Stair *tmps = new Stair();
	tmps->setpos(posn);
	posn->setbase(tmps);
}

bool isnull(Base *ba);
bool samechar(char ca, char cb);
bool smaller(int i , int k){
	return i < k;
}
const int R_Enemy = 18;
void Floor::generateEnemies()
{
	int i = 0;
	while(i < 20)
	{
		int r;
		int c;
		int poss = rand() % R_Enemy;
		Posn *posn;
		Enemy *ee = nullptr;

		int n = 0;
		while (n != 2)
		{
			c = rand() % col;
			r = rand() % row;

			Posn *temp = getPosn(r, c);
			if (temp && samechar(temp->getCh(), '.') && isnull(temp->getbase()))
			{
				n = 2;
				posn = temp;
			}
		}
		if (smaller(poss,4))
		{
			ee = new Human();
		}
		else if (smaller(poss,7))
		{
			ee = new Dwarf();
		}
		else if (smaller(poss,12))
		{
			ee = new Halfling();
		}
		else if (smaller(poss,14))
		{
			ee = new Elf();
		}
		else if (smaller(poss,16))
		{
			ee = new Orc();
		}
		else if (smaller(poss,18))
		{
			ee = new Merchant();
		}
		enemies[i] = ee;
		++i;
		posn->setbase(ee);
		ee->setpos(posn);
	}
}
const int R_Potions = 6;
void Floor::generatePotions()
{
	int i = 0;
	while(i < 10)
	{
		int r;
		int c;
		int poss = rand() % R_Potions;
		Posn *posn;
		Potion *pp = nullptr;
		int n = 0;
		while (n != 2)
		{
			r = rand() % row;
			c = rand() % col;
			Posn *tmpPosn = getPosn(r, c);
			if (tmpPosn)
			{
				if (tmpPosn && tmpPosn->getCh() == '.' && !tmpPosn->getbase())
				{
					n = 2;
					posn = tmpPosn;
				}
			}
		}

		if (smaller(poss,1))
		{
			pp = new Potion("BA");
		}
		else if (smaller(poss,2))
		{
			pp = new Potion("BD");
		}
		else if (smaller(poss,3))
		{
			pp = new Potion("PH");
		}
		else if (smaller(poss,4))
		{
			pp = new Potion("RH");
		}
		else if (smaller(poss,5))
		{
			pp = new Potion("WA");
		}
		else if (smaller(poss, 6))
		{
			pp = new Potion("WD");
		}
		pp->setpos(posn);
		posn->setbase(pp);
		++i;
	}
}
const int R_Treasure = 8;
void Floor::generateTreasures()
{
	//for (int i = 0; i < 10; i++)
	int i = 0;
	while (i < 10)
	{
		Treasure *treasure = nullptr;
		Posn *posn;

		int r;
		int c;
		int poss = rand() % R_Treasure;

		int n = 0;
		while (n != 2)
		{
			c = rand() % col;
			r = rand() % row;

			Posn *tmpPosn = getPosn(r, c);
			if (tmpPosn)
			{
				if (!tmpPosn->getbase())
				{
					if (samechar(tmpPosn->getCh(), '.'))
					{
						n = 2;
						posn = tmpPosn;
					}
				}
			}
		}

		if (smaller(poss,5))
		{
			treasure = new NormalHoard();
		}
		else if (smaller(poss,7))
		{
			treasure = new SmallHoard();
		}
		else 
		{
			treasure = new DragonHoard();
			Dragon *dd = treasure->getDragon();
			Posn *finalpos;

			int idx;
			int j = 0;
			while (j != 2)
			{
				finalpos = posn->getNber(idx);
				idx = rand() % 8;
				if (finalpos)
				{
					if ((!finalpos->getbase()) && (samechar(finalpos->getCh(), '.')))
					{
						j = 2;
						dd->setpos(finalpos);
						finalpos->setbase(dd);
					}
				}
			}
		}
		treasure->setpos(posn);
		posn->setbase(treasure);
		++i;
	}
}

void Floor::clearFloor()
{
	if (player != nullptr)
	{
		//player = player->getPlayer();
		//Posn* pos= player->getPosition();
		if (player->getpos())
		{
			player->getpos()->setbase(nullptr);
		}
		player->setpos(nullptr);
	}
	if (theFloor.size() != 0)
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (theFloor[i][j].getbase() && (samechar(theFloor[i][j].getbase()->getsym(), 'D')))
				{
					continue;
				}
				delete theFloor[i][j].getbase();
				theFloor[i][j].setbase(nullptr);
			}
		}
	}
	int i = 0;
	while(i < 20){
		enemies[i] = nullptr;
		++i;
	}
}

void Floor::setLevel(int n)
{
	this->level = n;
}

int Floor::getLevel()
{
	return this->level;
}

Posn *Floor::getPosn(int row, int column)
{
	Posn *p = &(theFloor[row][column]);
	return p;
}

Enemy **Floor::getEnemies()
{
	return this->enemies;
}

void Floor::setPlayer(Player *p)
{
	player = p;
}

Player *Floor::getPlayer()
{
	return this->player;
}

int Floor::getRow()
{
	return this->row;
}

int Floor::getColumn()
{
	return this->col;
}
bool chOne(int c, int r)
{
	return (c > 2 && c < 29 && r > 2 && r < 7);
}
bool chTwo(int c, int r)
{
	return (c > 3 && c < 25 && r > 14 && r < 22);
}
bool chThree(int c, int r)
{
	return (c > 37 && c < 51 && r > 9 && r < 13);
}

bool chFour(int c, int r)
{
	return (((c > 36 && c < 76) && (r > 18 && r < 22)) || ((c > 64 && c < 76) && (r > 15 && r < 19)));
}
bool chFive(int c, int r)
{
	return ((c > 38 && c < 62 && r > 2 && r < 7) ||(c > 60 && c < 76 && r > 6 && r < 14) ||
			(c > 61 && c < 70 && r == 5) ||(c > 61 && c < 73 && r == 6));
}
int findChamber(int c, int r)
{
	if (chOne(c, r))
	{
		return 1;
	}
	if (chTwo(c, r))
	{
		return 2;
	}
	if (chThree(c, r))
	{
		return 3;
	}
	if (chFour(c, r))
	{
		return 4;
	}
	if (chFive(c, r))
	{
		return 5;
	}
	else
	{
		return 0;
	}
}

void Floor::notify(int r, int c, char sign)
{
	game->notify(r, c, sign); 
}


void Floor::init(Game *cc)
{
	clearFloor();
	delete player;
	game = cc;
	for (int i = 0; i < row; i++)
	{
		vector<Posn> p;
		for (int j = 0; j < col; j++)
		{
			Posn tmpposn;
			p.emplace_back(tmpposn);
		}
		theFloor.emplace_back(p);
	}
	fstream fs("floor.txt");
	char c;
	int i = 0;
	while(i < row)
	{ 
		int j = 0;
		while(j < col)
		{
			fs >> noskipws >> c;
			theFloor[i][j].setPosn(i, j, c, findChamber(j, i), this);
			theFloor[i][j].setNbers();
			j++;
		}
		i++;
		fs.get();
	}
	fs.close();
}
void Floor::initFloor()
{
	level++;
	clearFloor();
	generatePlayer();
	generateStair();
	generatePotions();
	generateTreasures();
	generateEnemies();
}

void Floor::nextfloor()
{
	level++;
	clearFloor();
	generatePlayer();
	generateStair();
	generatePotions();
	generateTreasures();
	generateEnemies();
	if (samestr(player->getRace(), "Shade"))
	{
		player->setAtk(25);
		player->setDef(25);
	}
	if (samestr(player->getRace(), "Drow"))
	{
		player->setAtk(25);
		player->setDef(15);
	}
	if (samestr(player->getRace(), "Vampire"))
	{
		player->setAtk(25);
		player->setDef(25);
	}
	if (samestr(player->getRace(), "Troll"))
	{
		player->setAtk(25);
		player->setDef(15);
	}
	if (samestr(player->getRace(), "Goblin"))
	{
		player->setAtk(15);
		player->setDef(20);
	}
}

