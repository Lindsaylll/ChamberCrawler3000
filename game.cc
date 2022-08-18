#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <algorithm>

#include "posn.h"
#include "player.h"
#include "treasure.h"
#include "enemy.h"
#include "game.h"
#include "floor.h"
#include "textdisplay.h"


using namespace std;

bool samestr(string sa, string sb);
bool samechar(char ca, char cb);

Game::Game()
{
    floor = new Floor(25, 79);
    td = new TextDisplay(25, 79);
}

Game::~Game()
{
    delete floor;
    delete td;
}

void Game::notify(int row, int column, char ch)
{
    td->notify(row, column, ch);
}

void state(Player *p, string m, string ss)
{
    string M;
    if (samestr(p->getRace(), "Vampire"))
    {
        M = "???";
    }
    else
    {
        M = to_string(p->getMaxHp());
    }
    cout << setw(50) << left << "Race: " + p->getRace() + "   Gold: " + to_string(p->getgold()) << "Floor: " + ss << endl;
    cout << "HP: " << p->getHp() << "/" << M << endl;
    cout << "Atk: " << to_string(p->getAtk()) << endl;
    cout << "Def: " << to_string(p->getDef()) << endl;
    cout << "Action: " + m << endl;
}
void Game::printStat(string m)
{
    Player *player = floor->getPlayer();
    string s = to_string(floor->getLevel());


    if (player != nullptr)
    {
        state(player, m, s);
    }
    else
    {

        // print state
        cout << setw(50) << left << "Race: N/A   Gold: 0"
             << "Floor: " + s << endl;
        cout << "HP: 0/0" << endl;
        cout << "Atk: 0" << endl;
        cout << "Def: 0" << endl;
        cout << "Action: " + m << endl;
    }
}
bool samestr(string sa, string sb);
bool samechar(char ca, char cb);

void Game::init()
{
    floor->init(this);
}
bool IsShade(char c)
{
    return c == 's';
}
bool IsDrow(char c)
{
    return c == 'd';
}
bool IsVam(char c)
{
    return c == 'v';
}
bool Istroll(char c)
{
    return c == 't';
}
bool Isgoblin(char c)
{
    return c == 'g';
}
void Game::createPC()
{
    td->print(cout);
    printStat("");

    delete floor->getPlayer();

    while (true)
    {
        cout << "Choose your race: (s)hade, (d)row, (v)ampire, (t)roll, (g)oblin" << endl;
        char c;
        cin >> c;
        Player *p = nullptr;
        if (cin.eof())
        {
            exit(0);
        }
        if (IsShade(c))
        {
            p = new Shade();
            floor->setPlayer(p);
            break;
        }
        else if (IsDrow(c))
        {
            p = new Drow();
            floor->setPlayer(p);
            break;
        }
        else if (IsVam(c))
        {
            p = new Vampire();
            floor->setPlayer(p);
            break;
        }
        else if (Istroll(c))
        {
            p = new Troll();
            floor->setPlayer(p);
            break;
        }
        else if (Isgoblin(c))
        {
            p = new Goblin();
            floor->setPlayer(p);
            break;
        }
        else
        {
            cout << "Invalid input!" << endl;
            continue;
        }
    }
}


void Game::newGame()
{
    Merchant::hostile = false;
    floor->clearFloor();
    createPC();
    floor->setLevel(0);
    floor->initFloor();
    play("", "");
}

void Game::newFloor()
{
    floor->nextfloor();
}


bool Isyes(string c)
{
    return c == "y";
}
bool actone(string s)
{
    return s == "q";
}
bool acttwo(string s)
{
    return s == "r";
}
bool actthree(string s)
{
    return (s == "nw" || s == "no" || s == "ne" || s == "we" || s == "ea" || s == "sw" || s == "so" || s == "se");
}
bool actfour(string s)
{
    return s == "a";
}
bool actfive(string s)
{
    return s == "u";
}

void Game::play(string m, string loaded)
{
    string mes = m;
    bool Isdead = false;

    while (true)
    {
        bool atk = false;
        Player *player = floor->getPlayer();
        td->print(cout);
        printStat(mes);
        mes = "";

        if (Isdead)
        {
            Isdead = false;
            cout << "You are Dead! new game? [y/n]" << endl;
            string str;
            cin >> str;
            if (Isyes(str))
            {
                newGame();
                delete player;
                break;
            }
            else
            {
                floor->clearFloor();
                delete player;
                break;
            }
        }

    // cmd__:
        string com;

        cin >> com;

        if (cin.eof() || actone(com))
        {
            break;
        }
        else if (acttwo(com))
        {
            newGame();
            delete player;
            break;
        }
        else if (actthree(com))
        {

            string move_msg = player->playerMove(com);

            if (samestr(move_msg, "nextFloor"))
            {
                if (floor->getLevel() == 5)
                {
                    cout << "Congrats, you survived the dungeon! " << endl;
                    int score;
                    if (samestr(player->getRace(),"Shade")){
                        int gold = player->getgold();
                        score = gold*1.5;
                        cout << "Your score is " + to_string(score) << ". ";
                    }else {
                        score = player->getgold();
                        cout << "Your score is " + to_string(score) << ". ";
                    }
                    cout << "new game? [y/n]   ";
                    string s;
                    cin >> s;
                    if (samestr(s, "y"))
                    {
                        newGame();
                        break;
                    }
                }
                mes += "You entered the deeper floor. ";
                newFloor();
                continue;
            }
            else if (move_msg[0] >='0' && move_msg[0] <= '9')
            {
                mes += "MOVED TO " + com + ". Found " + move_msg + " golds. ";
            }
            else if (!samestr(move_msg,"You moved to " ))
            {
                mes += move_msg + com + ". ";
                continue;
            }
            else
            {
                mes += move_msg + com + ". ";
            }
        }
        else if (actfour(com))
        {
            string s;
            cin >> s;
            string atk_msg = floor->playerAttack(s);
            if (samestr(atk_msg, "noenemy"))
            {
                mes += "There is no enemy on " + s + ". ";
                continue;
            }
            else
            {
                mes += atk_msg;
            }
        }
        else if (actfive(com))
        {
            string s;
            cin >> s;
            mes += floor->consumePotion(s);
        }
        else
        {
            mes += "Invalid input!";
            continue;
        }
        if (player->getHp() == 0)
        {
            Isdead = true;
            continue;
        }

        vector<Posn *> neighbours = player->getpos()->getNbers();
        Enemy **enemies = floor->getEnemies();
        int i = 0;
        while (i != 20)
        {
            Enemy *e = enemies[i];
            if (e)
            {
                if (e->getHp() == 0)
                {
                    if (samestr(player->getRace(), "Goblin"))
                    {
                        player->addgold(5);
                    }
                    enemies[i]->dropgold();
                    enemies[i]->setpos(nullptr);
                    delete enemies[i];
                    enemies[i] = nullptr;
                }
            }
            ++i;
        }
        int u = 0;
        while (u < 8)
        {
            Base *obj = neighbours[u]->getbase();
            Enemy *e = nullptr;
            if (obj)
            {

                if (samestr(obj->gettp(), "enemy"))
                {
                    e = dynamic_cast<Enemy *>(obj);
                    if (obj->getrace() == "Dragon")
                    {
                        e->inactivate();
                    }
                }
                else if ((samestr(obj->gettp(), "treasure")) &&
                         (samestr(dynamic_cast<Treasure *>(obj)->getSize(), "Dragon")))
                {
                    e = dynamic_cast<DragonHoard *>(obj)->getDragon();
                    if (e)
                        e->inactivate();
                }
            }

            if (e)
            {
                if ((samestr(e->getRace(), "Merchant")) && !Merchant::hostile)
                {
                    mes += "A friendly Merchant is there. ";
                    ++u;
                    continue;
                }
                if (!(e->isActive()))
                {
                    if ((samestr(e->getRace(), "Dragon")) && atk)
                    {

                        ++u;
                        continue;
                    }
                    else if (samestr(e->getRace(), "Dragon"))
                        atk = true;
                    mes += e->Damage(player);
                    e->activate();
                    if (player->getHp() == 0)
                    {
                        Isdead = true;
                        ++u;
                        continue;
                    }
                }
            }
            ++u;
        }

        int h = 0;
        while (h < 20)
        {
            if (enemies[h])
            {
                if (!enemies[h]->isActive())
                {
                    int count = 0;
                emy_move__:
                    int dirc = rand() % 4;
                    count++;
                    if ((samestr(enemies[h]->move(dirc), "nomove")) && count != 8)
                        goto emy_move__;
                }
                enemies[h]->inactivate();
            }
            ++h;
        }

        if (!Isdead && (samestr(player->getRace(), "Troll")) && player->getHp() != player->getMaxHp())
        {
            player->heal(5);
            mes += "Healed yourself 5 HP. ";
        }
    }
}

