#include "User.h"

std::string User::cipher(const std::string& text) {
    std::string result = text;
    for (char& c : result) {
        c += 5;
    }
    return result;
}

void User::registerUser() {
    printSubHeader("User Registration");
    std::cout << "\t\tEnter Username: ";
    std::cin >> username;
    std::ifstream userFile("users.txt");
    std::string line;
    bool exists = false;
    while (getline(userFile, line)) {
        if (line.substr(0, line.find(',')) == username) {
            exists = true;
            break;
        }
    }
    userFile.close();
    if (exists) {
        setColor(RED);
        std::cout << "\n\t\tUsername already taken. Please try another.\n";
        setColor(RESET_COLOR);
        Sleep(2000);
        return;
    }
    std::cout << "\t\tEnter Password: ";
    std::cin >> password;
    std::cout << "\t\tEnter Email: ";
    std::cin >> email;
    std::ofstream outFile("users.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << username << "," << cipher(password) << "," << email << std::endl;
        outFile.close();
        setColor(GREEN);
        std::cout << "\n\t\tRegistration successful! Press any key to continue...\n";
        setColor(RESET_COLOR);
        _getch();
    } else {
        setColor(RED);
        std::cout << "\n\t\tError: Could not open users file.\n";
        setColor(RESET_COLOR);
    }
}

std::string User::loginUser() {
    while (true) {
        printSubHeader("User Login");
        std::cout << "\t\tEnter Username (or type 'back' to return): ";
        std::cin >> username;
        if (username == "back") return "";
        std::cout << "\t\tEnter Password: ";
        std::cin >> password;
        std::ifstream userFile("users.txt");
        std::string line;
        bool found = false;
        if (userFile.is_open()) {
            while (getline(userFile, line)) {
                std::string storedUser = line.substr(0, line.find(','));
                std::string storedPass = line.substr(line.find(',') + 1, line.rfind(',') - line.find(',') - 1);
                if (storedUser == username && storedPass == cipher(password)) {
                    found = true;
                    break;
                }
            }
            userFile.close();
        }
        if (found) {
            setColor(GREEN);
            std::cout << "\n\t\tLogin successful! Welcome, " << username << "!\n";
            setColor(RESET_COLOR);
            Sleep(1500);
            return username;
        } else {
            setColor(RED);
            std::cout << "\n\t\tInvalid username or password. Press any key to try again...\n";
            setColor(RESET_COLOR);
            _getch();
            clearScreen();
        }
    }
}