#ifndef ADDEXPENSE_CPP
#define ADDEXPENSE_CPP

#include "expense.h"
#include <vector>
#include <string>
#include <iostream>
#include <regex>
#include <algorithm>
#include <ctime>

using namespace std;

// =================================================================
// OOP CONCEPT: Modularity & Global State References
// Linking to shared data types and external objects defined in expense.h
// =================================================================
extern vector<Expense> g_expenses;
extern int g_nextId;
extern string g_lastExpenseError;

// Helper function to auto increment unique IDs
int generateNextId() {
    return g_nextId++;
}

// Function to validate date format (YYYY-MM-DD) and limits
bool isValidDate(const string& date) {
    // Check format YYYY-MM-DD using regex
    regex datePattern(R"(\d{4}-\d{2}-\d{2})");
    if (!regex_match(date, datePattern)) {
        return false;
    }
    
    // Extract year, month, day
    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));
    
    // Basic year/month/day range checks
    if (year < 2020 || year > 2030) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    
    // Months with 30 days
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }
    
    // February check for leap year
    if (month == 2) {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (isLeapYear ? 29 : 28)) {
            return false;
        }
    }
    
    return true;
}

// Checking if selected category matches valid dropdown options
bool isValidCategory(const string& category) {
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

// Check amount bounds
bool isValidAmount(double amount) {
    return amount > 0 && amount <= 1000000;
}

// Validation function checking all input data before updating object state
bool validateExpenseInput(const string& title, double amount, const string& category, const string& date) {
    // Check title length
    if (title.empty()) {
        g_lastExpenseError = "Please enter a title";
        return false;
    }
    
    if (title.length() > 100) {
        g_lastExpenseError = "Title cannot exceed 100 characters";
        return false;
    }
    
    // Validate amount limit
    if (!isValidAmount(amount)) {
        g_lastExpenseError = "Please enter a valid amount greater than 0 (max Rs. 1,000,000)";
        return false;
    }
    
    // Validate category selection
    if (category.empty() || category == "Select Category") {
        g_lastExpenseError = "Please select a category";
        return false;
    }
    
    if (!isValidCategory(category)) {
        g_lastExpenseError = "Invalid category selected";
        return false;
    }
    
    // Validate date format
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

// =========================================================================
// OOP CONCEPT: Object Creation & Data Encapsulation
// Instantiates an Expense object, sets properties, and pushes it to storage
// =========================================================================
bool addExpense(const string& title, double amount, const string& category, const string& date, const string& note) {
    // Abort if inputs fail validation
    if (!validateExpenseInput(title, amount, category, date)) {
        cerr << "Error: " << g_lastExpenseError << endl;
        return false;
    }
    
    // Format description with optional note
    string description = title;
    if (!note.empty()) {
        description = title + " - " + note;
    }
    
    // OOP: Instantiating Expense object and assigning state attributes
    Expense newExpense;
    newExpense.id = generateNextId();
    newExpense.category = category;
    newExpense.amount = amount;
    newExpense.date = date;
    newExpense.description = description;
    
    // Adding object instance into vector collection
    g_expenses.push_back(newExpense);
    
    // Print output to console for verification
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

// =========================================================================
// OOP CONCEPT: Getter Methods / Accessors
// Controlled functions providing access to encapsulated state data
// =========================================================================

// Getter for error status
string getLastExpenseError() {
    return g_lastExpenseError;
}

// Function to reset error state
void clearExpenseError() {
    g_lastExpenseError = "";
}

// Getter returning current list of Expense objects
vector<Expense> getExpenses() {
    return g_expenses;
}

#endif