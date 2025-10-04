#ifndef APP_H
#define APP_H

#include "TaskManager.h"
#include "FitnessTracker.h"
#include "FinanceManager.h"
#include "HabitTracker.h"
#include "WellnessManager.h"

// Application Core Class (Manages the overall flow and the collection of modules)
class App {
private:
    std::string currentUser;
    TaskManager* taskModule;
    FitnessTracker* fitnessModule;
    FinanceManager* financeModule;
    HabitTracker* habitModule;
    WellnessManager* wellnessModule;

public:
    App(const std::string& user);
    ~App();
    void showDashboard();
};

#endif