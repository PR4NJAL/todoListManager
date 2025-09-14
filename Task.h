#pragma once
#include <string>

struct Task {
    int uid;
    std::string content;
    bool completed;
    
    Task() : uid(-1), content(""), completed(false) {}
    Task(int id, const std::string& text, bool done = false) 
        : uid(id), content(text), completed(done) {}
};