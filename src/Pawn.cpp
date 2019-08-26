#include "Pawn.hpp"

#include <sstream>
#include <array>

static const std::array<std::string, 21> str_dmg_ref {
    "1d0", // 0
    "1d6 - 5",
    "1d6 - 5",
    "1d6 - 4",
    "1d6 - 4",
    "1d6 - 3",
    "1d6 - 3",
    "1d6 - 2",
    "1d6 - 2",
    "1d6 - 1",
    "1d6", // 10
    "1d6 + 1",
    "1d6 + 2",
    "2d6 - 1",
    "2d6",
    "2d6 + 1",
    "2d6 + 2",
    "3d6 - 1",
    "2d6",
    "2d6 + 1",
    "2d6 + 2", // 20
};

Pawn::Pawn(int x, int y,
           Pawn_controller contr, int team,
           const std::string& name,
           int hp, unsigned str)
: stats{.str = str}
, name{name}
, controller{contr}
, team{team}
, x{x}
, y{y}
, hp{hp}
, hp_max{this->hp}
{}

void Pawn::move(Direction dir)
{
    // set target coordinates (where we want to move to)
    switch(dir) {
        case NORTH: --this->y; break;
        case EAST:  ++this->x; break;
        case SOUTH: ++this->y; break;
        case WEST:  --this->x; break;
        default: break;
    }
}

void Pawn::take_damage(int dmg) {this->hp -= dmg;}

bool Pawn::check_dead() {return(this->hp <= 0);}

std::string Pawn::get_dmg_dice()
{
    if(this->stats.str < str_dmg_ref.size()) {
        return str_dmg_ref[this->stats.str];
    } else {
        return str_dmg_ref.back();
    }
}
