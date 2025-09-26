#include "User.h"
#include "App.h"

//*******************************************************************************************************************
                                                  //  Main function Stimulation and Logics
//********************************************************************************************************************
// --- Main Function ---
int main() {
    User user;
    std::string loggedInUser;
    
    createFileIfNotExists("users.txt");
    createFileIfNotExists("quotes.txt");
    createFileIfNotExists("exercises.txt");
    createFileIfNotExists("quiz_questions.txt");
    
    std::ofstream quotesFile("quotes.txt", std::ios::app);
    if (quotesFile.is_open() && quotesFile.tellp() == 0) {
        quotesFile << "The only way to do great work is to love what you do." << std::endl;
        quotesFile << "The future belongs to those who believe in the beauty of their dreams." << std::endl;
        quotesFile << "Believe you can and you're halfway there." << std::endl;
        quotesFile.close();
    }
    std::ofstream exercisesFile("exercises.txt", std::ios::app);
    if (exercisesFile.is_open() && exercisesFile.tellp() == 0) {
        exercisesFile << "Try to name five things you can see, hear, and feel right now." << std::endl;
        exercisesFile << "Solve a simple brain teaser puzzle online." << std::endl;
        exercisesFile << "Write a short paragraph about your favorite memory from this week." << std::endl;
        exercisesFile.close();
    }
    std::ofstream quizFile("quiz_questions.txt", std::ios::in);
    if (quizFile.is_open() && quizFile.tellp() == 0) {
        quizFile << "What_is_the_capital_of_France?,Paris,London,Berlin,Rome" << std::endl;
        quizFile << "What_is_2+2?,4,3,5,6" << std::endl;
        quizFile << "What_is_the_largest_ocean?,Pacific_Ocean,Atlantic_Ocean,Indian_Ocean,Arctic_Ocean" << std::endl;
        quizFile << "What_is_the_color_of_the_sky_on_a_clear_day?,Blue,Green,Red,Yellow" << std::endl;
        quizFile.close();
    }
    
    while (true) {
        printHeader();
        std::cout << "\n\t\t\t\t\t1. Login\n";
        std::cout << "\t\t\t\t\t2. Register\n";
        std::cout << "\t\t\t\t\t3. Exit\n";
        std::cout << "\n\t\t\t\t\tEnter your choice: ";
        char choice = _getch();
        
        switch (choice) {
            case '1':
                loggedInUser = user.loginUser();
                if (!loggedInUser.empty()) {
                    App myApp(loggedInUser);
                    myApp.showDashboard();
                }
                break;
            case '2':
                user.registerUser();
                break;
            case '3':
                setColor(CYAN);
                std::cout << "\n\n\t\t\t\tThank you for using Wellvish!\n\n";
                setColor(RESET_COLOR);
                return 0;
            default:
                setColor(RED);
                std::cout << "\n\t\t\t\tInvalid choice. Please try again.\n";
                setColor(RESET_COLOR);
                _getch();
                break;
        }
    }
    return 0;
}