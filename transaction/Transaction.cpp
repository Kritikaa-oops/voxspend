#ifndef TRANSACTION_CPP
#define TRANSACTION_CPP

#include "../expense.h"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

// ============ GLOBAL DATA (Shared with AddExpense.cpp) ============
extern vector<Expense> g_expenses;
extern string g_lastExpenseError;

// ============ TRANSACTION FUNCTIONS (TransactionPage.qml) ============

// Get all expenses for display
vector<Expense> getExpenses() {
    return g_expenses;
}

// Get expense by ID
Expense* getExpenseById(int id) {
    for (auto& expense : g_expenses) {
        if (expense.id == id) {
            return &expense;
        }
    }
    return nullptr;
}

// Search expenses by keyword (title/description)
vector<Expense> searchExpenses(const string& keyword) {
    vector<Expense> result;
    
    if (keyword.empty()) {
        return g_expenses;
    }
    
    // Convert keyword to lowercase for case-insensitive search
    string lowerKeyword = keyword;
    transform(lowerKeyword.begin(), lowerKeyword.end(), lowerKeyword.begin(), ::tolower);
    
    for (const auto& expense : g_expenses) {
        string lowerDesc = expense.description;
        transform(lowerDesc.begin(), lowerDesc.end(), lowerDesc.begin(), ::tolower);
        
        if (lowerDesc.find(lowerKeyword) != string::npos) {
            result.push_back(expense);
        }
    }
    
    return result;
}

// Filter expenses by category
vector<Expense> filterExpensesByCategory(const string& category) {
    vector<Expense> result;
    
    if (category.empty() || category == "All") {
        return g_expenses;
    }
    
    for (const auto& expense : g_expenses) {
        if (expense.category == category) {
            result.push_back(expense);
        }
    }
    
    return result;
}

// Delete expense
bool deleteExpense(int id) {
    size_t sizeBefore = g_expenses.size();
    
    g_expenses.erase(
        remove_if(g_expenses.begin(), g_expenses.end(),
                  [id](const Expense& e) { return e.id == id; }),
        g_expenses.end()
    );
    
    if (g_expenses.size() < sizeBefore) {
        cout << "✅ Expense ID " << id << " deleted successfully." << endl;
        g_lastExpenseError = "";
        return true;
    } else {
        g_lastExpenseError = "Expense ID " + to_string(id) + " not found";
        cerr << "Error: " << g_lastExpenseError << endl;
        return false;
    }
}

// Edit expense
bool editExpense(int id, const string& newTitle, double newAmount, const string& newCategory, const string& newDate, const string& newNote) {
    for (auto& expense : g_expenses) {
        if (expense.id == id) {
            // Build description from title and note
            string description = newTitle;
            if (!newNote.empty()) {
                description = newTitle + " - " + newNote;
            }
            
            // Update fields
            expense.description = description;
            expense.amount = newAmount;
            expense.category = newCategory;
            expense.date = newDate;
            
            cout << "✅ Expense ID " << id << " edited successfully." << endl;
            g_lastExpenseError = "";
            return true;
        }
    }
    
    g_lastExpenseError = "Expense ID " + to_string(id) + " not found";
    cerr << "Error: " << g_lastExpenseError << endl;
    return false;
}

// Get recent expenses (for dashboard)
vector<Expense> getRecentExpenses(int count) {
    vector<Expense> sorted = g_expenses;
    sort(sorted.begin(), sorted.end(),
         [](const Expense& a, const Expense& b) {
             return a.id > b.id;
         });
    
    vector<Expense> recent;
    int displayCount = min(count, (int)sorted.size());
    for (int i = 0; i < displayCount; i++) {
        recent.push_back(sorted[i]);
    }
    
    return recent;
}

// Get expense count
int getExpenseCount() {
    return g_expenses.size();
}

// Get total spending
double getTotalExpenses() {
    double total = 0.0;
    for (const auto& expense : g_expenses) {
        total += expense.amount;
    }
    return total;
}

// Get total for a specific category
double getTotalForCategory(const string& category) {
    double total = 0.0;
    for (const auto& expense : g_expenses) {
        if (expense.category == category) {
            total += expense.amount;
        }
    }
    return total;
}

string getLastExpenseError() {
    return g_lastExpenseError;
}

void clearExpenseError() {
    g_lastExpenseError = "";
}

#endif