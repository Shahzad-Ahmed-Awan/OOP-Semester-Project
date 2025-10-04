#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>   // For _getch()
#include <windows.h> // For colors and Sleep()
#include <ctime>     // For time-related functions
#include <cstdlib>   // For exit(), rand(), srand()
#include <iomanip>   // For std::setw
#include <sstream>   // For string streams
#include <limits>    // For numeric_limits

// Define color codes for console text
#define RESET_COLOR 7
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define YELLOW 6
#define BOLD_WHITE 15
#define BOLD_CYAN 11
#define BOLD_GREEN 10
#define BOLD_RED 12
#define BOLD_YELLOW 14

// Global handle for console manipulation
extern HANDLE hConsole;

// --- Utility and UI Functions ---
// Encapsulating low-level UI functions
void setColor(int color);
void clearScreen();
void printHeader();
void printSubHeader(const std::string& title);
void createFileIfNotExists(const std::string& filename);
std::string getCurrentDateString();
std::string getCurrentMonthAndYear();
std::string getYesterdayDateString();
int getValidInt(int min, int max);

// --- Data Structures ---
struct Date {
    int day, month, year;
};

#endif