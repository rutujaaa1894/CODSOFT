#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Task {
    string description;
    bool isDone;
};

vector<Task> todoList;

void displayMenu() {
    cout << "To-Do List Manager" << endl;
    cout << "-----------------" << endl;
    cout << "1. Add Task" << endl;
    cout << "2. List Tasks" << endl;
    cout << "3. Mark Task as Complete" << endl;
    cout << "4. Remove Task" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

void addTask() {
    Task newTask;
    cout << "Enter a task: ";
    cin.ignore();
    getline(cin, newTask.description);
    newTask.isDone = false;
    todoList.push_back(newTask);
    cout << "Task added successfully!" << endl;
}

void listTasks() {
    if (todoList.empty()) {
        cout << "No tasks available." << endl;
        return;
    }

    cout << "To-Do List:" << endl;
    for (int i = 0; i < todoList.size(); i++) {
        cout << i + 1 << ". " << todoList[i].description;
        if (todoList[i].isDone) {
            cout << " (Complete)";
        } else {
            cout << " (Pending)";
        }
        cout << endl;
    }
}

void markTaskAsComplete() {
    if (todoList.empty()) {
        cout << "No tasks available." << endl;
        return;
    }

    int taskNumber;
    cout << "Enter the task number to mark as complete: ";
    cin >> taskNumber;

    if (taskNumber > 0 && taskNumber <= todoList.size()) {
        todoList[taskNumber - 1].isDone = true;
        cout << "Task marked as complete successfully!" << endl;
    } else {
        cout << "Invalid task number." << endl;
    }
}

void removeTask() {
    if (todoList.empty()) {
        cout << "No tasks available." << endl;
        return;
    }

    int taskNumber;
    cout << "Enter the task number to remove: ";
    cin >> taskNumber;

    if (taskNumber > 0 && taskNumber <= todoList.size()) {
        todoList.erase(todoList.begin() + taskNumber - 1);
        cout << "Task removed successfully!" << endl;
    } else {
        cout << "Invalid task number." << endl;
    }
}

int main() {
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                listTasks();
                break;
            case 3:
                markTaskAsComplete();
                break;
            case 4:
                removeTask();
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
    }

    return 0;
}