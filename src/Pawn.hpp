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
    // TODO - include max_hp here
    struct Stats {
        int str;
        int max_hp;
    };

public:
    Pawn(int x, int y,
         Pawn_controller contr,
         int team,
         const std::string& name,
         int hp,
         int str,
         unsigned stat_variation = 20 /* stat variation percentage */
        );
    virtual ~Pawn(){};

    void move(Direction dir);
    void take_damage(int dmg);
    bool check_dead();
    std::string get_dmg_dice();
    std::string get_rough_health();
    int get_health_perc();

private:
    Stats stats;
    std::string name;
    Pawn_controller controller;
    int team;
    int x, y;
    int hp;

    Pawn* last_attacked; // the pawn that was last attacked by this one

    friend class Viewport;
    friend class Data_master;
    friend class Pawn_statsview;
};

#endif //define PAWN_HPP
