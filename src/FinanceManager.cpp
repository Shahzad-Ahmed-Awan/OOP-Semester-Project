#include "FinanceManager.h"

std::string FinanceManager::getExpensesFilePath() const {
    return "expenses_" + currentUser + ".txt";
}

std::string FinanceManager::getBudgetFilePath() const {
    return "budget_" + currentUser + ".txt";
}

double FinanceManager::getTotalMonthlyExpenses() const {
    std::ifstream inFile(getExpensesFilePath());
    if (!inFile.is_open()) return 0.0;
    double total = 0.0;
    std::string line;
    std::string currentMonth = getCurrentMonthAndYear();
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        try {
            size_t comma1 = line.find(',');
            size_t comma2 = line.find(',', comma1 + 1);
            double amount = std::stod(line.substr(0, comma1));
            std::string date = line.substr(comma2 + 1);
            if (date.substr(0, 7) == currentMonth) {
                total += amount;
            }
        } catch (const std::exception& e) {
            // Skip invalid lines
        }
    }
    inFile.close();
    return total;
}

void FinanceManager::runMenu() {
    char choice;
    do {
        printSubHeader("Finance Section");
        std::cout << "\t\t\t1. Add Expense\n";
        std::cout << "\t\t\t2. Set Monthly Budget\n";
        std::cout << "\t\t\t3. View Monthly Summary & Insights\n";
        std::cout << "\t\t\t4. Delete an Expense\n";
        setColor(YELLOW);
        std::cout << "\t\t\t5. Back to Main Menu\n";
        setColor(RESET_COLOR);
        std::cout << "\n\t\t\tEnter your choice: ";
        choice = _getch();
        switch (choice) {
            case '1': addExpense(); break;
            case '2': setBudget(); break;
            case '3': viewSummary(); break;
            case '4': deleteExpense(); break;
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

void FinanceManager::addExpense() {
    printSubHeader("Add a New Expense");
    double amount;
    std::string category;
    std::string date;
    
    // Input validation for amount
    while (true) {
        std::cout << "\t\tEnter expense amount ($): ";
        std::string amountStr;
        std::cin >> amountStr;
        std::stringstream ss(amountStr);
        if (ss >> amount && amount > 0) {
            break;
        } else {
            setColor(RED);
            std::cout << "\n\t\tInvalid input. Please enter a positive number.\n";
            setColor(RESET_COLOR);
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "\t\tEnter expense category (e.g., Food_Transport): ";
    std::cin >> category;
    date = getCurrentDateString();
    std::ofstream outFile(getExpensesFilePath(), std::ios::app);
    if (outFile.is_open()) {
        outFile << std::fixed << std::setprecision(2) << amount << "," << category << "," << date << std::endl;
        outFile.close();
        setColor(GREEN);
        std::cout << "\n\t\tExpense added successfully!\n";
    } else {
        setColor(RED);
        std::cout << "\n\t\tError: Could not open expenses file.\n";
    }
    setColor(RESET_COLOR);
    _getch();
}

void FinanceManager::setBudget() {
    printSubHeader("Set Your Monthly Budget");
    double budget;
    std::cout << "\t\tEnter your monthly budget: $";
    while(!(std::cin >> budget) || budget <= 0) {
        setColor(RED);
        std::cout << "\n\t\tInvalid input. Please enter a positive number: $";
        setColor(RESET_COLOR);
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::ofstream outFile(getBudgetFilePath());
    if (outFile.is_open()) {
        outFile << budget << std::endl;
        outFile.close();
        setColor(GREEN);
        std::cout << "\n\t\tMonthly budget of $" << budget << " set successfully!\n";
    } else {
        setColor(RED);
        std::cout << "\n\t\tError: Could not open budget file.\n";
    }
    setColor(RESET_COLOR);
    _getch();
}

void FinanceManager::viewSummary() {
    printSubHeader("Monthly Expense Summary & Insights");
    
    // C++ vanilla approach: fixed-size array of structs instead of a map
    const int MAX_CATEGORIES = 100; // Define a reasonable maximum
    struct CategorySummary {
        std::string category;
        double total = 0.0;
    };
    CategorySummary categoryTotals[MAX_CATEGORIES];
    int numCategories = 0;

    std::ifstream inFile(getExpensesFilePath());
    if (inFile.is_open()) {
        std::string line;
        std::string currentMonth = getCurrentMonthAndYear();
        while (getline(inFile, line)) {
            if (line.empty()) continue;
            try {
                size_t comma1 = line.find(',');
                size_t comma2 = line.find(',', comma1 + 1);
                double amount = stod(line.substr(0, comma1));
                std::string category = line.substr(comma1 + 1, comma2 - comma1 - 1);
                std::string date = line.substr(comma2 + 1);
                if (date.substr(0, 7) == currentMonth) {
                    bool found = false;
                    for (int i = 0; i < numCategories; ++i) {
                        if (categoryTotals[i].category == category) {
                            categoryTotals[i].total += amount;
                            found = true;
                            break;
                        }
                    }
                    if (!found && numCategories < MAX_CATEGORIES) {
                        categoryTotals[numCategories].category = category;
                        categoryTotals[numCategories].total = amount;
                        numCategories++;
                    }
                }
            } catch (...) {
                continue;
            }
        }
        inFile.close();
    }

    if (numCategories == 0) {
        std::cout << "\t\tNo expenses logged for this month yet.\n";
        _getch();
        return;
    }

    double total = 0;
    std::cout << "\t\t--- Category-wise Insights (This Month) ---\n";
    for (int i = 0; i < numCategories; ++i) {
        total += categoryTotals[i].total;
        std::cout << "\t\t" << categoryTotals[i].category << ": $" << categoryTotals[i].total << std::endl;
    }
    
    std::cout << "\t\t--------------------------------------\n";
    setColor(BOLD_CYAN);
    std::cout << "\t\tTotal Expenses (This Month): $" << total << std::endl;
    double monthlyBudget = 0;
    std::ifstream budgetFile(getBudgetFilePath());
    if (budgetFile.is_open()) {
        budgetFile >> monthlyBudget;
        budgetFile.close();
    }
    if (monthlyBudget > 0) {
        std::cout << "\t\tMonthly Budget: $" << monthlyBudget << std::endl;
        if (total > monthlyBudget) {
            setColor(BOLD_RED);
            std::cout << "\t\tStatus: You are OVER budget by $" << total - monthlyBudget << "!\n";
        } else {
            setColor(BOLD_GREEN);
            std::cout << "\t\tStatus: You are UNDER budget by $" << monthlyBudget - total << "!\n";
        }
    }
    setColor(RESET_COLOR);
    _getch();
}

void FinanceManager::deleteExpense() {
    printSubHeader("Delete an Expense");
    std::ifstream inFile(getExpensesFilePath());
    if (!inFile.is_open() || inFile.peek() == EOF) {
        std::cout << "\t\tNo expenses found to delete.\n";
        _getch();
        return;
    }
    inFile.close();

    // Display expenses to the user
    int count = 0;
    std::string line;
    inFile.open(getExpensesFilePath());
    setColor(YELLOW);
    std::cout << "\t\t------------------------------------------------\n";
    std::cout << "\t\t # |      Amount      | Category       | Date\n";
    std::cout << "\t\t------------------------------------------------\n";
    setColor(RESET_COLOR);
    while(getline(inFile, line)) {
        if (line.empty()) continue;
        count++;
        try {
            size_t comma1 = line.find(',');
            size_t comma2 = line.find(',', comma1 + 1);
            std::string amountStr = line.substr(0, comma1);
            std::string category = line.substr(comma1 + 1, comma2 - comma1 - 1);
            std::string date = line.substr(comma2 + 1);
            std::cout << "\t\t " << std::setw(2) << count << " | " << std::setw(15) << std::left << amountStr << "| " << std::setw(15) << std::left << category << "| " << date << std::endl;
        } catch (const std::exception& e) {
             std::cout << "\t\t [Error reading expense " << count << "]\n";
        }
    }
    inFile.close();
    std::cout << "\t\t------------------------------------------------\n";

    std::ifstream inFileCheck(getExpensesFilePath());
    int totalExpenses = 0;
    while (getline(inFileCheck, line)) {
        if (!line.empty()) {
            totalExpenses++;
        }
    }
    inFileCheck.close();
    if (totalExpenses == 0) {
        _getch();
        return;
    }

    std::cout << "\n\t\tEnter the number of the expense to delete: ";
    int expenseNumber = getValidInt(1, totalExpenses);
    
    std::ifstream inFile2(getExpensesFilePath());
    std::ofstream tempFile("temp_expenses.txt");
    if (!inFile2.is_open() || !tempFile.is_open()) {
        setColor(RED);
        std::cout << "\n\t\tError opening files.\n";
        setColor(RESET_COLOR);
        _getch();
        return;
    }
    
    count = 0;
    bool found = false;
    while(getline(inFile2, line)) {
        if (line.empty()) continue;
        count++;
        if (count == expenseNumber) {
            found = true;
            continue;
        }
        tempFile << line << std::endl;
    }

    inFile2.close();
    tempFile.close();

    if (found) {
        remove(getExpensesFilePath().c_str());
        rename("temp_expenses.txt", getExpensesFilePath().c_str());
        setColor(GREEN);
        std::cout << "\n\t\tExpense deleted successfully!\n";
    } else {
        remove("temp_expenses.txt");
        setColor(RED);
        std::cout << "\n\t\tInvalid expense number.\n";
    }
    setColor(RESET_COLOR);
    _getch();
}