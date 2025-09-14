#include "FileManager.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

FileManager::FileManager(const std::string& directory) : contentDir(directory) {
    // Create directory if it doesn't exist
    std::filesystem::create_directories(contentDir);
}

int FileManager::parseFileName(const std::string& path) {
    size_t lastSlash = path.find_last_of("/\\");
    size_t lastDot = path.find_last_of('.');
    
    if (lastDot == std::string::npos || lastSlash == std::string::npos) {
        return -1;
    }
    
    std::string filename = path.substr(lastSlash + 1, lastDot - lastSlash - 1);
    
    try {
        return std::stoi(filename);
    } catch (const std::exception&) {
        return -1;
    }
}

std::unordered_map<int, Task> FileManager::loadTasks() {
    std::unordered_map<int, Task> tasks;
    
    if (!std::filesystem::exists(contentDir)) {
        return tasks;
    }
    
    for (const auto& entry : std::filesystem::directory_iterator(contentDir)) {
        if (!entry.is_regular_file()) continue;
        
        std::string filePath = entry.path().string();
        int uid = parseFileName(filePath);
        
        if (uid < 0) continue;
        
        std::ifstream file(filePath);
        if (file.is_open()) {
            std::string content;
            std::getline(file, content);
            tasks[uid] = Task(uid, content, false);
            file.close();
        }
    }
    
    return tasks;
}

std::set<int> FileManager::getAvailableUIDs(const std::set<int>& usedUIDs, int maxUID) {
    std::set<int> availableUIDs;
    
    for (int i = 0; i <= maxUID; ++i) {
        if (usedUIDs.find(i) == usedUIDs.end()) {
            availableUIDs.insert(i);
        }
    }
    
    return availableUIDs;
}

bool FileManager::saveTask(int uid, const std::string& content) {
    try {
        std::string filePath = contentDir + "/" + std::to_string(uid) + ".txt";
        std::ofstream file(filePath);
        
        if (!file.is_open()) {
            return false;
        }
        
        file << content;
        file.close();
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error saving task: " << e.what() << std::endl;
        return false;
    }
}

bool FileManager::deleteTaskFile(int uid) {
    try {
        std::string filePath = contentDir + "/" + std::to_string(uid) + ".txt";
        return std::filesystem::remove(filePath);
    } catch (const std::exception& e) {
        std::cerr << "Error deleting task file: " << e.what() << std::endl;
        return false;
    }
}

bool FileManager::taskFileExists(int uid) {
    std::string filePath = contentDir + "/" + std::to_string(uid) + ".txt";
    return std::filesystem::exists(filePath);
}