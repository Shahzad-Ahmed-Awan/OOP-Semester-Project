#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "Module.h"

//*******************************************************************************************************************
                                                  //  study and task Management Class
//********************************************************************************************************************

class TaskManager : public Module {
private:
    std::string getTaskFilePath() const;

public:
    TaskManager(const std::string& user) : Module(user) {}

    int getPendingTaskCount() const;
    void addTask();
    void viewTasks();
    
    // The `runMenu()` method now encapsulates all task-related menu logic
    void runMenu() override;

private:
    void markTaskCompleted();
    void deleteTask();
    void dailyReview();
    void startPomodoro();
};

#endif