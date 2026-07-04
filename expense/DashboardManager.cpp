#include "DashboardManager.h"
#include <algorithm>
#include <map>

DashboardManager::DashboardManager() : m_monthlyLimit(50000.0), m_currency("Rs.") {}

double DashboardManager::getTotalSpent(const vector<Expense>& expenses) const {
    double total = 0.0;
    for (const auto& expense : expenses) {
        total += expense.amount;
    }
    return total;
}

double DashboardManager::getMonthlyLimit() const {
    return m_monthlyLimit;
}

void DashboardManager::setMonthlyLimit(double limit) {
    if (limit > 0) {
        m_monthlyLimit = limit;
    }
}

string DashboardManager::getCurrency() const {
    return m_currency;
}

double DashboardManager::getBudgetUsagePercentage(const vector<Expense>& expenses) const {
    double total = getTotalSpent(expenses);
    if (m_monthlyLimit <= 0) return 0;
    return (total / m_monthlyLimit) * 100.0;
}

double DashboardManager::getRemainingBudget(const vector<Expense>& expenses) const {
    double total = getTotalSpent(expenses);
    return m_monthlyLimit - total;
}

vector<pair<string, double>> DashboardManager::getCategoryWiseSummary(const vector<Expense>& expenses) const {
    map<string, double> categoryTotals;
    vector<pair<string, double>> result;
    
    for (const auto& expense : expenses) {
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

vector<Expense> DashboardManager::getRecentExpenses(const vector<Expense>& expenses, int count) const {
    vector<Expense> sorted = expenses;
    vector<Expense> recent;
    
    sort(sorted.begin(), sorted.end(),
         [](const Expense& a, const Expense& b) {
             return a.id > b.id;
         });
    
    int displayCount = min(count, (int)sorted.size());
    for (int i = 0; i < displayCount; i++) {
        recent.push_back(sorted[i]);
    }
    
    return recent;
}