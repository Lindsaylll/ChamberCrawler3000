#include <iostream>
#include <string>
#include <fstream>

#include "game.h"

using namespace std;

int main(int argc, char *argv[])
{
	Game c;
	c.init();
	cout << "welcome to new game" << endl;
	c.newGame();
}
