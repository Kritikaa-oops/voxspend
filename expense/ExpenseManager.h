#ifndef EXPENSE_MANAGER_H
#define EXPENSE_MANAGER_H

#include "../expense.h"
#include <vector>
#include <string>

using namespace std;

extern vector<Expense> g_expenses;
extern int g_nextId;
extern string g_lastExpenseError;

// ============ ADD EXPENSE FUNCTIONS ============
bool addExpense(const string& title, double amount, const string& category, const string& date, const string& note);
string getLastExpenseError();
void clearExpenseError();

#endif