#ifndef EXPENSE_LOGIC_H
#define EXPENSE_LOGIC_H

#include "expense.h"
#include <vector>
#include <string>

using namespace std;

extern vector<Expense> allExpenses;
extern vector<User> allUsers;
extern User currentUser;

bool addExpense(const string& category, double amount, const string& date, const string& description);
bool deleteExpense(int id);
bool editExpense(int id, const string& newCategory, double newAmount, const string& newDescription);
Expense* findExpenseById(int id);
double getTotalForCategory(const string& category);
double getTotalExpense();
vector<Expense>& getExpenses();
void setExpenses(const vector<Expense>& expenses);
void clearExpenses();
int generateNextId();

bool registerUser(const string& username, const string& password);
bool loginUser(const string& username, const string& password);
bool isUserLoggedIn();
void logoutUser();
User* findUserByUsername(const string& username);
bool validatePassword(const string& password);
bool validateUsername(const string& username);

#endif