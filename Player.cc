#include "Player.h"
using namespace std;

Player::Player():Type{"shade"}, HP{125}, Atk{25}, Def{25}, maxHP{125}{}


Player::Player(string Type, int HP, int Atk, int Def, int maxHP):Type{Type}, HP{HP}, Atk{Atk}, Def{Def}, maxHP{maxHP}{}
// Player::~Player(){}
int Player:: getHP(){
    return HP;
}
int Player::getAtk(){
    return Atk;
}
int Player::getDef(){
    return Def;
}
int Player::getmaxHP(){
    return maxHP;
}
string Player::getType(){
    return Type;
}