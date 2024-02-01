#include <iostream>
#include <vector>
#include <fstream>

struct Task {
    std::string description;
    bool completed;
};

const std::string SESSION_FILE = ".todolist_session.txt"; 

void displayMenu() {
    std::cout << "\n===== To-Do List Menu =====\n";
    std::cout << "1. Add Task\n";
    std::cout << "2. View Tasks\n";
    std::cout << "3. Mark Task as Completed\n";
    std::cout << "4. Edit Task\n";
    std::cout << "5. Remove Task\n";
    std::cout << "6. New Session\n";
    std::cout << "7. Exit\n";
    std::cout << "===========================\n";
}

void addTask(std::vector<Task>& tasks) {
    Task newTask;
    std::cout << "Enter task description: ";
    std::cin.ignore(); // Clear the input buffer
    std::getline(std::cin, newTask.description);
    newTask.completed = false;
    tasks.push_back(newTask);
    std::cout << "Task added successfully!\n";
}

void viewTasks(const std::vector<Task>& tasks) {
    std::cout << "\n===== To-Do List =====\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        std::cout << i + 1 << ". ";
        if (tasks[i].completed) {
            std::cout << "[X] ";
        } else {
            std::cout << "[ ] ";
        }
        std::cout << tasks[i].description << std::endl;
    }
    std::cout << "=======================\n";
}

void markTaskCompleted(std::vector<Task>& tasks) {
    viewTasks(tasks);

    if (!tasks.empty()) {
        size_t index;
        std::cout << "Enter the number of the task to mark as completed: ";
        std::cin >> index;

        if (index > 0 && index <= tasks.size()) {
            tasks[index - 1].completed = true;
            std::cout << "Task marked as completed!\n";
        } else {
            std::cout << "Invalid task number!\n";
        }
    } else {
        std::cout << "No tasks available.\n";
    }
}

void editTask(std::vector<Task>& tasks) {
    viewTasks(tasks);

    if (!tasks.empty()) {
        size_t index;
        std::cout << "Enter the number of the task to edit: ";
        std::cin >> index;

        if (index > 0 && index <= tasks.size()) {
            Task& taskToEdit = tasks[index - 1];
            std::cout << "Editing Task " << index << ":\n";
            
            std::cout << "Enter new task description: ";
            std::cin.ignore(); // Clear the input buffer
            std::getline(std::cin, taskToEdit.description);

            char completionChoice;
            std::cout << "Mark as completed? (y/n): ";
            std::cin >> completionChoice;
            taskToEdit.completed = (completionChoice == 'y' || completionChoice == 'Y');

            std::cout << "Task edited successfully!\n";
        } else {
            std::cout << "Invalid task number!\n";
        }
    } else {
        std::cout << "No tasks available.\n";
    }
}

void removeTask(std::vector<Task>& tasks) {
    viewTasks(tasks);

    if (!tasks.empty()) {
        size_t index;
        std::cout << "Enter the number of the task to remove: ";
        std::cin >> index;

        if (index > 0 && index <= tasks.size()) {
            tasks.erase(tasks.begin() + index - 1);
            std::cout << "Task removed successfully!\n";
        } else {
            std::cout << "Invalid task number!\n";
        }
    } else {
        std::cout << "No tasks available.\n";
    }
}

void saveTasks(const std::vector<Task>& tasks) {
    std::ofstream sessionFile(SESSION_FILE);

    if (sessionFile.is_open()) {
        for (const auto& task : tasks) {
            sessionFile << task.description << "," << task.completed << "\n";
        }
        std::cout << "Tasks saved to " << SESSION_FILE << std::endl;
        sessionFile.close();
    } else {
        std::cerr << "Error opening session file for writing!\n";
    }
}

void loadTasks(std::vector<Task>& tasks) {
    std::ifstream sessionFile(SESSION_FILE);

    if (sessionFile.is_open()) {
        tasks.clear();

        std::string line;
        while (std::getline(sessionFile, line)) {
            size_t commaPos = line.find(',');
            if (commaPos != std::string::npos) {
                Task loadedTask;
                loadedTask.description = line.substr(0, commaPos);
                loadedTask.completed = (line.substr(commaPos + 1) == "1");
                tasks.push_back(loadedTask);
            }
        }

        std::cout << "Tasks loaded from " << SESSION_FILE << std::endl;
        sessionFile.close();
    } else {
        std::cerr << "Creating a new session file.\n";
        std::ofstream newSessionFile(SESSION_FILE);
        newSessionFile.close();
    }
}

int main() {
    std::vector<Task> tasks;

    loadTasks(tasks);

    int choice;
    do {
        displayMenu();
        std::cout << "Enter your choice (1-7): ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addTask(tasks);
                break;
            case 2:
                viewTasks(tasks);
                break;
            case 3:
                markTaskCompleted(tasks);
                saveTasks(tasks); // Autosave after marking a task as completed
                break;
            case 4:
                editTask(tasks);
                saveTasks(tasks); // Autosave after editing a task
                break;
            case 5:
                removeTask(tasks);
                saveTasks(tasks); // Autosave after removing a task
                break;
            case 6:
                saveTasks(tasks); // Autosave before starting a new session
                std::cout << "Starting a new session...\n";
                tasks.clear();
                break;
            case 7:
                std::cout << "Exiting the program. Goodbye!\n";
                saveTasks(tasks); // Autosave before exiting
                break;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 7.\n";
        }

    } while (choice != 7);

    return 0;
}
