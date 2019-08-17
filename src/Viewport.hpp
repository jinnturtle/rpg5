#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

//std C++ lib
#include <vector>

//3rd party libs
#include <ncurses.h>

//homebrew
#include "Data_master.hpp"

class Viewport final {
public:
    Viewport(int x = 0, int y = 0, int w = 80, int h = 24);

    void attach_dm(Data_master* dm);
    void render();

private:
    int x, y; // position on the GUI
    int w, h; // dimensions on the GUI
    int map_x, map_y; // position in the map
    Data_master* dm;
    
    void render_level();
    void render_pawns();
    void addch_at(int x, int y, char glyph);
};

#endif //define VIEWPORT_HPP
