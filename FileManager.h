#pragma once
#include "Task.h"
#include <string>
#include <unordered_map>
#include <set>

class FileManager {
private:
    std::string contentDir;
    int parseFileName(const std::string& path);

public:
    FileManager(const std::string& directory = "./content");
    
    // Load all tasks from files
    std::unordered_map<int, Task> loadTasks();
    
    // Get available UIDs that can be reused
    std::set<int> getAvailableUIDs(const std::set<int>& usedUIDs, int maxUID);
    
    // File operations
    bool saveTask(int uid, const std::string& content);
    bool deleteTaskFile(int uid);
    bool taskFileExists(int uid);
};