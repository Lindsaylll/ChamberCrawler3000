#ifndef _FLOOR_H
#define _FLOOR_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Posn;
class Player;
class Enemy;
class Base;
class Game;

class Floor
{
private:
	vector<vector<Posn>> theFloor;
	const int row;
	const int col;
	int level;
	Enemy *enemies[20];
	Player *player;
	Game *game;

public:
	Floor(int row, int column);

	~Floor();

	std::string playerAttack(std::string d);

	std::string consumePotion(std::string d);

	void generatePlayer();

	void generateStair();

	void generateEnemies();

	void generatePotions();

	void generateTreasures();

	void clearFloor();

	void setLevel(int n);

	int getLevel();

	Posn *getPosn(int row, int column);
	
	Enemy **getEnemies();

	void setPlayer(Player *p);

	Player *getPlayer();

	int getRow();

	int getColumn();

	void notify(int row, int column, char ch);

	void init(Game *cc);

	void initFloor();

	void nextfloor();
};

#endif

