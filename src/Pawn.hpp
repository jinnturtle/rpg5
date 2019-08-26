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
        unsigned str;
    };
    
public:
    Pawn(int x, int y,
         Pawn_controller contr, int team,
         const std::string& name, 
         int hp, unsigned str);
    virtual ~Pawn(){};

    void move(Direction dir);
    void take_damage(int dmg);
    bool check_dead();
    std::string get_dmg_dice();
    
private:
    Stats stats;
    std::string name;
    Pawn_controller controller;
    int team;
    int x, y;
    int hp, hp_max;
    
    friend class Viewport;
    friend class Data_master;
    friend class Pawn_statsview;
};

#endif //define PAWN_HPP
