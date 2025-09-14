#include "UIHandler.h"
#include <iostream>
#include <limits>

UIHandler::UIHandler(TaskManager& tm) : taskManager(tm) {}

void UIHandler::clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string UIHandler::getStringInput(const std::string& prompt) {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    return input;
}

int UIHandler::getIntInput(const std::string& prompt) {
    int value;
    std::cout << prompt;
    std::cin >> value;
    clearInputBuffer();
    return value;
}

void UIHandler::displayMenu() {
    std::cout << "TASK MANAGER" << std::endl
              << "Please choose an operation option" << std::endl
              << "1: View your tasks" << std::endl
              << "2: Add a new task" << std::endl
              << "3: Delete a task" << std::endl
              << "4: Edit a task" << std::endl
              << "5: Toggle task completion" << std::endl
              << "0: Exit" << std::endl;
}

void UIHandler::handleViewTasks() {
    std::cout << std::endl << "You chose to view your tasks" << std::endl << std::endl;
    taskManager.printAllTasks();
}

void UIHandler::handleAddTask() {
    std::cout << std::endl << "You chose to add a new task" << std::endl << std::endl;
    
    std::string content = getStringInput("Please type in task -> ");
    
    if (taskManager.addTask(content)) {
        std::cout << std::endl << "Successfully added the new task" << std::endl << std::endl;
    } else {
        std::cout << std::endl << "Failed to add task" << std::endl << std::endl;
    }
}

void UIHandler::handleDeleteTask() {
    std::cout << std::endl << "You chose to delete a task" << std::endl << std::endl;
    
    if (taskManager.isEmpty()) {
        std::cout << "No tasks to delete." << std::endl << std::endl;
        return;
    }
    
    taskManager.printAllTasks();
    
    int uid = getIntInput("Please choose the uid of the task to be deleted -> ");
    
    Task* task = taskManager.getTask(uid);
    if (task) {
        std::string content = task->content;
        if (taskManager.deleteTask(uid)) {
            std::cout << std::endl << "Successfully deleted task: " << std::endl 
                      << content << std::endl << std::endl;
        } else {
            std::cout << std::endl << "Failed to delete task" << std::endl << std::endl;
        }
    } else {
        std::cout << std::endl << "Task with UID " << uid << " does not exist." << std::endl << std::endl;
    }
}

void UIHandler::handleEditTask() {
    std::cout << std::endl << "You chose to edit a task" << std::endl << std::endl;
    
    if (taskManager.isEmpty()) {
        std::cout << "No tasks to edit." << std::endl << std::endl;
        return;
    }
    
    taskManager.printAllTasks();
    
    int uid = getIntInput("Please choose the uid of the task to be edited -> ");
    
    if (!taskManager.taskExists(uid)) {
        std::cout << std::endl << "Task with UID " << uid << " does not exist." << std::endl << std::endl;
        return;
    }
    
    std::string newContent = getStringInput("Please type in new task content -> ");
    
    if (taskManager.editTask(uid, newContent)) {
        std::cout << std::endl << "Successfully edited task: " << std::endl 
                  << newContent << std::endl << std::endl;
    } else {
        std::cout << std::endl << "Failed to edit task" << std::endl << std::endl;
    }
}

void UIHandler::handleToggleCompletion() {
    std::cout << std::endl << "You chose to toggle task completion" << std::endl << std::endl;
    
    if (taskManager.isEmpty()) {
        std::cout << "No tasks available." << std::endl << std::endl;
        return;
    }
    
    taskManager.printAllTasks();
    
    int uid = getIntInput("Please choose the uid of the task to toggle completion -> ");
    
    Task* task = taskManager.getTask(uid);
    if (task) {
        if (taskManager.toggleTaskCompletion(uid)) {
            std::cout << std::endl << "Successfully toggled completion for task: " << std::endl
                      << task->content << std::endl
                      << "Status: " << (task->completed ? "Completed" : "Pending") << std::endl << std::endl;
        } else {
            std::cout << std::endl << "Failed to toggle task completion" << std::endl << std::endl;
        }
    } else {
        std::cout << std::endl << "Task with UID " << uid << " does not exist." << std::endl << std::endl;
    }
}

void UIHandler::processUserChoice(int choice) {
    switch (choice) {
        case 1:
            handleViewTasks();
            break;
        case 2:
            handleAddTask();
            break;
        case 3:
            handleDeleteTask();
            break;
        case 4:
            handleEditTask();
            break;
        case 5:
            handleToggleCompletion();
            break;
        case 0:
            std::cout << std::endl << "Goodbye!" << std::endl;
            break;
        default:
            std::cout << std::endl << "Invalid option. Please try again." << std::endl << std::endl;
    }
}

void UIHandler::run() {
    int choice;
    
    do {
        displayMenu();
        choice = getIntInput("Type a valid option number -> ");
        processUserChoice(choice);
        
        if (choice != 0) {
            std::cout << "--------------------------------------------------------------" << std::endl << std::endl;
        }
    } while (choice != 0);
}