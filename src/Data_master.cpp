#include "Data_master.hpp"

#include <climits>
#include <cmath>
#include <sstream>

Data_master::Data_master()
: map{nullptr}
, turn{0}
{
}

void Data_master::make_turn(Direction player_input)
{
    ++this->turn;
    this->move_pawns(player_input);
}

void Data_master::move_pawns(Direction player_input)
{
    for(auto& pawn : this->pawns) {
        switch(pawn->controller) {
            case PLAYER: this->player_take_turn(pawn, player_input); break;
            case AI_BASIC: this->ai_basic_take_turn(pawn); break;
            default: break;
        }
    }
    
    this->update_pawns();
}

void Data_master::add_pawn(Pawn* pawn)
{
    this->pawns.push_back(pawn);
}

void Data_master::set_floor_map(Floor_map* map)
{
    this->map = map;
}

bool Data_master::get_gameover()
{
    for(auto& pawn : this->pawns) {
        if(pawn->controller == PLAYER) {return false;}
    }
    
    return true;
}

void Data_master::player_take_turn(Pawn* pawn, Direction player_input)
{
    if(pawn->controller == PLAYER) {
        this->move_pawn(pawn, player_input);
    }
}

void Data_master::ai_basic_take_turn(Pawn* pawn)
{
    // this AI biscally moves to the closes non-friendly pawn and attacks it
    
    int closest_dist {INT_MAX};
    Pawn* closest_enemy {nullptr};
    for(auto& other_pawn : this->pawns) {
        // skip team-mates
        if(other_pawn->team == pawn->team) {continue;}
        
        int dist_x {abs(other_pawn->x - pawn->x)};
        int dist_y {abs(other_pawn->y - pawn->y)};
        int distance {dist_x + dist_y};
        if(closest_dist > distance) {
            closest_dist = distance;
            closest_enemy = other_pawn;
        }
    }
    
    //decide movement direction to get closer if were not close enough
    Direction direction{NONE};
    if(closest_enemy) {
        if(closest_enemy->x > pawn->x) {direction = EAST;}
        else if(closest_enemy->x < pawn->x) {direction = WEST;}
        else if(closest_enemy->y < pawn->y) {direction = NORTH;}
        else if(closest_enemy->y > pawn->y) {direction = SOUTH;}
    }
    this->move_pawn(pawn, direction);
}

Pawn* Data_master::get_pawn_at(int x, int y)
{
    for(auto& pawn: this->pawns) {
        if(pawn->x == x && pawn->y == y) {
            return pawn;
        }
    }
    
    return nullptr;
}

void Data_master::update_pawns()
{
    for(size_t i {0}; i < this->pawns.size(); ++i) {
        // if pawn is dead, delete by overwrting with back and delete back
        if(this->pawns[i]->hp <= 0) {
            this->pawns[i] = this->pawns.back();
            this->pawns.pop_back();
        }
    }
}

void Data_master::move_pawn(Pawn* pawn, Direction direction)
{
    int tgt_x = pawn->x;
    int tgt_y = pawn->y;
    
    switch(direction) {
        case NORTH: --tgt_y; break;
        case EAST: ++tgt_x; break;
        case SOUTH: ++tgt_y; break;
        case WEST: --tgt_x; break;
        default: break;
    }
    
    this->move_pawn(pawn, tgt_x, tgt_y);
}

void Data_master::move_pawn(Pawn* pawn, int x, int y)
{
    // dead pawns should not move (and retaliate after death)
    // the undead state is a different thing
    if(pawn->check_dead()) {return;}
    
    // check if there is a creature at target location, attack if so
    Pawn* tgt_pawn = this->get_pawn_at(x, y);
    if(tgt_pawn) {
        if(tgt_pawn != pawn && tgt_pawn->team != pawn->team) {
            pawn_attack(pawn, tgt_pawn);
        }
        
        return;
    }
    
    // see if the target coordinates are passable, and move there if so
    Tile* tgt_tile = this->map->get_tile(x, y);
    if(tgt_tile == nullptr) {return;}
    
    if(tgt_tile->get_type() != WALL) {
        pawn->x = x;
        pawn->y = y;
    }
}

void Data_master::pawn_attack(Pawn* attacker, Pawn* target)
{
    int dmg{roll_dice(attacker->get_dmg_dice())};
    if(dmg < 0) {dmg = 0;} // no unintentionally healing attacks
    // int dmg{attacker->get_dmg_dice()};
    
    target->take_damage(dmg);
    
    std::stringstream msg;
    msg << attacker->name << " attacks " << target->name
        << " for " << dmg << " damage.";
    if(target->check_dead()) {
        msg << " " << target->name << " expires.";
    }
    this->add_message(msg.str());
}

void Data_master::add_message(const std::string& msg)
{
    if(msg.size() > 0) {this->log.push_back(msg);}
}
