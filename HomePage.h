#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include "expense.h"
#include <vector>
#include <string>

using namespace std;

// ============ HOMEPAGE FUNCTIONS ============
string getWelcomeMessage();
double getCurrentMonthSpending();
string getFormattedCurrentMonthSpending();
vector<RecentTransaction> getRecentTransactions(int count);
bool hasTransactions();
int getTotalExpenseCount();
double getTotalSpending();
string getFormattedTotalSpending();
string getUserDisplayName();
string getUserDisplayEmail();
string getTimeBasedGreeting();
string getFullGreeting();
DashboardSummary getDashboardSummary();

// ============ MONTH RESET FUNCTIONS ============
vector<MonthlyArchive> getMonthlyArchives();
MonthlyArchive getMonthSummary(const string& month);
double getPreviousMonthSpending();
string getPreviousMonthName();
MonthlyComparison getMonthComparison();
void clearArchives();

#endif