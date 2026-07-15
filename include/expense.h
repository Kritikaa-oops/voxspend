#ifndef EXPENSE_H
#define EXPENSE_H

#include <string>
#include <vector>

using namespace std;

struct Expense {
    int id;
    string category;
    double amount;
    string date;
    string description;
};

struct Budget {
    string category;
    double limit;
};

struct User {
    string email;
    string password;
    string name;
    string phone;
    string profilePicture;
};

// ============ CHART DATA STRUCTURES ============

struct CategoryChartData {
    string label;
    string color;
    double percentage;
    double amount;
};

struct StatisticsData {
    double highestAmount;
    double averageAmount;
    double totalAmount;
    int totalCount;
    string highestCategory;
};

// ============ CATEGORY CARD DATA ============



// ============ MAIN PAGE DATA ============

struct RecentTransaction {
    int id;
    string title;
    string category;
    double amount;
    string date;
    string formattedAmount;
};

struct DashboardSummary {
    double totalSpent;
    int totalTransactions;
    int categoryCount;
    double currentMonthSpent;
    string topCategory;
};

// ============ MONTH RESET DATA (NEW) ============

struct MonthlyArchive {
    string month;
    vector<Expense> archivedExpenses;
    double totalSpent;
};

struct MonthlyComparison {
    string currentMonth;
    double currentSpent;
    string previousMonth;
    double previousSpent;
    double difference;
    double percentageChange;
};

#endif