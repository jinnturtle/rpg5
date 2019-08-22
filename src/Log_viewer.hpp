#ifndef LOG_VIEWER_HPP
#define LOG_VIEWER_HPP

#include "Data_master.hpp"

class Log_viewer {
public:
    Log_viewer(int x, int y, unsigned w, unsigned h, Data_master* dm = nullptr);
    
    void attach_log(Data_master* dm);
    void render();
    
private:
    int x, y;
    unsigned w, h;
    size_t top_line;
    Message_log* log; // the attached log to display
};

#endif //#ifndef LOG_VIEWER_HPP
