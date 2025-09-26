#ifndef HABITTRACKER_H
#define HABITTRACKER_H

#include "Module.h"

//*******************************************************************************************************************
                                                  //  Habit Tracking Class
//********************************************************************************************************************

class HabitTracker : public Module {
private:
    std::string getHabitsFilePath() const;

public:
    HabitTracker(const std::string& user) : Module(user) {}

    void runMenu() override;

private:
    void addHabit();
    void viewHabits();
    void trackHabit();
    void deleteHabit();
};

#endif