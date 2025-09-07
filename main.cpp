#include <bits/stdc++.h> //Replace this with specfics later
using namespace std;

static int uid = 0; // global variable

class taskList {
private:
  unordered_map<int, pair<string, bool>> map;

public:
  void bootstrapping() {

  } // meant to read from storage and set the hash map, on a seprate thread

  void addTask() {
    cout << "Please type in task -> ";
    string content;
    getline(cin, content);

    ofstream file;
    file.open("./content/" + to_string(map.size()) +
              ".txt"); // Have to have content dir prior
    if (!file.is_open())
      cerr << "Error: Unable to open file";
    else
      file << content;

    file.close();

    map[map.size()].first = content;
    map[map.size()].second = false;
    cout << endl << "Succesfully added the new task" << endl << endl;
  }

  void printTasks() {
    if (map.size() == 0) {
      cout << "EMPTY" << endl;
      return;
    }

    for (const auto &m : map) {
      cout << "UID:" << m.first << endl
           << "Content: " << m.second.first << endl
           << "Completed: " << m.second.second << endl;
    }
  }

  void deleteTask() {
    printTasks();
    cout << endl << "Please choose the uid of the task to be deleted -> ";
    int uid;
    cin >> uid;
    string content = map[uid].first;
    map.erase(uid);
    cout << endl << "Succesfully deleted task: " << endl << content << endl;
  }

  void editTask() {
    // NOTE:Support for only content edits right now!!!!!
    printTasks();
    cout << endl << "Please choose the uid of the task to be edited -> ";
    int uid;
    cin >> uid;
    cout << "Please type in new task content -> ";
    string content;
    getline(cin, content);
    map[uid].first = content;
    map[uid].second = false;
    cout << endl << "Succesfully edited task: " << endl << content << endl;
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
      newTaskList.printTasks();
      break;
    case 2:
      cout << endl << "You chose to add a new task" << endl << endl;
      newTaskList.addTask();
      break;
    case 3:
      cout << endl << "You chose to delete a task" << endl << endl;
      newTaskList.deleteTask();
      break;
    case 4:
      cout << endl << "You chose to edit a task" << endl << endl;
      newTaskList.editTask();
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
