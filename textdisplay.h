#ifndef _TEXTDISPLAY_H
#define _TEXTDISPLAY_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;
class TextDisplay {
private:
	vector<vector<char>> theDisplay;

public:
	int const row;
	int const column;

	TextDisplay(int row, int column);

	~TextDisplay();

	void notify(int row, int column, char ch);

	void print(std::ostream& out);

};

#endif 

