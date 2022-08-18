#include <iostream>
#include <string>
#include <vector>

#include "textdisplay.h"

using namespace std;

TextDisplay::TextDisplay(int row, int column) : row(row), column(column)
{
	theDisplay.clear();
	for (int i = 0; i < row; ++i)
	{
		vector<char> vec;
		for (int j = 0; j < column; ++j)
		{
			vec.emplace_back(' ');
		}
		theDisplay.emplace_back(vec);
	}
}

TextDisplay::~TextDisplay()
{
	theDisplay.clear();
}

void TextDisplay::notify(int row, int column, char ch)
{
	theDisplay[row][column] = ch;
}

void TextDisplay::print(ostream &out)
{
	int i = 0;
	while(i < row)
	{
		int j = 0;
		while (j < column){
			out << theDisplay[i][j];
			j++;
		}
		out << endl;
		i++;
	}
}

