#include "AddExpenseManager.h"
#include <iostream>
#include <regex>
#include <algorithm>

AddExpenseManager::AddExpenseManager() : m_nextId(1) {}

int AddExpenseManager::generateNextId() {
    return m_nextId++;
}

bool AddExpenseManager::isValidDate(const string& date) const {
    regex datePattern(R"(\d{4}-\d{2}-\d{2})");
    if (!regex_match(date, datePattern)) {
        return false;
    }
    
    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));
    
    if (year < 2020 || year > 2030) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }
    
    if (month == 2) {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (isLeapYear ? 29 : 28)) {
            return false;
        }
    }
    
    return true;
}

bool AddExpenseManager::isValidCategory(const string& category) const {
    vector<string> validCategories = {"Food", "Transport", "Shopping", "Bills", "Other"};
    
    for (const auto& cat : validCategories) {
        if (category == cat) {
            return true;
        }
    }
    return false;
}

bool AddExpenseManager::validateExpenseInput(const string& category, double amount, const string& date) {
    if (category.empty()) {
        m_lastError = "Please select a category";
        return false;
    }
    
    if (!isValidCategory(category)) {
        m_lastError = "Invalid category selected";
        return false;
    }
    
    if (amount <= 0) {
        m_lastError = "Please enter a valid amount greater than 0";
        return false;
    }
    
    if (amount > 1000000) {
        m_lastError = "Amount cannot exceed Rs. 1,000,000";
        return false;
    }
    
    if (date.empty()) {
        m_lastError = "Please select a date";
        return false;
    }
    
    if (!isValidDate(date)) {
        m_lastError = "Invalid date format. Use YYYY-MM-DD";
        return false;
    }
    
    m_lastError = "";
    return true;
}

bool AddExpenseManager::addExpense(const string& category, double amount, const string& date, const string& description) {
    if (!validateExpenseInput(category, amount, date)) {
        cerr << "Error: " << m_lastError << endl;
        return false;
    }
    
    Expense newExpense;
    newExpense.id = generateNextId();
    newExpense.category = category;
    newExpense.amount = amount;
    newExpense.date = date;
    newExpense.description = description;
    
    m_expenses.push_back(newExpense);
    
    cout << "========================================" << endl;
    cout << "  ✅ EXPENSE ADDED SUCCESSFULLY" << endl;
    cout << "========================================" << endl;
    cout << "  ID:         " << newExpense.id << endl;
    cout << "  Category:   " << newExpense.category << endl;
    cout << "  Amount:     Rs." << newExpense.amount << endl;
    cout << "  Date:       " << newExpense.date << endl;
    cout << "  Note:       " << (newExpense.description.empty() ? "(empty)" : newExpense.description) << endl;
    cout << "========================================" << endl;
    
    m_lastError = "";
    return true;
}

string AddExpenseManager::getErrorMessage() const {
    return m_lastError;
}

void AddExpenseManager::clearErrorMessage() {
    m_lastError = "";
}

void AddExpenseManager::clearAllExpenses() {
    m_expenses.clear();
    m_nextId = 1;
    m_lastError = "";
}

const vector<Expense>& AddExpenseManager::getExpenses() const {
    return m_expenses;
}

int AddExpenseManager::getExpenseCount() const {
    return m_expenses.size();
}