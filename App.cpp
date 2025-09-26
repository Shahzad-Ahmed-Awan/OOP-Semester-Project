#include "App.h"

App::App(const std::string& user) : currentUser(user) {
    taskModule = new TaskManager(user);
    fitnessModule = new FitnessTracker(user);
    financeModule = new FinanceManager(user);
    habitModule = new HabitTracker(user);
    wellnessModule = new WellnessManager(user);
}

App::~App() {
    delete taskModule;
    delete fitnessModule;
    delete financeModule;
    delete habitModule;
    delete wellnessModule;
}

void App::showDashboard() {
    char choice = 0;
    do {
        printHeader();
        setColor(BOLD_WHITE);
        std::cout << "\n\t\t\tWelcome, " << currentUser << "! What would you like to focus on today?\n\n";
        setColor(RESET_COLOR);
        
        setColor(BOLD_YELLOW);
        std::cout << "\t\t\t\t------------------------------------\n";
        std::cout << "\t\t\t\t    YOUR DAILY PROGRESS DASHBOARD   \n";
        std::cout << "\t\t\t\t------------------------------------\n";
        setColor(RESET_COLOR);
        
        int pendingTasks = taskModule->getPendingTaskCount();
        setColor(BOLD_CYAN);
        std::cout << "\t\t\t\t| Pending Tasks: " << std::setw(11) << std::right << pendingTasks << " |\n";
        setColor(RESET_COLOR);

        int waterIntake = fitnessModule->getTodayWaterIntake();
        setColor(BOLD_CYAN);
        std::cout << "\t\t\t\t| Water Intake : " << std::setw(11) << std::right << waterIntake << " glasses |\n";
        setColor(RESET_COLOR);
        
        double totalMonthlyExpenses = financeModule->getTotalMonthlyExpenses();
        setColor(BOLD_CYAN);
        std::cout << "\t\t\t\t| Total Expenses: " << std::setw(10) << std::right << "$" << totalMonthlyExpenses << " |\n";
        setColor(RESET_COLOR);
        
        std::cout << "\t\t\t\t------------------------------------\n\n";
        
        std::cout << "\t\t\t\t+------------------------+\n";
        std::cout << "\t\t\t\t|"; setColor(BOLD_GREEN); std::cout << " 1. Study Manager     "; setColor(RESET_COLOR); std::cout << "|\n";
        std::cout << "\t\t\t\t|"; setColor(BOLD_RED); std::cout << " 2. Fitness Tracker   "; setColor(RESET_COLOR); std::cout << "|\n";
        std::cout << "\t\t\t\t|"; setColor(BOLD_YELLOW); std::cout << " 3. Finance Hub       "; setColor(RESET_COLOR); std::cout << "|\n";
        std::cout << "\t\t\t\t|"; setColor(BOLD_CYAN); std::cout << " 4. Habits & Hobbies  "; setColor(RESET_COLOR); std::cout << "|\n";
        std::cout << "\t\t\t\t|"; setColor(BOLD_CYAN); std::cout << " 5. Mental Wellness   "; setColor(RESET_COLOR); std::cout << "|\n";
        std::cout << "\t\t\t\t|------------------------|\n";
        std::cout << "\t\t\t\t|"; setColor(YELLOW); std::cout << " 6. Logout            "; setColor(RESET_COLOR); std::cout << "|\n";
        std::cout << "\t\t\t\t|"; setColor(RED); std::cout << " 7. Exit Application  "; setColor(RESET_COLOR); std::cout << "|\n";
        std::cout << "\t\t\t\t+------------------------+\n";
        std::cout << "\n\t\t\t\tEnter your choice: ";
        choice = _getch();
        
        switch (choice) {
            case '1': taskModule->runMenu(); break;
            case '2': fitnessModule->runMenu(); break;
            case '3': financeModule->runMenu(); break;
            case '4': habitModule->runMenu(); break;
            case '5': wellnessModule->runMenu(); break;
            case '6':
                setColor(YELLOW);
                std::cout << "\n\n\t\t\t\tLogging out. See you soon!\n";
                setColor(RESET_COLOR);
                Sleep(1500);
                return;
            case '7':
                setColor(CYAN);
                std::cout << "\n\n\t\t\t\tThank you for using AuraSync! Exiting...\n\n";
                setColor(RESET_COLOR);
                Sleep(1500);
                exit(0);
            default:
                setColor(RED);
                std::cout << "\n\t\t\t\tInvalid choice. Please try again.\n";
                setColor(RESET_COLOR);
                _getch();
                break;
        }
    } while (true);
}