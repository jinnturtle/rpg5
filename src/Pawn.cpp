#include "Pawn.hpp"

Pawn::Pawn(const std::string& name, int x, int y, Pawn_controller contr,
           int hp, int hp_max, int dmg)
: name{name}
, controller{contr}
, x{x}
, y{y}
, hp{hp}
, hp_max{hp_max}
, dmg{dmg}
, map{nullptr}
{}

void Pawn::move(Direction dir)
{
    int tgt_x = this->x;
    int tgt_y = this->y;

    // set target coordinates (where we want to move to)
    switch(dir) {
        case NORTH: --tgt_y; break;
        case EAST:  ++tgt_x; break;
        case SOUTH: ++tgt_y; break;
        case WEST:  --tgt_x; break;
        default: break;
    }

    // see if the target coordinates are passable, and move there if so
    Tile* tgt_tile = this->map->get_tile(tgt_x, tgt_y);
    if(tgt_tile == nullptr) {return;}
    
    if(tgt_tile->get_type() != WALL) {
        this->x = tgt_x;
        this->y = tgt_y;
    }
}

void Pawn::assign_map(Floor_map* map) {this->map = map;}

void Pawn::attack(Pawn* enemy) {enemy->take_damage(this->dmg);}

void Pawn::take_damage(int dmg) {this->hp -= dmg;}
