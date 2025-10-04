#include "WellnessManager.h"

void WellnessManager::runMenu() {
    char choice;
    do {
        printSubHeader("Mental Wellness");
        std::cout << "\t\t\t1. Get a Motivational Quote\n";
        std::cout << "\t\t\t2. Get a Mind Exercise\n";
        std::cout << "\t\t\t3. Take a Quiz\n"; // New option for the quiz
        setColor(YELLOW);
        std::cout << "\t\t\t4. Back to Main Menu\n";
        setColor(RESET_COLOR);
        std::cout << "\n\t\t\tEnter your choice: ";
        choice = _getch();
        switch (choice) {
            case '1': showQuote(); break;
            case '2': showMindExercise(); break;
            case '3': takeQuiz(); break; // Call the new quiz function
            case '4': return;
            default:
                setColor(RED);
                std::cout << "\n\t\t\tInvalid choice. Please try again.\n";
                setColor(RESET_COLOR);
                _getch();
                break;
        }
    } while (true);
}

void WellnessManager::showQuote() {
    printSubHeader("Daily Motivational Quote");
    std::ifstream quoteFile("quotes.txt");
    if (!quoteFile.is_open() || quoteFile.peek() == EOF) {
        std::cout << "\t\tCould not find 'quotes.txt' or it is empty.\n";
        _getch();
        return;
    }

    // Count lines to pick a random one
    int lineCount = 0;
    std::string line;
    while (getline(quoteFile, line)) {
        if (!line.empty()) {
            lineCount++;
        }
    }
    quoteFile.clear();
    quoteFile.seekg(0);

    if (lineCount > 0) {
        srand(time(0));
        int randomIndex = rand() % lineCount;
        for (int i = 0; i < randomIndex; ++i) {
            getline(quoteFile, line);
        }
        getline(quoteFile, line);
        setColor(CYAN);
        std::cout << "\n\t\t\"" << line << "\"\n";
        setColor(RESET_COLOR);
    } else {
        std::cout << "\n\t\tNo quotes found in the file.\n";
    }
    quoteFile.close();
    _getch();
}

void WellnessManager::showMindExercise() {
    printSubHeader("Quick Mind Exercise");
    std::ifstream exerciseFile("exercises.txt");
    if (!exerciseFile.is_open() || exerciseFile.peek() == EOF) {
        std::cout << "\t\tCould not find 'exercises.txt' or it is empty.\n";
        _getch();
        return;
    }
    
    // Count lines to pick a random one
    int lineCount = 0;
    std::string line;
    while (getline(exerciseFile, line)) {
        if (!line.empty()) {
            lineCount++;
        }
    }
    exerciseFile.clear();
    exerciseFile.seekg(0);

    if (lineCount > 0) {
        srand(time(0));
        int randomIndex = rand() % lineCount;
        for (int i = 0; i < randomIndex; ++i) {
            getline(exerciseFile, line);
        }
        getline(exerciseFile, line);
        setColor(GREEN);
        std::cout << "\n\t\tYour challenge: " << line << "\n";
        setColor(RESET_COLOR);
    } else {
        std::cout << "\n\t\tNo exercises found in the file.\n";
    }
    exerciseFile.close();
    _getch();
}

void WellnessManager::takeQuiz() {
    printSubHeader("Mental Wellness Quiz");
    std::ifstream quizFile("quiz_questions.txt");
    if (!quizFile.is_open() || quizFile.peek() == EOF) {
        setColor(RED);
        std::cout << "\n\t\tQuiz file not found or is empty. Please add questions to 'quiz_questions.txt'.\n";
        setColor(RESET_COLOR);
        _getch();
        return;
    }

    int totalQuestions = 0;
    std::string line;
    while(getline(quizFile, line)) {
        if (!line.empty()) {
            totalQuestions++;
        }
    }
    quizFile.close();

    if (totalQuestions == 0) {
        setColor(RED);
        std::cout << "\n\t\tNo questions found in the quiz file.\n";
        setColor(RESET_COLOR);
        _getch();
        return;
    }

    std::cout << "\t\tThe quiz has a total of " << totalQuestions << " questions.\n";
    std::cout << "\t\tHow many questions would you like to take? ";
    int numQuestions = getValidInt(1, totalQuestions);

    int score = 0;
    int questionsAsked = 0;
    srand(time(0));

    for (int i = 0; i < numQuestions; ++i) {
        // Re-open and reset file pointer for each question to simulate random access
        quizFile.open("quiz_questions.txt");
        if (!quizFile.is_open()) {
            setColor(RED);
            std::cout << "\n\t\tError: Could not open quiz file.\n";
            setColor(RESET_COLOR);
            return;
        }
        
        int randomLine = rand() % totalQuestions;
        for (int j = 0; j < randomLine; ++j) {
            getline(quizFile, line);
        }
        getline(quizFile, line);
        quizFile.close();
        
        if (line.empty()) {
            continue;
        }

        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);
        size_t pos4 = line.find(',', pos3 + 1);

        std::string question = line.substr(0, pos1);
        std::string correctAnswer = line.substr(pos1 + 1, pos2 - pos1 - 1);
        std::string optionB = line.substr(pos2 + 1, pos3 - pos2 - 1);
        std::string optionC = line.substr(pos3 + 1, pos4 - pos3 - 1);
        std::string optionD = line.substr(pos4 + 1);
        
        std::string shuffledOptions[4] = {correctAnswer, optionB, optionC, optionD};
        for (int k = 0; k < 4; ++k) {
            int swapIndex = rand() % 4;
            std::string temp = shuffledOptions[k];
            shuffledOptions[k] = shuffledOptions[swapIndex];
            shuffledOptions[swapIndex] = temp;
        }

        questionsAsked++;
        printSubHeader("Question " + std::to_string(questionsAsked));
        std::cout << "\t\t" << question << "\n\n";
        std::cout << "\t\t1. " << shuffledOptions[0] << "\n";
        std::cout << "\t\t2. " << shuffledOptions[1] << "\n";
        std::cout << "\t\t3. " << shuffledOptions[2] << "\n";
        std::cout << "\t\t4. " << shuffledOptions[3] << "\n\n";
        
        std::cout << "\t\tEnter your choice (1-4): ";
        int userChoice = getValidInt(1, 4);
        
        if (shuffledOptions[userChoice - 1] == correctAnswer) {
            setColor(GREEN);
            std::cout << "\n\t\tCorrect!\n";
            score++;
        } else {
            setColor(RED);
            std::cout << "\n\t\tIncorrect. The correct answer was: " << correctAnswer << "\n";
        }
        setColor(RESET_COLOR);
        _getch();
    }

    printSubHeader("Quiz Results");
    setColor(BOLD_YELLOW);
    std::cout << "\n\t\tYou scored " << score << " out of " << questionsAsked << "!\n";
    setColor(RESET_COLOR);
    if (score == questionsAsked) {
        setColor(BOLD_GREEN);
        std::cout << "\t\tPerfect score! You are a genius!\n";
        setColor(RESET_COLOR);
    } else if (score > questionsAsked / 2) {
        setColor(CYAN);
        std::cout << "\t\tGreat job! Keep up the good work.\n";
        setColor(RESET_COLOR);
    } else {
        setColor(BOLD_RED);
        std::cout << "\t\tYou can do better next time. Keep practicing!\n";
        setColor(RESET_COLOR);
    }
    _getch();
}