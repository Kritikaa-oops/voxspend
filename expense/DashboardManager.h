#ifndef DASHBOARD_MANAGER_H
#define DASHBOARD_MANAGER_H

#include "../expense.h"
#include <vector>
#include <string>

using namespace std;

class DashboardManager {
private:
    double m_monthlyLimit;
    string m_currency;
    
public:
    DashboardManager();
    
    // ============ DASHBOARD DATA (DashboardView.qml) ============
    double getTotalSpent(const vector<Expense>& expenses) const;
    double getMonthlyLimit() const;
    void setMonthlyLimit(double limit);
    string getCurrency() const;
    double getBudgetUsagePercentage(const vector<Expense>& expenses) const;
    double getRemainingBudget(const vector<Expense>& expenses) const;
    
    // ============ CATEGORY SUMMARY ============
    vector<pair<string, double>> getCategoryWiseSummary(const vector<Expense>& expenses) const;
    
    // ============ RECENT EXPENSES ============
    vector<Expense> getRecentExpenses(const vector<Expense>& expenses, int count) const;
};

#endif