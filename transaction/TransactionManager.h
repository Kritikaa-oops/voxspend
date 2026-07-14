#ifndef TRANSACTION_MANAGER_H
#define TRANSACTION_MANAGER_H

#include "../expense.h"
#include <vector>
#include <string>

using namespace std;

// ============ TRANSACTION FUNCTIONS ============
vector<Expense> getExpenses();
vector<Expense> searchExpenses(const string& keyword);
vector<Expense> filterExpensesByCategory(const string& category);
bool deleteExpense(int id);
bool editExpense(int id, const string& title, double amount, const string& category, const string& date, const string& note);
int getExpenseCount();
double getTotalExpenses();
double getTotalForCategory(const string& category);
vector<Expense> getRecentExpenses(int count);

// ============ CHART FUNCTIONS ============
vector<pair<string, double>> getCategoryWiseSummary();
vector<CategoryChartData> getCategoryChartData();
double getHighestExpense();
double getAverageExpense();
string getHighestCategory();
StatisticsData getStatisticsData();
vector<double> getDistributionPercentages();
vector<string> getCategoryNames();
vector<string> getCategoryColors();
vector<pair<string, double>> getLastSixMonthsSpending();

// ============ CATEGORY FUNCTIONS ============
vector<CategoryCardData> getCategoryCardData();
double getCategoryAmount(const string& category);
string getFormattedCategoryAmount(const string& category);
bool hasCategoryExpenses(const string& category);
vector<string> getUniqueCategories();
int getCategoryCount();
double getCategoryPercentage(const string& category);
string getCategoryColor(const string& category);
string getTopCategory();
string getBottomCategory();

#endif