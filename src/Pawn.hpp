#ifndef PAWN_HPP
#define PAWN_HPP

#include <string>

#include "world.hpp"

enum Pawn_controller {
    PLAYER = 0,
    AI_NONE,
    AI_BASIC
};

class Pawn {
    struct Stats {
        int per;
        int str;
    };
    
public:
    Pawn(const std::string& name, int x, int y,
         Pawn_controller contr, int team,
         int hp = 10, int hp_max = 10, int dmg = 1);
    virtual ~Pawn(){};

    void move(Direction dir);
    void take_damage(int dmg);
    std::string attack(Pawn* enemy);
    
private:
    Stats stats;
    std::string name;
    Pawn_controller controller;
    int team;
    int x, y;
    int hp, hp_max;
    int dmg; //obsolete, should calculate based on str + weapon + effects, etc

    friend class Viewport;
    friend class Data_master;
    friend class Pawn_statsview;
};

#endif //define PAWN_HPP
