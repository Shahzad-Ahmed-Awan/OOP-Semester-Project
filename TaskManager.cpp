#include "TaskManager.h"

std::string TaskManager::getTaskFilePath() const {
    return "study_tasks_" + currentUser + ".txt";
}

int TaskManager::getPendingTaskCount() const {
    std::ifstream inFile(getTaskFilePath());
    if (!inFile.is_open()) return 0;
    std::string line;
    int count = 0;
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        try {
            size_t lastComma = line.rfind(',');
            if (lastComma != std::string::npos) {
                int status = std::stoi(line.substr(lastComma + 1));
                if (status == 0) {
                    count++;
                }
            }
        } catch (const std::exception& e) {
            // Skip invalid lines
        }
    }
    inFile.close();
    return count;
}

void TaskManager::addTask() {
    printSubHeader("Add a New Study Task");
    std::string title;
    int priority = 0;
    Date dueDate;
    std::cout << "\t\tEnter Task Title (use underscores for spaces): ";
    getline(std::cin, title);
    std::cout << "\t\tEnter Priority (1-High, 2-Medium, 3-Low): ";
    priority = getValidInt(1, 3);
    std::cout << "\t\t---------   Due Date For Task:  ----------------- \n";
    std::cout << "\t\tEnter Due Date (Day-1-31): ";
    dueDate.day = getValidInt(1, 31);
    std::cout << "\t\tEnter Due Date (Month-1-12): ";
    dueDate.month = getValidInt(1, 12);
    std::cout << "\t\tEnter Due Date (Month-2025-2050): ";
    dueDate.year = getValidInt(2025, 2050);
    
    std::ofstream outFile(getTaskFilePath(), std::ios::app);
    if (outFile.is_open()) {
        outFile << title << "," << priority << "," << dueDate.day << "," << dueDate.month << "," << dueDate.year << ",0\n";
        outFile.close();
        setColor(GREEN);
        std::cout << "\n\t\tTask added successfully!\n";
    } else {
        setColor(RED);
        std::cout << "\n\t\tError: Could not open tasks file for writing.\n";
    }
    setColor(RESET_COLOR);
    _getch();
}

void TaskManager::viewTasks() {
    printSubHeader("Your Study Tasks");
    std::ifstream inFile(getTaskFilePath());
    if (!inFile.is_open() || inFile.peek() == EOF) {
        std::cout << "\t\tNo tasks found. Add one first!\n";
        _getch();
        return;
    }
    std::string line;
    int count = 0;
    setColor(YELLOW);
    std::cout << "\t\t------------------------------------------------------------------\n";
    std::cout << "\t\t # |      Title      | Priority |   Due Date   | Status\n";
    std::cout << "\t\t------------------------------------------------------------------\n";
    setColor(RESET_COLOR);
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        count++;
        try {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t pos3 = line.find(',', pos2 + 1);
            size_t pos4 = line.find(',', pos3 + 1);
            size_t pos5 = line.find(',', pos4 + 1);
            
            std::string title = line.substr(0, pos1);
            int priority = std::stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
            int day = std::stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
            int month = std::stoi(line.substr(pos3 + 1, pos4 - pos3 - 1));
            int year = std::stoi(line.substr(pos4 + 1, pos5 - pos4 - 1));
            int status = std::stoi(line.substr(pos5 + 1));

            std::cout << "\t\t " << std::setw(2) << count << " | " << std::setw(15) << std::left << title.substr(0, 15) << " | ";
            if (priority == 1) { setColor(RED); std::cout << "High  "; }
            else if (priority == 2) { setColor(YELLOW); std::cout << "Medium"; }
            else { setColor(GREEN); std::cout << "Low   "; }
            setColor(RESET_COLOR);
            std::cout << " | " << day << "/" << month << "/" << year << " | ";
            if (status == 1) { setColor(BOLD_GREEN); std::cout << "Done\n"; }
            else { setColor(BOLD_RED); std::cout << "Pending\n"; }
            setColor(RESET_COLOR);
        } catch (const std::exception& e) {
            std::cout << "\t\t [Error reading task " << count << "]\n";
        }
    }
    std::cout << "\t\t------------------------------------------------------------------\n";
    inFile.close();
    _getch();
}

// The `runMenu()` method now encapsulates all task-related menu logic
void TaskManager::runMenu() {
    char choice;
    do {
        printSubHeader("Study Section");
        std::cout << "\t\t\t1. Add Task\n";
        std::cout << "\t\t\t2. View Tasks\n";
        std::cout << "\t\t\t3. Mark Task as Completed\n";
        std::cout << "\t\t\t4. Delete Task\n";
        std::cout << "\t\t\t5. Daily Review & Suggestions\n";
        std::cout << "\t\t\t6. Start Pomodoro Timer\n";
        setColor(YELLOW);
        std::cout << "\t\t\t7. Back to Main Menu\n";
        setColor(RESET_COLOR);
        std::cout << "\n\t\t\tEnter your choice: ";
        choice = _getch();
        switch (choice) {
            case '1': addTask(); break;
            case '2': viewTasks(); break;
            case '3': markTaskCompleted(); break;
            case '4': deleteTask(); break;
            case '5': dailyReview(); break;
            case '6': startPomodoro(); break;
            case '7': return;
            default:
                setColor(RED);
                std::cout << "\n\t\t\tInvalid choice. Please try again.\n";
                setColor(RESET_COLOR);
                _getch();
                break;
        }
    } while (true);
}

void TaskManager::markTaskCompleted() {
    printSubHeader("Mark Task as Completed");
    viewTasks();
    std::cout << "\n\t\tEnter the number of the task to mark as completed: ";
    std::ifstream inFile(getTaskFilePath());
    if (!inFile.is_open()) {
        setColor(RED);
        std::cout << "\n\t\tError: Could not open tasks file.\n";
        setColor(RESET_COLOR);
        _getch();
        return;
    }

    int totalTasks = 0;
    std::string line;
    while (getline(inFile, line)) {
        if (!line.empty()) {
            totalTasks++;
        }
    }
    inFile.close();
    
    if (totalTasks == 0) {
        _getch();
        return;
    }

    int taskNumber = getValidInt(1, totalTasks);
    
    inFile.open(getTaskFilePath());
    std::ofstream tempFile("temp_tasks.txt");
    int count = 0;
    bool found = false;
    while (getline(inFile, line)) {
        if (line.empty()) {
            tempFile << line << std::endl;
            continue;
        }
        count++;
        if (count == taskNumber) {
            size_t lastComma = line.rfind(',');
            if (lastComma != std::string::npos) {
                line.replace(lastComma + 1, 1, "1");
                found = true;
            }
        }
        tempFile << line << std::endl;
    }
    inFile.close();
    tempFile.close();
    if (found) {
        remove(getTaskFilePath().c_str());
        rename("temp_tasks.txt", getTaskFilePath().c_str());
        setColor(GREEN);
        std::cout << "\n\t\tTask marked as completed!\n";
    } else {
        remove("temp_tasks.txt");
        setColor(RED);
        std::cout << "\n\t\tTask not found or invalid number.\n";
    }
    setColor(RESET_COLOR);
    _getch();
}

void TaskManager::deleteTask() {
    printSubHeader("Delete a Task");
    viewTasks();
    std::ifstream inFile(getTaskFilePath());
    if (!inFile.is_open()) {
        setColor(RED);
        std::cout << "\n\t\tError: Could not open tasks file.\n";
        setColor(RESET_COLOR);
        _getch();
        return;
    }

    int totalTasks = 0;
    std::string line;
    while (getline(inFile, line)) {
        if (!line.empty()) {
            totalTasks++;
        }
    }
    inFile.close();
    
    if (totalTasks == 0) {
        _getch();
        return;
    }

    std::cout << "\n\t\tEnter the number of the task to delete: ";
    int taskNumber = getValidInt(1, totalTasks);
    
    inFile.open(getTaskFilePath());
    std::ofstream tempFile("temp_tasks.txt");
    int count = 0;
    bool found = false;
    while (getline(inFile, line)) {
        if (line.empty()) {
            tempFile << line << std::endl;
            continue;
        }
        count++;
        if (count == taskNumber) {
            found = true;
            continue;
        }
        tempFile << line << std::endl;
    }
    inFile.close();
    tempFile.close();
    if (found) {
        remove(getTaskFilePath().c_str());
        rename("temp_tasks.txt", getTaskFilePath().c_str());
        setColor(GREEN);
        std::cout << "\n\t\tTask deleted successfully!\n";
    } else {
        remove("temp_tasks.txt");
        setColor(RED);
        std::cout << "\n\t\tTask not found.\n";
    }
    setColor(RESET_COLOR);
    _getch();
}

void TaskManager::dailyReview() {
    printSubHeader("Daily Review & Suggestions");
    std::string reviewFile = "daily_review_" + currentUser + "_" + getCurrentDateString() + ".txt";
    std::ifstream checkReview(reviewFile);
    if (checkReview.is_open()) {
        setColor(YELLOW);
        std::cout << "\t\tYou have already completed your daily review for today. Great job!\n";
        setColor(RESET_COLOR);
        checkReview.close();
        _getch();
        return;
    }
    checkReview.close();
    std::ifstream inFile(getTaskFilePath());
    if (!inFile.is_open()) {
        std::cout << "\t\tNo tasks found to review.\n";
        _getch();
        return;
    }
    std::string line;
    int completedCount = 0;
    int pendingCount = 0;
    std::cout << "\t\t--- Your Daily Progress ---\n";
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        try {
            size_t lastComma = line.rfind(',');
            int status = std::stoi(line.substr(lastComma + 1));
            if (status == 1) {
                completedCount++;
            } else {
                pendingCount++;
            }
        } catch (const std::exception& e) {
            // Skip invalid line
        }
    }
    inFile.close();
    setColor(BOLD_GREEN);
    std::cout << "\t\tCompleted Tasks: " << completedCount << "\n";
    setColor(BOLD_RED);
    std::cout << "\t\tPending Tasks: " << pendingCount << "\n\n";
    setColor(RESET_COLOR);
    if (pendingCount > 0) {
        setColor(YELLOW);
        std::cout << "\t\t--- Smart Suggestions ---\n";
        std::cout << "\t\tYou have pending tasks. Here are some high-priority ones:\n";
        setColor(RESET_COLOR);
        std::ifstream suggestionsFile(getTaskFilePath());
        while (getline(suggestionsFile, line)) {
            if (line.empty()) continue;
            try {
                size_t firstComma = line.find(',');
                std::string title = line.substr(0, firstComma);
                line.erase(0, firstComma + 1);
                int priority = std::stoi(line.substr(0, line.find(',')));
                size_t lastComma = line.rfind(',');
                int status = std::stoi(line.substr(lastComma + 1));
                if (status == 0 && priority == 1) {
                    std::cout << "\t\t- " << title << "\n";
                }
            } catch (const std::exception& e) {
                // Skip invalid line
            }
        }
        suggestionsFile.close();
    } else {
        setColor(GREEN);
        std::cout << "\t\tGreat job! All tasks completed.\n";
        setColor(RESET_COLOR);
    }
    std::ofstream reviewFileOut(reviewFile);
    if (reviewFileOut.is_open()) {
        reviewFileOut << "completed";
        reviewFileOut.close();
    }
    _getch();
}

void TaskManager::startPomodoro() {
    printSubHeader("Pomodoro Timer");
    int workMinutes = 25;
    setColor(CYAN);
    std::cout << "\n\t\tStarting a 25-minute focus session!\n";
    std::cout << "\t\tPress any key to cancel early.\n\n";
    setColor(RESET_COLOR);
    for (int i = workMinutes * 60; i > 0; --i) {
        if (_kbhit()) {
            _getch();
            std::cout << "\n\n\t\tTimer cancelled.\n";
            _getch();
            return;
        }
        std::cout << "\r\t\tTime remaining: " << std::setw(2) << std::setfill('0') << i / 60 << "m " << std::setw(2) << std::setfill('0') << i % 60 << "s    ";
        Sleep(1000);
    }
    setColor(GREEN);
    std::cout << "\n\n\t\tTime for a 5-minute break! Great work!\n";
    Beep(523, 1000);
    setColor(RESET_COLOR);
    _getch();
}