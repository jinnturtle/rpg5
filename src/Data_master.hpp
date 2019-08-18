#ifndef DATAMASTER_HPP
#define DATAMASTER_HPP

#include <vector>

#include "Pawn.hpp"

// tabletop RPGs have a game master (aka. dungeon master), this is
// the data master (your digital DM)
class Data_master final {
public:
    void move_pawns(Direction player_input);
    void add_pawn(Pawn* pawn);
    void set_floor_map(Floor_map* map);
    void set_player(Pawn* pawn);
    
private:
    std::vector<Pawn*> pawns;
    Floor_map* map;

    void player_take_turn(Pawn* pawn, Direction player_input);
    void ai_basic_take_turn(Pawn* pawn);
    Pawn* get_pawn_at(int x, int y);
    void update_pawns();
    
    friend class Viewport;
};

#endif //#ifndef DATAMASTER_HPP
