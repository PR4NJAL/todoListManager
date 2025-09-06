#include <bits/stdc++.h>
using namespace std;

class taskList {
public:
  unordered_map<int, string> map;

  void addTask() {
    cout << "Please type in task -> ";
    string content;
    getline(cin, content);
    map[0] = content;
    cout << endl << "Succesfully added the new task" << endl << endl;
  }
};

int main() {
  taskList newTaskList;

  while (1) {
    cout << "TASK MANAGER" << endl
         << "Please choose an operation option" << endl
         << "1: View your tasks" << endl
         << "2: Add a new task" << endl
         << "3: Delete a task" << endl
         << "4: Edit a task" << endl;

    int option = 0;
    cout << endl << "Type a valid option number -> ";
    cin >> option;
    cin.ignore(numeric_limits<streamsize>::max(),
               '\n'); // Clear the input buffer (suggested by AI)

    switch (option) {
    case 1:
      cout << endl << "You chose to view your tasks" << endl << endl;
      // Print the list
      break;
    case 2:
      cout << endl << "You chose to add a new task" << endl << endl;
      newTaskList.addTask();
      break;
    case 3:
      cout << endl << "You chose to delete a task" << endl << endl;
      // Choose uid
      // Delete the uid from storage
      // Print confirmation
      break;
    case 4:
      cout << endl << "You chose to edit a task" << endl << endl;
      // Choose uid
      // Choose whether to edit the content
      // or edit the completed boolean
      break;
    default:
      cout << endl
           << "You chose an invalid option...Please try again" << endl
           << endl;
    }
    cout << "--------------------------------------------------------------"
         << endl
         << endl;
  }
  return 0;
}
