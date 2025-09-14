#pragma once
#include "TaskManager.h"
#include <string>

class UIHandler {
private:
    TaskManager& taskManager;
    
    // Input helpers
    std::string getStringInput(const std::string& prompt);
    int getIntInput(const std::string& prompt);
    void clearInputBuffer();
    
    // Menu operations
    void handleViewTasks();
    void handleAddTask();
    void handleDeleteTask();
    void handleEditTask();
    void handleToggleCompletion();

public:
    UIHandler(TaskManager& tm);
    
    void displayMenu();
    void processUserChoice(int choice);
    void run();
};