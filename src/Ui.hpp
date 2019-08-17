#ifndef UI_HPP
#define UI_HPP

#include "Viewport.hpp"
#include "Pawn_statsview.hpp"

class Ui final {
public:
    Ui(Viewport* viewport = nullptr, Pawn_statsview* statsview = nullptr);
    
    void render();
    
private:
    Viewport* viewport;
    Pawn_statsview* statsview;
};

#endif //define UI_HPP
