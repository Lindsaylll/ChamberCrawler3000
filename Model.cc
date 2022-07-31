#include "Model.h"
// #include "Player.h"

// #include 

Game::Game(){
    player = Player("shade", 125, 25, 25, 25);
}

Game::Game(string type){
    if(type == "shade"){
        auto shade = Shade();
        this->player = shade;
    }
    
}



