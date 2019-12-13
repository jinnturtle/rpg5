#include "Pawn.hpp"

#include <sstream>
#include <array>

// strength to damage conversion table
// TODO - later move to weapon class and make hand as one of weapons, as some
// creatures don't have hands and will use other conversions from strength
// e.g. hoof, claw, etc
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
           Pawn_controller contr,
           int team,
           const std::string& name,
           int hp,
           unsigned str)
: stats{.str = str}
, name{name}
, controller{contr}
, team{team}
, x{x}
, y{y}
, hp{hp}
, hp_max{this->hp}
, last_attacked{nullptr}
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

std::string Pawn::get_rough_health()
{
    // times 100 to represent percent of health remaining
    auto hp_perc {this->get_health_perc()};

    if(hp_perc >= 100) {
       return "unhurt";
    }
    else if(hp_perc >= 90) {
       return "slightly hurt";
    }
    else if(hp_perc >= 60) {
       return "hurt";
    }
    else if(hp_perc >= 10) {
       return "badly hurt";
    }
    else if(hp_perc >= 1) {
       return "near death";
    }
    else {
       return "dead";
    }
}

// get percent of health remaining
int Pawn::get_health_perc()
{
    return 100 * this->hp / this->hp_max;
}
