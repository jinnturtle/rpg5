#ifndef DATAMASTER_HPP
#define DATAMASTER_HPP

#include <vector>

#include "Pawn.hpp"
#include "Floor_map.hpp"

// tabletop RPGs have a game master (aka. dungeon master), this is
// the data master (your digital DM)
class Data_master final {
public:
    void set_player(Pawn* player);
    void move_pawns(Direction player_input);
    void add_pawn(Pawn* pawn);
    void set_floor_map(Floor_map* map);
    bool get_gameover();
    
private:
    Pawn* player;
    std::vector<Pawn*> pawns;
    Floor_map* map;

    void update_pawns();
    void move_pawn(Pawn* pawn, Direction direction);
    void move_pawn(Pawn* pawn, int x, int y);
    void player_take_turn(Pawn* pawn, Direction player_input);
    void ai_basic_take_turn(Pawn* pawn);
    Pawn* get_pawn_at(int x, int y);
    
    friend class Viewport;
};

#endif //#ifndef DATAMASTER_HPP
