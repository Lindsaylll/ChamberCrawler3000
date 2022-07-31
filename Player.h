#ifndef Player_h
#define Player_h

#include <string>
using namespace std;


class Player{
    string Type;
    int HP;
    int Atk;
    int Def;
    int maxHP;
public:
    Player();
    Player(string Type, int HP,int Atk,int Def, int maxHP);
    // virtual ~Player() = 0;
    int getHP();
    int getAtk();
    int getDef(); 
    int getmaxHP();
    string getType();
};






#endif