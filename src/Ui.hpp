#ifndef UI_HPP
#define UI_HPP

#include "Viewport.hpp"
#include "Pawn_statsview.hpp"
#include "Log_viewer.hpp"

class Ui final {
public:
    Ui(
        Viewport* viewport = nullptr,
        Pawn_statsview* statsview = nullptr,
        Log_viewer* logview = nullptr
    );
    
    void render();
    
private:
    Viewport* viewport;
    Pawn_statsview* statsview;
    Log_viewer* logview;
};

#endif //define UI_HPP
