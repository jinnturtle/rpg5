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
        int str;
    };
    
public:
    Pawn(int x, int y,
         Pawn_controller contr, int team,
         const std::string& name, 
         int hp, int str);
    virtual ~Pawn(){};

    void move(Direction dir);
    void take_damage(int dmg);
    std::string attack(Pawn* enemy);
    bool check_dead();
    
private:
    Stats stats;
    std::string name;
    Pawn_controller controller;
    int team;
    int x, y;
    int hp, hp_max;
    
    int calc_dmg();

    friend class Viewport;
    friend class Data_master;
    friend class Pawn_statsview;
};

#endif //define PAWN_HPP
