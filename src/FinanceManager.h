#ifndef FINANCEMANAGER_H
#define FINANCEMANAGER_H

#include "Module.h"

//*******************************************************************************************************************
                                                  //  Finance and calculation Class
//********************************************************************************************************************
class FinanceManager : public Module {
private:
    std::string getExpensesFilePath() const;
    std::string getBudgetFilePath() const;

public:
    FinanceManager(const std::string& user) : Module(user) {}

    double getTotalMonthlyExpenses() const;
    void runMenu() override;

private:
    void addExpense();
    void setBudget();
    void viewSummary();
    void deleteExpense();
};

#endif