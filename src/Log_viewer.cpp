#include "Log_viewer.hpp"

#include <ncurses.h>

Log_viewer::Log_viewer(int x, int y, unsigned w, unsigned h, Data_master* dm)
: x{x}
, y{y}
, w{w}
, h{h}
{
    if(dm) {
        this->log = &dm->log;
    } else {
        this->log = nullptr;
    }
}

void Log_viewer::attach_log(Data_master* dm) {this->log = &dm->log;}

void Log_viewer::render()
{
    if(this->log == nullptr) {return;} // TODO log warning
    
    Message_log::reverse_iterator ritr;
    ritr = this->log->rbegin();
    for(size_t i{0}; i < h && i < this->log->size(); ++i) {
        mvprintw(this->y + i, this->x, ritr[i].c_str());
    }
}
