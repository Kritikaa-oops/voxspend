#include "ExpenseManager.h"
#include <iostream>
#include <regex>
#include <algorithm>

vector<Expense> g_expenses;
int g_nextId = 1;
string g_lastExpenseError = "";

int generateNextId() { return g_nextId++; }

bool isValidDate(const string& date) {
    regex datePattern(R"(\d{4}-\d{2}-\d{2})");
    if (!regex_match(date, datePattern)) return false;
    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));
    if (year < 2020 || year > 2030) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;
    if (month == 2) {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (isLeap ? 29 : 28)) return false;
    }
    return true;
}

bool isValidCategory(const string& category) {
    vector<string> valid = {"Food", "Transport", "Shopping", "Bills", "Other"};
    for (const auto& c : valid) {
        if (category == c) return true;
    }
    return false;
}

bool validateExpenseInput(const string& title, double amount, const string& category, const string& date) {
    if (title.empty()) { g_lastExpenseError = "Please enter a title"; return false; }
    if (amount <= 0 || amount > 1000000) { g_lastExpenseError = "Invalid amount"; return false; }
    if (!isValidCategory(category)) { g_lastExpenseError = "Invalid category"; return false; }
    if (!isValidDate(date)) { g_lastExpenseError = "Invalid date"; return false; }
    g_lastExpenseError = "";
    return true;
}

bool addExpense(const string& title, double amount, const string& category, const string& date, const string& note) {
    if (!validateExpenseInput(title, amount, category, date)) return false;
    Expense e;
    e.id = generateNextId();
    e.category = category;
    e.amount = amount;
    e.date = date;
    e.description = title + (note.empty() ? "" : " - " + note);
    g_expenses.push_back(e);
    g_lastExpenseError = "";
    return true;
}

string getLastExpenseError() { return g_lastExpenseError; }
void clearExpenseError() { g_lastExpenseError = ""; }