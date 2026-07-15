#ifndef CHARTS_CPP
#define CHARTS_CPP

#include "expense.h"
#include "Category.h" // FIXED: Added this so it can find getTotalExpenses()
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include <cmath>
#include <ctime>

using namespace std;

// ============ GLOBAL DATA (Shared with AddExpense.cpp) ============
extern vector<Expense> g_expenses;

// ============ CHART DATA STRUCTURES ============
// (These are now safely stored in expense.h)

// ============ CHART FUNCTIONS (ChartsPage.qml) ============

// Get category wise summary with percentages
vector<pair<string, double>> getCategoryWiseSummary() {
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

// Get category chart data with percentages and colors
vector<CategoryChartData> getCategoryChartData() {
    vector<CategoryChartData> result;
    double total = getTotalExpenses();

    // Color mapping for categories
    map<string, string> categoryColors = {
        {"Food", "#543D6F"},
        {"Transport", "#81C784"},
        {"Shopping", "#A5D6A7"},
        {"Bills", "#C8E6C9"},
        {"Other", "#E8F5E9"}
    };

    auto summary = getCategoryWiseSummary();

    for (const auto& pair : summary) {
        CategoryChartData data;
        data.label = pair.first;
        data.amount = pair.second;
        data.percentage = (total > 0) ? (pair.second / total) * 100.0 : 0.0;

        // Get color for category
        if (categoryColors.find(pair.first) != categoryColors.end()) {
            data.color = categoryColors[pair.first];
        } else {
            data.color = "#D3D3D3"; // Default gray
        }

        result.push_back(data);
    }

    return result;
}

// FIXED: Your friend forgot to write this function!
// Get expense count
int getExpenseCount() {
    return g_expenses.size();
}

// Get highest expense
double getHighestExpense() {
    if (g_expenses.empty()) {
        return 0.0;
    }

    double highest = g_expenses[0].amount;
    for (const auto& expense : g_expenses) {
        if (expense.amount > highest) {
            highest = expense.amount;
        }
    }
    return highest;
}

// Get average expense
double getAverageExpense() {
    if (g_expenses.empty()) {
        return 0.0;
    }
    return getTotalExpenses() / g_expenses.size();
}

// Get highest expense category
string getHighestCategory() {
    if (g_expenses.empty()) {
        return "No data";
    }

    auto summary = getCategoryWiseSummary();
    if (!summary.empty()) {
        return summary[0].first;
    }
    return "No data";
}

// Get statistics data for dashboard
StatisticsData getStatisticsData() {
    StatisticsData stats;
    stats.totalAmount = getTotalExpenses();
    stats.totalCount = getExpenseCount();
    stats.highestAmount = getHighestExpense();
    stats.averageAmount = getAverageExpense();
    stats.highestCategory = getHighestCategory();
    return stats;
}

// Get distribution percentages for pie chart (expense distribution)
vector<double> getDistributionPercentages() {
    vector<double> percentages;
    double total = getTotalExpenses();

    if (total == 0) {
        return {25.0, 25.0, 25.0, 25.0}; // Equal distribution when no data
    }

    auto summary = getCategoryWiseSummary();

    // Get top 4 categories
    int count = min(4, (int)summary.size());
    for (int i = 0; i < count; i++) {
        percentages.push_back((summary[i].second / total) * 100.0);
    }

    // Fill remaining with 0
    while (percentages.size() < 4) {
        percentages.push_back(0);
    }

    return percentages;
}

// Get category names for distribution
vector<string> getCategoryNames() {
    vector<string> names;
    auto summary = getCategoryWiseSummary();

    int count = min(4, (int)summary.size());
    for (int i = 0; i < count; i++) {
        names.push_back(summary[i].first);
    }

    // Fill remaining with empty
    while (names.size() < 4) {
        names.push_back("");
    }

    return names;
}

// Get category colors for distribution
vector<string> getCategoryColors() {
    vector<string> colors = {"#543D6F", "#81C784", "#A5D6A7", "#C8E6C9"};

    vector<string> result;
    auto summary = getCategoryWiseSummary();

    int count = min(4, (int)summary.size());
    for (int i = 0; i < count; i++) {
        result.push_back(colors[i % colors.size()]);
    }

    while (result.size() < 4) {
        result.push_back("#E0E0E0");
    }

    return result;
}

// Get monthly spending (for trend analysis)
double getMonthlySpending(const string& month) {
    double total = 0.0;
    for (const auto& expense : g_expenses) {
        if (expense.date.substr(0, 7) == month) {
            total += expense.amount;
        }
    }
    return total;
}

// Get spending by month for last 6 months
vector<pair<string, double>> getLastSixMonthsSpending() {
    vector<pair<string, double>> result;

    // Get current date
    time_t now = time(nullptr);
    struct tm* tm = localtime(&now);

    int currentYear = tm->tm_year + 1900;
    int currentMonth = tm->tm_mon + 1;

    // Get last 6 months
    for (int i = 5; i >= 0; i--) {
        int month = currentMonth - i;
        int year = currentYear;

        if (month <= 0) {
            month += 12;
            year -= 1;
        }

        char monthStr[8];
        snprintf(monthStr, sizeof(monthStr), "%04d-%02d", year, month);
        string monthKey = string(monthStr);

        double spending = getMonthlySpending(monthKey);
        result.push_back({monthKey, spending});
    }

    return result;
}

#endif