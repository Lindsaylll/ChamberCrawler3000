#ifndef _GAME_H
#define _GAME_H
#include <iostream>
#include <string>


class Floor;
class TextDisplay;

class Game {
	Floor* floor;
	TextDisplay* td;

public:

	Game();

	~Game();

	void notify(int row, int column, char ch);

	void printStat(std::string message);

	void createPC();

	void init();

	void newGame();

	void newFloor();

	void newFloor(std::string loaded);

	void play(std::string msg, std::string loaded);

};

#endif 

