#include "HabitTracker.h"

std::string HabitTracker::getHabitsFilePath() const {
    return "habits_" + currentUser + ".txt";
}

void HabitTracker::runMenu() {
    char choice;
    do {
        printSubHeader("Habits & Hobbies");
        std::cout << "\t\t\t1. Add a New Habit\n";
        std::cout << "\t\t\t2. View Your Habits\n";
        std::cout << "\t\t\t3. Track a Habit (Check-in)\n";
        std::cout << "\t\t\t4. Delete a Habit\n";
        setColor(YELLOW);
        std::cout << "\t\t\t5. Back to Main Menu\n";
        setColor(RESET_COLOR);
        std::cout << "\n\t\t\tEnter your choice: ";
        choice = _getch();
        switch (choice) {
            case '1': addHabit(); break;
            case '2': viewHabits(); break;
            case '3': trackHabit(); break;
            case '4': deleteHabit(); break;
            case '5': return;
            default:
                setColor(RED);
                std::cout << "\n\t\t\tInvalid choice. Please try again.\n";
                setColor(RESET_COLOR);
                _getch();
                break;
        }
    } while (true);
}

void HabitTracker::addHabit() {
    printSubHeader("Add a New Habit");
    std::string title;
    std::cout << "\t\tEnter the habit title (e.g., 'Read_for_30min'): ";
    getline(std::cin, title);
    std::ofstream outFile(getHabitsFilePath(), std::ios::app);
    if (outFile.is_open()) {
        outFile << title << ",0," << "none" << std::endl;
        outFile.close();
        setColor(GREEN);
        std::cout << "\n\t\tHabit added successfully!\n";
    } else {
        setColor(RED);
        std::cout << "\n\t\tError: Could not open habits file.\n";
    }
    setColor(RESET_COLOR);
    _getch();
}

void HabitTracker::viewHabits() {
    printSubHeader("Your Habits");
        std::ifstream inFile(getHabitsFilePath());
        if (!inFile.is_open() || inFile.peek() == EOF) {
            std::cout << "\t\tNo habits found. Add one first!\n";
            _getch();
            return;
        }
        std::string line;
        setColor(YELLOW);
        std::cout << "\t\t------------------------------------\n";
        std::cout << "\t\t      Habit      |  Current Streak\n";
        std::cout << "\t\t------------------------------------\n";
        setColor(RESET_COLOR);
        while (getline(inFile, line)) {
            if (line.empty()) continue;
            try {
                size_t comma1 = line.find(',');
                size_t comma2 = line.find(',', comma1 + 1);
                std::string title = line.substr(0, comma1);
                int streak = std::stoi(line.substr(comma1 + 1, comma2 - comma1 - 1));
                std::cout << "\t\t" << std::setw(15) << std::left << title.substr(0, 15) << " | " << streak << " days\n";
            } catch (const std::exception& e) {
                std::cout << "\t\t [Error reading habit]\n";
            }
        }
        std::cout << "\t\t------------------------------------\n";
        inFile.close();
        _getch();
}

void HabitTracker::trackHabit() {
    printSubHeader("Track a Habit");
        viewHabits();
        std::string title;
        std::cout << "\n\t\tEnter the habit title to track today: ";
        getline(std::cin, title);
        std::ifstream inFile(getHabitsFilePath());
        std::ofstream tempFile("temp_habits.txt");
        std::string line;
        bool found = false;
        while (getline(inFile, line)) {
            if (line.empty()) {
                tempFile << line << std::endl;
                continue;
            }
            size_t comma1 = line.find(',');
            std::string habitTitle = line.substr(0, comma1);
            if (habitTitle == title) {
                try {
                    size_t comma2 = line.find(',', comma1 + 1);
                    int streak = std::stoi(line.substr(comma1 + 1, comma2 - comma1 - 1));
                    std::string lastDate = line.substr(comma2 + 1);
                    std::string today = getCurrentDateString();
                    if (lastDate == today) {
                        setColor(YELLOW);
                        std::cout << "\n\t\tYou have already checked in for this habit today!\n";
                        setColor(RESET_COLOR);
                        found = true;
                        tempFile << line << std::endl;
                    } else if (lastDate == getYesterdayDateString() || lastDate == "none") {
                        streak++;
                        tempFile << habitTitle << "," << streak << "," << today << std::endl;
                        setColor(GREEN);
                        std::cout << "\n\t\tStreak updated for " << title << " to " << streak << "!\n";
                        setColor(RESET_COLOR);
                        found = true;
                    } else {
                        streak = 1;
                        tempFile << habitTitle << "," << streak << "," << today << std::endl;
                        setColor(RED);
                        std::cout << "\n\t\tStreak for " << title << " reset. New streak is 1.\n";
                        setColor(RESET_COLOR);
                        found = true;
                    }
                } catch (const std::exception& e) {
                    tempFile << line << std::endl;
                }
            } else {
                tempFile << line << std::endl;
            }
        }
        inFile.close();
        tempFile.close();
        if (found) {
            remove(getHabitsFilePath().c_str());
            rename("temp_habits.txt", getHabitsFilePath().c_str());
        } else {
            remove("temp_habits.txt");
            setColor(RED);
            std::cout << "\n\t\tHabit not found.\n";
            setColor(RESET_COLOR);
        }
        _getch();
}

void HabitTracker::deleteHabit() {
    printSubHeader("Delete a Habit");
        std::ifstream inFile(getHabitsFilePath());
        if (!inFile.is_open() || inFile.peek() == EOF) {
            std::cout << "\t\tNo habits found to delete.\n";
            _getch();
            return;
        }
        
        // Count habits to get the valid range for user input
        int totalHabits = 0;
        std::string line;
        while (getline(inFile, line)) {
            if (!line.empty()) {
                totalHabits++;
            }
        }
        inFile.close();
        
        if (totalHabits == 0) {
            _getch();
            return;
        }
        
        // Re-open and display habits with a number
        inFile.open(getHabitsFilePath());
        setColor(YELLOW);
        std::cout << "\t\t------------------------------------\n";
        std::cout << "\t\t # |      Habit      |  Current Streak\n";
        std::cout << "\t\t------------------------------------\n";
        setColor(RESET_COLOR);
        int count = 0;
        while (getline(inFile, line)) {
            if (line.empty()) continue;
            count++;
            try {
                size_t comma1 = line.find(',');
                size_t comma2 = line.find(',', comma1 + 1);
                std::string title = line.substr(0, comma1);
                int streak = std::stoi(line.substr(comma1 + 1, comma2 - comma1 - 1));
                std::cout << "\t\t " << std::setw(2) << count << " | " << std::setw(15) << std::left << title.substr(0, 15) << " | " << streak << " days\n";
            } catch (const std::exception& e) {
                 std::cout << "\t\t [Error reading habit " << count << "]\n";
            }
        }
        std::cout << "\t\t------------------------------------\n";
        inFile.close();
        
        std::cout << "\n\t\tEnter the number of the habit to delete: ";
        int habitNumber = getValidInt(1, totalHabits);

        // Delete the habit
        inFile.open(getHabitsFilePath());
        std::ofstream tempFile("temp_habits.txt");
        count = 0;
        bool found = false;
        while (getline(inFile, line)) {
            if (line.empty()) continue;
            count++;
            if (count == habitNumber) {
                found = true;
                continue;
            }
            tempFile << line << std::endl;
        }

        inFile.close();
        tempFile.close();

        if (found) {
            remove(getHabitsFilePath().c_str());
            rename("temp_habits.txt", getHabitsFilePath().c_str());
            setColor(GREEN);
            std::cout << "\n\t\tHabit deleted successfully!\n";
        } else {
            remove("temp_habits.txt");
            setColor(RED);
            std::cout << "\n\t\tInvalid habit number.\n";
        }
        setColor(RESET_COLOR);
        _getch();
}