#ifndef ADD_EXPENSE_MANAGER_H
#define ADD_EXPENSE_MANAGER_H

#include "../expense.h"
#include <vector>
#include <string>

using namespace std;

class AddExpenseManager {
private:
    vector<Expense> m_expenses;
    int m_nextId;
    string m_lastError;
    
public:
    AddExpenseManager();
    
    // ============ ADD EXPENSE (AddExpense.qml) ============
    bool addExpense(const string& category, double amount, const string& date, const string& description);
    
    // ============ VALIDATION ============
    bool validateExpenseInput(const string& category, double amount, const string& date);
    bool isValidCategory(const string& category) const;
    bool isValidDate(const string& date) const;
    
    // ============ HELPERS ============
    string getErrorMessage() const;
    void clearErrorMessage();
    void clearAllExpenses();
    
    // ============ GETTERS ============
    const vector<Expense>& getExpenses() const;
    int getExpenseCount() const;
    
private:
    int generateNextId();
};

#endif