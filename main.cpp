#include "TaskManager.h"
#include "UIHandler.h"
#include <iostream>
#include <exception>

int main() {
    try {
        TaskManager taskManager("./content");
        UIHandler ui(taskManager);
        
        ui.run();
        
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return -1;
    }
    
    return 0;
}