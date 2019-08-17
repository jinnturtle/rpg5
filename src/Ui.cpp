#include "Ui.hpp"

Ui::Ui(Viewport* viewport, Pawn_statsview* statsview)
: viewport{viewport}
, statsview{statsview}
{}

void Ui::render()
{
    if(this->viewport) {this->viewport->render();}
    if(this->statsview) {this->statsview->render();}
}
