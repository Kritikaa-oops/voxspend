#include "BackendManager.h"
#include <iostream>

// ============ GLOBAL INSTANCES ============
AuthManager g_authManager;
AddExpenseManager g_addExpenseManager;
DashboardManager g_dashboardManager;

// ============================================================
// AUTHENTICATION FUNCTIONS (login.qml, logout.qml, signup.qml)
// ============================================================

bool loginUser(const string& email, const string& password) {
    return g_authManager.loginUser(email, password);
}

void logoutUser() {
    g_authManager.logoutUser();
}

bool registerUser(const string& email, const string& password, const string& name) {
    return g_authManager.registerUser(email, password, name);
}

string getCurrentUserName() {
    return g_authManager.getCurrentUserName();
}

string getCurrentUserEmail() {
    return g_authManager.getCurrentUserEmail();
}

bool isUserLoggedIn() {
    return g_authManager.isUserLoggedIn();
}

// ============================================================
// ADD EXPENSE FUNCTIONS (AddExpense.qml)
// ============================================================

bool addExpense(const string& category, double amount, const string& date, const string& description) {
    return g_addExpenseManager.addExpense(category, amount, date, description);
}

string getLastExpenseError() {
    return g_addExpenseManager.getErrorMessage();
}

void clearExpenseError() {
    g_addExpenseManager.clearErrorMessage();
}

int getExpenseCount() {
    return g_addExpenseManager.getExpenseCount();
}

vector<Expense> getExpenses() {
    return g_addExpenseManager.getExpenses();
}

// ============================================================
// DASHBOARD FUNCTIONS (DashboardView.qml)
// ============================================================

double getTotalSpent() {
    return g_dashboardManager.getTotalSpent(g_addExpenseManager.getExpenses());
}

double getMonthlyLimit() {
    return g_dashboardManager.getMonthlyLimit();
}

void setMonthlyLimit(double limit) {
    g_dashboardManager.setMonthlyLimit(limit);
}

string getCurrency() {
    return g_dashboardManager.getCurrency();
}

double getBudgetUsagePercentage() {
    return g_dashboardManager.getBudgetUsagePercentage(g_addExpenseManager.getExpenses());
}

double getRemainingBudget() {
    return g_dashboardManager.getRemainingBudget(g_addExpenseManager.getExpenses());
}

vector<pair<string, double>> getCategoryWiseSummary() {
    return g_dashboardManager.getCategoryWiseSummary(g_addExpenseManager.getExpenses());
}

vector<Expense> getRecentExpenses(int count) {
    return g_dashboardManager.getRecentExpenses(g_addExpenseManager.getExpenses(), count);
}
