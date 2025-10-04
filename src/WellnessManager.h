#ifndef WELLNESSMANAGER_H
#define WELLNESSMANAGER_H

#include "Module.h"

//*******************************************************************************************************************
                                                  //  Mental Wellness Class
//********************************************************************************************************************
class WellnessManager : public Module {
public:
    WellnessManager(const std::string& user) : Module(user) {}

    void runMenu() override;

private:
    void showQuote();
    void showMindExercise();
    void takeQuiz();
};

#endif