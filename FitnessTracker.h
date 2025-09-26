#ifndef FITNESSTRACKER_H
#define FITNESSTRACKER_H

#include "Module.h"

class FitnessTracker : public Module {
private:
    std::string getWaterFilePath() const;

public:
    FitnessTracker(const std::string& user) : Module(user) {}

    int getTodayWaterIntake() const;
    void runMenu() override;

private:
    void calculateBMI();
    void setFitnessGoal();
    void provideNutritionSuggestions();
    void trackWater();
};

#endif