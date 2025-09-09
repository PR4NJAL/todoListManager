#include <bits/stdc++.h> //Replace this with specfics later
#include <cstdio>
using namespace std;

class TaskList {
private:
  unordered_map<int, pair<string, bool>> map;

  int parseFileName(string path) { // Isn't this too long???
    int index = path.length();
    string returnStr = "";
    for (index = index - 1; index >= 0; index--) {
      if (path[index] == '.')
        break;
    }

    for (index = index - 1; index >= 0; index--) {
      if (path[index] != '/')
        returnStr += path[index];
      else
        break;
    }
    reverse(returnStr.begin(), returnStr.end());
    stringstream ss;
    ss << returnStr;
    int returnInt = 0;
    ss >> returnInt;
    return returnInt;
  }

public:
  TaskList() { // Formerly bootstrap function
    string path = "./content";
    for (const auto &entry : filesystem::directory_iterator(path)) {
      string filePath = (entry.path()).string();
      ifstream file;
      file.open(filePath);
      getline(file, map[parseFileName(filePath)].first);
      map[parseFileName(filePath)].second = false;
      file.close();
    }
  } // NOTE:Meant to read from storage and set the hash map, TODO:on a seprate
    // thread

  void addTask() {
    cout << "Please type in task -> ";
    string content;
    getline(cin, content);

    ofstream file;
    file.open("./content/" + to_string(map.size()) +
              ".txt"); // NOTE:Have to have content dir prior
    if (!file.is_open())
      cerr << "Error: Unable to open file";
    else {
      file << content;
      map[map.size()].first = content;
      map[map.size()].second = false;
      cout << endl << "Succesfully added the new task" << endl << endl;
    }
    file.close();
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

    int status = remove(("./content/" + to_string(uid) + ".txt")
                            .c_str()); // INFO:This is a C library function
    if (status != 0)
      cerr << "Error deleting task";
    else {
      string content = map[uid].first;
      map.erase(uid);
      cout << endl << "Succesfully deleted task: " << endl << content << endl;
    }
  }

  void editTask() {
    // NOTE:Support for only content edits right now!!!!!
    printTasks();
    cout << endl << "Please choose the uid of the task to be edited -> ";
    int uid;
    cin >> uid;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Please type in new task content -> ";
    string content;
    getline(cin, content);

    ofstream file;
    file.open("./content/" + to_string(uid) +
              ".txt"); // NOTE:Have to have content dir prior
    if (!file.is_open())
      cerr << "Error: Unable to open file";
    else {
      file << content;
      map[uid].first = content;
      map[uid].second = false;
      cout << endl << "Succesfully edited task: " << endl << content << endl;
    }
    file.close();
  }
};

int main() {
  TaskList newTaskList;

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
               '\n'); // INFO:Clear the input buffer (suggested by AI)

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
// TODO:Add Error Handling, Reuse deleted UID, Add specific headers instead,
// Modularize code instead of mono repo
