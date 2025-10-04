#include "Utils.h"

// Global handle for console manipulation
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// --- Utility and UI Functions ---
// Encapsulating low-level UI functions
void setColor(int color) {
    SetConsoleTextAttribute(hConsole, color);
}

void clearScreen() {
    system("cls");
}

void printHeader() {
    clearScreen();
  setColor(BOLD_YELLOW);
    std::cout << "\n\n";
    std::cout << "\t\t\t\t __      __     .__ .__           .__        \n";
    std::cout << "\t\t\t\t/  \\    /  \\  ____ |  | |  |   ___  __ |__| ______        \n";
    setColor(BOLD_CYAN);
    std::cout << "\t\t\t\t\\  \\/\\/  \\/ / __ \\|  | |  |   \\  \\/ / |  |/  ___/   \n";
    std::cout << "\t\t\t\t \\        / \\  ___/|  |_|  |__  \\  \\/  |  |\\___ \\      \n";
    setColor(BOLD_YELLOW);
    std::cout << "\t\t\t\t  \\__/\\  /    \\___  >____/____/    \\_/   |__/____  >      \n";
    std::cout << "\t\t\t\t      \\/      \\/                             \\/      \n";
    setColor(YELLOW);
    std::cout << "\t\t\t\t-----------------------------------------------------------\n";
    std::cout << "\t\t\t\t      Your Personal Productivity & Lifestyle Hub\n";
    std::cout << "\t\t\t\t-----------------------------------------------------------\n\n";
    setColor(RESET_COLOR);
}

void printSubHeader(const std::string& title) {
    printHeader();
    setColor(BOLD_YELLOW);
    std::cout << "\n\t\t\t\t<<<<<<<<<<<<<< " << title << " >>>>>>>>>>>>>>\n\n";
    setColor(RESET_COLOR);
}

void createFileIfNotExists(const std::string& filename) {
    std::ofstream file(filename, std::ios::app);
    file.close();
}

std::string getCurrentDateString() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    std::stringstream ss;
    ss << 1900 + ltm->tm_year << "-" << std::setw(2) << std::setfill('0') << 1 + ltm->tm_mon << "-" << std::setw(2) << std::setfill('0') << ltm->tm_mday;
    return ss.str();
}

std::string getCurrentMonthAndYear() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    std::stringstream ss;
    ss << 1900 + ltm->tm_year << "-" << std::setw(2) << std::setfill('0') << 1 + ltm->tm_mon;
    return ss.str();
}

std::string getYesterdayDateString() {
    time_t now = time(0);
    now -= 24 * 60 * 60;
    tm *ltm = localtime(&now);
    std::stringstream ss;
    ss << 1900 + ltm->tm_year << "-" << std::setw(2) << std::setfill('0') << 1 + ltm->tm_mon << "-" << std::setw(2) << std::setfill('0') << ltm->tm_mday;
    return ss.str();
}

// Function to safely get a validated integer input
int getValidInt(int min, int max) {
    int value;
    while (true) {
        if (std::cin >> value && value >= min && value <= max) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "\t\tInvalid input. Please enter a number between " << min << " and " << max << ": ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}