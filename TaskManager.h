#pragma once
#include "Task.h"
#include "FileManager.h"
#include <unordered_map>
#include <queue>
#include <vector>

class TaskManager {
private:
    std::unordered_map<int, Task> tasks;
    std::priority_queue<int, std::vector<int>, std::greater<int>> availableUIDs;
    FileManager fileManager;
    
    int getNextUID();

public:
    TaskManager(const std::string& contentDir = "./content");
    
    // Core operations
    bool addTask(const std::string& content);
    bool deleteTask(int uid);
    bool editTask(int uid, const std::string& newContent);
    bool toggleTaskCompletion(int uid);
    
    // Query operations
    std::vector<Task> getAllTasks() const;
    Task* getTask(int uid);
    bool taskExists(int uid) const;
    bool isEmpty() const;
    
    // Display helpers
    void printTask(const Task& task) const;
    void printAllTasks() const;
};