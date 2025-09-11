#include <bits/stdc++.h> //TODO:Replace this with specfics later
#include <cstdio>
using namespace std;

class TaskList {
private:
  unordered_map<int, pair<string, bool>> map;
  priority_queue<int, vector<int>, greater<int>> pq;

  int parseFileName(string path) {
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
  TaskList() {
    string path = "./content";
    set<int> presentUIDs;
    int maxUID = -1;

    for (const auto &entry : filesystem::directory_iterator(path)) {
      string filePath = (entry.path()).string();
      ifstream file(filePath);
      int parseIndex = parseFileName(filePath);
      getline(file, map[parseIndex].first);
      map[parseIndex].second = false;
      file.close();
      presentUIDs.insert(parseIndex);
      if (parseIndex > maxUID)
        maxUID = parseIndex;
    }

    for (int i = 0; i <= maxUID; ++i) {
      if (presentUIDs.find(i) == presentUIDs.end()) {
        pq.push(i);
      }
    }
  }

  void addTask() {
    cout << "Please type in task -> ";
    string content;
    getline(cin, content);

    ofstream file;
    int index = 0;

    if (pq.empty()) {
      file.open("./content/" + to_string(map.size()) + ".txt");
      index = map.size();
    } else {
      file.open("./content/" + to_string(pq.top()) + ".txt");
      index = pq.top();
      pq.pop();
    }

    if (!file.is_open())
      cerr << "Error: Unable to open file";
    else {
      file << content;
      map[index].first = content;
      map[index].second = false;
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (map.find(uid) == map.end()) {
      cerr << "Error: UID does not exist." << endl;
      return;
    }

    int status = remove(("./content/" + to_string(uid) + ".txt").c_str());
    if (status != 0)
      cerr << "Error deleting task";
    else {
      string content = map[uid].first;
      map.erase(uid);
      pq.push(uid); // Add to the priority queue
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

    if (map.find(uid) == map.end()) {
      cerr << "Error: UID does not exist." << endl;
      return;
    }

    cout << "Please type in new task content -> ";
    string content;
    getline(cin, content);

    ofstream file;
    file.open("./content/" + to_string(uid) + ".txt");
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
// TODO:Add more error handling, Add specific headers instead,
// Modularize code instead of mono repo
