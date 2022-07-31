#include <iostream>

#include "Model.h"

using namespace std;

int main(){
    cout << "You are goint to enter the game." << endl;
    cout << "Please choose your role; enter: \n 's' for shade(125 HP, 25 Atk, 25 Def); \n'd' for drow(150 HP, 25 Atk , 15 Def, all potions have their effect magnified by 1.5); \n 'v' for vampire(50 HP, 25 Atk, 25 Def, gains 5 HP every successful attack and has no maximum HP); \n't' for troll(120 HP, 25 Atk, 15 Def, regains 5 HP every turn; HP is capped at 120 HP);\n'g' for goblin(110 HP, 15 Atk, 20 Def, steals 5 gold from every slain enemy)" << endl;
    string player_tp;
    // shade (125 HP, 25 Atk, 25 Def).
    // drow (150 HP, 25 Atk , 15 Def, all potions have their effect magnified by 1.5)
    // vampire (50 HP, 25 Atk, 25 Def, gains 5 HP every successful attack and has no maximum HP), 
    // troll (120 HP, 25 Atk, 15 Def, regains 5 HP every turn; HP is capped at 120 HP), 
    //  goblin (110 HP, 15 Atk, 20 Def, steals 5 gold from every slain enemy)
    // all have limit HP = start except for vampire
    cin >> player_tp;

    while(true){
        if(player_tp == "s"){
            cout << "shade" << endl;
            

            break;
        }
        if(player_tp == "d"){
            // cout << "drow" << endl;
            break;
        }
        if(player_tp == "v"){
            // cout << "vampire" << endl;
            break;
        }
        if(player_tp == "t"){
            // cout << "troll" << endl;
            break;
        }
        if(player_tp == "g"){
            // cout << "goblin" << endl;

            break;
        }
        cout << "non-valid type" << endl;
        cout << "Please choose your role; enter: \n \t's' for shade(125 HP, 25 Atk, 25 Def); \n \t'd' for drow(150 HP, 25 Atk , 15 Def, all potions have their effect magnified by 1.5); \n \t'v' for vampire(50 HP, 25 Atk, 25 Def, gains 5 HP every successful attack and has no maximum HP); \n\t't' for troll(120 HP, 25 Atk, 15 Def, regains 5 HP every turn; HP is capped at 120 HP);\n\t'g' for goblin(110 HP, 15 Atk, 20 Def, steals 5 gold from every slain enemy)." << endl;
        cin >> player_tp;
        continue;
    }


}