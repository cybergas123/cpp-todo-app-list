#include <iostream>
#include <vector>

struct Task {
    std::string description;
    bool completed;
};

void displayMenu() {
    std::cout << "\n===== To-Do List Menu =====\n";
    std::cout << "1. Add Task\n";
    std::cout << "2. View Tasks\n";
    std::cout << "3. Mark Task as Completed\n";
    std::cout << "4. Exit\n";
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

int main() {
    std::vector<Task> tasks;

    int choice;
    do {
        displayMenu();
        std::cout << "Enter your choice (1-4): ";
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
                break;
            case 4:
                std::cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
        }

    } while (choice != 4);

    return 0;
}
