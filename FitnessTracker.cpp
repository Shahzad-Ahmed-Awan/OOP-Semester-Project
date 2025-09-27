#include "FitnessTracker.h"

std::string FitnessTracker::getWaterFilePath() const {
    return "water_" + currentUser + ".txt";
}

int FitnessTracker::getTodayWaterIntake() const {
    std::ifstream inFile(getWaterFilePath());
    if (!inFile.is_open()) return 0;
    std::string line;
    int intake = 0;
    std::string todayDate = getCurrentDateString();
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        size_t commaPos = line.find(',');
        if (commaPos == std::string::npos) continue;
        std::string fileDate = line.substr(0, commaPos);
        if (fileDate == todayDate) {
            try {
                intake = std::stoi(line.substr(commaPos + 1));
            } catch (const std::exception& e) {
                intake = 0;
            }
            break;
        }
    }
    inFile.close();
    return intake;
}

void FitnessTracker::runMenu() {
    char choice;
    do {
        printSubHeader("Fitness Section");
        std::cout << "\t\t\t1. BMI Calculator\n";
        std::cout << "\t\t\t2. Set Fitness Goal\n";
        std::cout << "\t\t\t3. Provide Nutrition Suggestions\n";
        std::cout << "\t\t\t4. Water Intake Tracker\n";
        setColor(YELLOW);
        std::cout << "\t\t\t5. Back to Main Menu\n";
        setColor(RESET_COLOR);
        std::cout << "\n\t\t\tEnter your choice: ";
        choice = _getch();
        switch (choice) {
            case '1': calculateBMI(); break;
            case '2': setFitnessGoal(); break;
            case '3': provideNutritionSuggestions(); break;
            case '4': trackWater(); break;
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

void FitnessTracker::calculateBMI() {
    printSubHeader("BMI Calculator");
    float height, weight;
    std::cout << "\t\tEnter your height in meters (e.g., 1.75): ";
    while(!(std::cin >> height) || height <= 0) {
        setColor(RED);
        std::cout << "\n\t\tInvalid input. Please enter a positive number: ";
        setColor(RESET_COLOR);
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "\t\tEnter your weight in kilograms (e.g., 70): ";
    while(!(std::cin >> weight) || weight <= 0) {
        setColor(RED);
        std::cout << "\n\t\tInvalid input. Please enter a positive number: ";
        setColor(RESET_COLOR);
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    float bmi = weight / (height * height);
    std::cout << "\n\t\tYour BMI is: " << bmi << std::endl;
    setColor(BOLD_YELLOW);
    std::cout << "\t\tCategory: ";
    if (bmi < 18.5) std::cout << "Underweight\n";
    else if (bmi >= 18.5 && bmi < 24.9) std::cout << "Normal weight\n";
    else if (bmi >= 25 && bmi < 29.9) std::cout << "Overweight\n";
    else std::cout << "Obesity\n";
    setColor(RESET_COLOR);
    _getch();
}

void FitnessTracker::setFitnessGoal() {
    printSubHeader("Fitness Goal Setting");
    std::string goal;
    std::cout << "\t\tWhat is your fitness goal?\n";
    std::cout << "\t\t1. Bulk (Gain muscle)\n";
    std::cout << "\t\t2. Cut (Lose fat)\n";
    std::cout << "\t\t3. Maintain (Stay at current weight)\n";
    std::cout << "\t\tEnter your choice (1-3): ";
    int choice = getValidInt(1, 3);
    switch (choice) {
        case 1: goal = "Bulk"; break;
        case 2: goal = "Cut"; break;
        case 3: goal = "Maintain"; break;
        default: goal = "Unspecified"; break;
    }
    std::ofstream goalFile("fitness_goals_" + currentUser + ".txt");
    if (goalFile.is_open()) {
        goalFile << goal << std::endl;
        goalFile.close();
        setColor(GREEN);
        std::cout << "\n\t\tYour goal has been set to: " << goal << "\n";
        setColor(RESET_COLOR);
    } else {
        setColor(RED);
        std::cout << "\n\t\tError: Could not open goals file.\n";
        setColor(RESET_COLOR);
    }
    _getch();
}

void FitnessTracker::provideNutritionSuggestions() {
    printSubHeader("Nutrition Suggestions");
    std::ifstream goalFile("fitness_goals_" + currentUser + ".txt");
    if (!goalFile.is_open() || goalFile.peek() == EOF) {
        std::cout << "\t\tPlease set a fitness goal first.\n";
        _getch();
        return;
    }
    std::string goal;
    getline(goalFile, goal);
    goalFile.close();
    setColor(CYAN);
    std::cout << "\t\tBased on your goal to " << goal << ", here are some general tips:\n\n";
    setColor(RESET_COLOR);
    if (goal == "Bulk") {
        std::cout << "\t\t- Calorie intake: 2500-3000 calories/day\n";
        std::cout << "\t\t- Focus on protein and complex carbs.\n";
        std::cout << "\t\t- Suggested foods: Chicken breast, brown rice, nuts, protein shakes.\n";
    } else if (goal == "Cut") {
        std::cout << "\t\t- Calorie intake: 1500-2000 calories/day\n";
        std::cout << "\t\t- Focus on lean protein and vegetables.\n";
        std::cout << "\t\t- Suggested foods: Fish, salads, lean beef, quinoa.\n";
    } else if (goal == "Maintain") {
        std::cout << "\t\t- Calorie intake: 2000-2500 calories/day\n";
        std::cout << "\t\t- Maintain a balanced diet of all food groups.\n";
        std::cout << "\t\t- Suggested foods: Whole grains, fruits, vegetables, lean meats.\n";
    } else {
        std::cout << "\t\t- No specific suggestions available for your goal.\n";
    }
    _getch();
}

void FitnessTracker::trackWater() {
    printSubHeader("Water Intake Tracker");
    int glasses;
    std::cout << "\t\tHow many glasses of water did you drink today? ";
    glasses = getValidInt(0, 100);
    std::ofstream outFile(getWaterFilePath(), std::ios::out);
    if (outFile.is_open()) {
        outFile << getCurrentDateString() << "," << glasses << std::endl;
        outFile.close();
    }
    setColor(GREEN);
    std::cout << "\n\t\tGreat job staying hydrated! Logged " << glasses << " glasses.\n";
    if (glasses < 8) {
        setColor(YELLOW);
        std::cout << "\t\tReminder: Try to drink at least 8 glasses a day!\n";
    }
    setColor(RESET_COLOR);
    _getch();
}