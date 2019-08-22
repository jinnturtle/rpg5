#include "Ui.hpp"

Ui::Ui(Viewport* viewport, Pawn_statsview* statsview, Log_viewer* logview)
: viewport{viewport}
, statsview{statsview}
, logview{logview}
{}

void Ui::render()
{
    if(this->viewport) {this->viewport->render();}
    if(this->statsview) {this->statsview->render();}
    if(this->logview) {this->logview->render();}
}
