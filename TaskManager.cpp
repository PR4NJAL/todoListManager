#include "TaskManager.h"
#include <iostream>
#include <algorithm>
#include <set>

TaskManager::TaskManager(const std::string& contentDir) : fileManager(contentDir) {
    // Load existing tasks
    tasks = fileManager.loadTasks();
    
    // Build available UIDs queue
    std::set<int> usedUIDs;
    int maxUID = -1;
    
    for (const auto& [uid, task] : tasks) {
        usedUIDs.insert(uid);
        if (uid > maxUID) {
            maxUID = uid;
        }
    }
    
    // Add available UIDs to the priority queue
    std::set<int> available = fileManager.getAvailableUIDs(usedUIDs, maxUID);
    for (int uid : available) {
        availableUIDs.push(uid);
    }
}

int TaskManager::getNextUID() {
    if (!availableUIDs.empty()) {
        int uid = availableUIDs.top();
        availableUIDs.pop();
        return uid;
    }
    return tasks.size();
}

bool TaskManager::addTask(const std::string& content) {
    try {
        int uid = getNextUID();
        
        if (fileManager.saveTask(uid, content)) {
            tasks[uid] = Task(uid, content, false);
            return true;
        }
        
        // If saving failed, return the UID to available pool
        availableUIDs.push(uid);
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Error in addTask: " << e.what() << std::endl;
        return false;
    }
}

bool TaskManager::deleteTask(int uid) {
    try {
        if (!taskExists(uid)) {
            throw std::runtime_error("UID does not exist.");
        }
        
        if (fileManager.deleteTaskFile(uid)) {
            tasks.erase(uid);
            availableUIDs.push(uid);
            return true;
        }
        
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Error in deleteTask: " << e.what() << std::endl;
        return false;
    }
}

bool TaskManager::editTask(int uid, const std::string& newContent) {
    try {
        if (!taskExists(uid)) {
            throw std::runtime_error("UID does not exist.");
        }
        
        if (fileManager.saveTask(uid, newContent)) {
            tasks[uid].content = newContent;
            // Note: We're not changing completion status during edit
            return true;
        }
        
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Error in editTask: " << e.what() << std::endl;
        return false;
    }
}

bool TaskManager::toggleTaskCompletion(int uid) {
    try {
        if (!taskExists(uid)) {
            throw std::runtime_error("UID does not exist.");
        }
        
        tasks[uid].completed = !tasks[uid].completed;
        
        // Save the task to update the file (you might want to store completion status in file)
        return fileManager.saveTask(uid, tasks[uid].content);
    } catch (const std::exception& e) {
        std::cerr << "Error in toggleTaskCompletion: " << e.what() << std::endl;
        return false;
    }
}

std::vector<Task> TaskManager::getAllTasks() const {
    std::vector<Task> taskList;
    for (const auto& [uid, task] : tasks) {
        taskList.push_back(task);
    }
    
    // Sort by UID for consistent display
    std::sort(taskList.begin(), taskList.end(), 
              [](const Task& a, const Task& b) { return a.uid < b.uid; });
    
    return taskList;
}

Task* TaskManager::getTask(int uid) {
    auto it = tasks.find(uid);
    return (it != tasks.end()) ? &(it->second) : nullptr;
}

bool TaskManager::taskExists(int uid) const {
    return tasks.find(uid) != tasks.end();
}

bool TaskManager::isEmpty() const {
    return tasks.empty();
}

void TaskManager::printTask(const Task& task) const {
    std::cout << "UID: " << task.uid << std::endl
              << "Content: " << task.content << std::endl
              << "Completed: " << (task.completed ? "Yes" : "No") << std::endl;
}

void TaskManager::printAllTasks() const {
    if (isEmpty()) {
        std::cout << "EMPTY" << std::endl;
        return;
    }
    
    std::vector<Task> taskList = getAllTasks();
    for (const Task& task : taskList) {
        printTask(task);
        std::cout << std::endl;
    }
}