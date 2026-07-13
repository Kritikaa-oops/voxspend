#ifndef CATEGORY_CPP
#define CATEGORY_CPP

#include "../expense.h"
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

// ============ GLOBAL DATA (Shared with AddExpense.cpp) ============
extern vector<Expense> g_expenses;

// ============ CATEGORY DATA STRUCTURE ============

struct CategoryCardData {
    string name;
    double amount;
    string formattedAmount;
    string color;
    double percentage;
};

// ============ CATEGORY FUNCTIONS (BACKEND VERSION) ============

vector<pair<string, double>> getCategoryTotals() {
    map<string, double> categoryTotals;
    vector<pair<string, double>> result;
    
    for (const auto& expense : g_expenses) {
        categoryTotals[expense.category] += expense.amount;
    }
    
    for (const auto& pair : categoryTotals) {
        result.push_back(pair);
    }
    
    sort(result.begin(), result.end(),
         [](const pair<string, double>& a, const pair<string, double>& b) {
             return a.second > b.second;
         });
    
    return result;
}

vector<CategoryCardData> getCategoryCardData() {
    vector<CategoryCardData> result;
    auto categoryTotals = getCategoryTotals();
    
    map<string, string> categoryColors = {
        {"Food", "#543D6F"},
        {"Transport", "#81C784"},
        {"Shopping", "#A5D6A7"},
        {"Bills", "#C8E6C9"},
        {"Other", "#E8F5E9"}
    };
    
    for (const auto& pair : categoryTotals) {
        CategoryCardData data;
        data.name = pair.first;
        data.amount = pair.second;
        
        string amountStr = to_string((int)pair.second);
        int len = amountStr.length();
        string formatted = "";
        for (int i = 0; i < len; i++) {
            if (i > 0 && (len - i) % 3 == 0) {
                formatted += ",";
            }
            formatted += amountStr[i];
        }
        data.formattedAmount = formatted;
        
        if (categoryColors.find(pair.first) != categoryColors.end()) {
            data.color = categoryColors[pair.first];
        } else {
            data.color = "#D3D3D3";
        }
        
        double total = getTotalExpenses();
        data.percentage = (total > 0) ? (pair.second / total) * 100.0 : 0.0;
        
        result.push_back(data);
    }
    
    return result;
}

double getCategoryAmount(const string& category) {
    double total = 0.0;
    for (const auto& expense : g_expenses) {
        if (expense.category == category) {
            total += expense.amount;
        }
    }
    return total;
}

string getFormattedCategoryAmount(const string& category) {
    double amount = getCategoryAmount(category);
    string amountStr = to_string((int)amount);
    int len = amountStr.length();
    string formatted = "";
    for (int i = 0; i < len; i++) {
        if (i > 0 && (len - i) % 3 == 0) {
            formatted += ",";
        }
        formatted += amountStr[i];
    }
    return "Rs" + formatted;
}

bool hasCategoryExpenses(const string& category) {
    for (const auto& expense : g_expenses) {
        if (expense.category == category) {
            return true;
        }
    }
    return false;
}

vector<string> getUniqueCategories() {
    map<string, bool> uniqueMap;
    vector<string> result;
    
    for (const auto& expense : g_expenses) {
        if (uniqueMap.find(expense.category) == uniqueMap.end()) {
            uniqueMap[expense.category] = true;
            result.push_back(expense.category);
        }
    }
    
    return result;
}

int getCategoryCount() {
    return getUniqueCategories().size();
}

double getTotalExpenses() {
    double total = 0.0;
    for (const auto& expense : g_expenses) {
        total += expense.amount;
    }
    return total;
}

double getCategoryPercentage(const string& category) {
    double total = getTotalExpenses();
    if (total == 0) {
        return 0.0;
    }
    double amount = getCategoryAmount(category);
    return (amount / total) * 100.0;
}

string getCategoryColor(const string& category) {
    map<string, string> categoryColors = {
        {"Food", "#543D6F"},
        {"Transport", "#81C784"},
        {"Shopping", "#A5D6A7"},
        {"Bills", "#C8E6C9"},
        {"Other", "#E8F5E9"}
    };
    
    if (categoryColors.find(category) != categoryColors.end()) {
        return categoryColors[category];
    }
    return "#D3D3D3";
}

string getTopCategory() {
    auto totals = getCategoryTotals();
    if (totals.empty()) {
        return "";
    }
    return totals[0].first;
}

string getBottomCategory() {
    auto totals = getCategoryTotals();
    if (totals.empty()) {
        return "";
    }
    return totals[totals.size() - 1].first;
}

// ============ QML EXPOSED FUNCTIONS (with Qml suffix) ============

const char* getFormattedCategoryAmountQml(const char* category) {
    static string formatted = getFormattedCategoryAmount(string(category));
    return formatted.c_str();
}

const char* getTopCategoryQml() {
    static string top = getTopCategory();
    return top.c_str();
}

const char* getBottomCategoryQml() {
    static string bottom = getBottomCategory();
    return bottom.c_str();
}

#endif