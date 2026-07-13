#ifndef ADDEXPENSE_CPP
#define ADDEXPENSE_CPP

#include "../expense.h"
#include <vector>
#include <string>
#include <iostream>
#include <regex>
#include <algorithm>
#include <ctime>

using namespace std;

// ============ GLOBAL DATA ============
extern vector<Expense> g_expenses;
extern int g_nextId;
extern string g_lastExpenseError;

// ============ PRIVATE HELPER FUNCTIONS ============

int generateNextId() {
    return g_nextId++;
}

bool isValidDate(const string& date) {
    // Check format YYYY-MM-DD
    regex datePattern(R"(\d{4}-\d{2}-\d{2})");
    if (!regex_match(date, datePattern)) {
        return false;
    }
    
    // Extract year, month, day
    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));
    
    // Basic validation
    if (year < 2020 || year > 2030) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    
    // Month-specific day validation
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }
    
    // February validation (leap year)
    if (month == 2) {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (isLeapYear ? 29 : 28)) {
            return false;
        }
    }
    
    return true;
}

bool isValidCategory(const string& category) {
    // Valid categories from AddExpense.qml
    vector<string> validCategories = {
        "Food", "Transport", "Shopping", "Bills", "Other"
    };
    
    for (const auto& cat : validCategories) {
        if (category == cat) {
            return true;
        }
    }
    return false;
}

bool isValidAmount(double amount) {
    return amount > 0 && amount <= 1000000;
}

bool validateExpenseInput(const string& title, double amount, const string& category, const string& date) {
    // Validate title
    if (title.empty()) {
        g_lastExpenseError = "Please enter a title";
        return false;
    }
    
    if (title.length() > 100) {
        g_lastExpenseError = "Title cannot exceed 100 characters";
        return false;
    }
    
    // Validate amount
    if (!isValidAmount(amount)) {
        g_lastExpenseError = "Please enter a valid amount greater than 0 (max Rs. 1,000,000)";
        return false;
    }
    
    // Validate category
    if (category.empty() || category == "Select Category") {
        g_lastExpenseError = "Please select a category";
        return false;
    }
    
    if (!isValidCategory(category)) {
        g_lastExpenseError = "Invalid category selected";
        return false;
    }
    
    // Validate date
    if (date.empty()) {
        g_lastExpenseError = "Please select a date";
        return false;
    }
    
    if (!isValidDate(date)) {
        g_lastExpenseError = "Invalid date format. Use YYYY-MM-DD";
        return false;
    }
    
    g_lastExpenseError = "";
    return true;
}

// ============ ADD EXPENSE FUNCTIONS (AddExpense.qml) ============

bool addExpense(const string& title, double amount, const string& category, const string& date, const string& note) {
    // Validate input
    if (!validateExpenseInput(title, amount, category, date)) {
        cerr << "Error: " << g_lastExpenseError << endl;
        return false;
    }
    
    // Create description from title and note
    string description = title;
    if (!note.empty()) {
        description = title + " - " + note;
    }
    
    // Create new expense
    Expense newExpense;
    newExpense.id = generateNextId();
    newExpense.category = category;
    newExpense.amount = amount;
    newExpense.date = date;
    newExpense.description = description;
    
    // Add to global list
    g_expenses.push_back(newExpense);
    
    cout << "========================================" << endl;
    cout << "  ✅ EXPENSE ADDED SUCCESSFULLY" << endl;
    cout << "========================================" << endl;
    cout << "  ID:         " << newExpense.id << endl;
    cout << "  Title:      " << title << endl;
    cout << "  Category:   " << newExpense.category << endl;
    cout << "  Amount:     Rs." << newExpense.amount << endl;
    cout << "  Date:       " << newExpense.date << endl;
    cout << "  Note:       " << (note.empty() ? "(empty)" : note) << endl;
    cout << "========================================" << endl;
    
    g_lastExpenseError = "";
    return true;
}

// ============ HELPER FUNCTIONS ============

string getLastExpenseError() {
    return g_lastExpenseError;
}

void clearExpenseError() {
    g_lastExpenseError = "";
}

int getExpenseCount() {
    return g_expenses.size();
}

double getTotalExpenses() {
    double total = 0.0;
    for (const auto& expense : g_expenses) {
        total += expense.amount;
    }
    return total;
}

vector<Expense> getExpenses() {
    return g_expenses;
}

#endif