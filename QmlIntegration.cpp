#include "BackendManager.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// ============================================================
// GLOBAL DATA DEFINITIONS
// ============================================================

vector<User> g_users;
User g_currentUser;
string g_lastAuthError = "";

vector<Expense> g_expenses;
int g_nextId = 1;
string g_lastExpenseError = "";

// ============================================================
// AUTHENTICATION FUNCTIONS
// ============================================================

bool loginUser(const char* email, const char* password) {
    return ::loginUser(string(email), string(password));
}

bool isUserLoggedIn() {
    return ::isUserLoggedIn();
}

const char* getCurrentUserNameQml() {
    static string name = ::getCurrentUserName();
    return name.c_str();
}

const char* getCurrentUserEmailQml() {
    static string email = ::getCurrentUserEmail();
    return email.c_str();
}

const char* getLastAuthErrorQml() {
    static string error = ::getLastAuthError();
    return error.c_str();
}

void clearAuthError() {
    ::clearAuthError();
}

void logoutUser() {
    ::logoutUser();
}

const char* getCurrentUserProfileNameQml() {
    static string name = ::getCurrentUserProfileName();
    return name.c_str();
}

const char* getCurrentUserProfileEmailQml() {
    static string email = ::getCurrentUserProfileEmail();
    return email.c_str();
}

bool registerUser(const char* name, const char* email, const char* password, const char* confirmPassword) {
    return ::registerUser(string(name), string(email), string(password), string(confirmPassword));
}

bool registerUserWithPhone(const char* name, const char* phone, const char* password, const char* confirmPassword) {
    return ::registerUserWithPhone(string(name), string(phone), string(password), string(confirmPassword));
}

bool updateUserProfile(const char* newName, const char* newEmail) {
    return ::updateUserProfile(string(newName), string(newEmail));
}

// ============================================================
// EXPENSE FUNCTIONS
// ============================================================

bool addExpense(const char* title, double amount, const char* category, const char* date, const char* note) {
    return ::addExpense(string(title), amount, string(category), string(date), string(note));
}

const char* getLastExpenseErrorQml() {
    static string error = ::getLastExpenseError();
    return error.c_str();
}

void clearExpenseError() {
    ::clearExpenseError();
}

// ============================================================
// TRANSACTION FUNCTIONS
// ============================================================

bool deleteExpense(int id) {
    return ::deleteExpense(id);
}

bool editExpense(int id, const char* title, double amount, const char* category, const char* date, const char* note) {
    return ::editExpense(id, string(title), amount, string(category), string(date), string(note));
}

vector<Expense> getExpenses() {
    return ::getExpenses();
}

vector<Expense> searchExpenses(const char* keyword) {
    return ::searchExpenses(string(keyword));
}

vector<Expense> filterExpensesByCategory(const char* category) {
    return ::filterExpensesByCategory(string(category));
}

int getExpenseCount() {
    return ::getExpenseCount();
}

double getTotalExpenses() {
    return ::getTotalExpenses();
}

double getTotalForCategory(const char* category) {
    return ::getTotalForCategory(string(category));
}

vector<Expense> getRecentExpenses(int count) {
    return ::getRecentExpenses(count);
}

// ============================================================
// CHART FUNCTIONS
// ============================================================

vector<pair<string, double>> getCategoryWiseSummary() {
    return ::getCategoryWiseSummary();
}

vector<CategoryChartData> getCategoryChartData() {
    return ::getCategoryChartData();
}

double getHighestExpense() {
    return ::getHighestExpense();
}

double getAverageExpense() {
    return ::getAverageExpense();
}

string getHighestCategory() {
    return ::getHighestCategory();
}

StatisticsData getStatisticsData() {
    return ::getStatisticsData();
}

vector<double> getDistributionPercentages() {
    return ::getDistributionPercentages();
}

vector<string> getCategoryNames() {
    return ::getCategoryNames();
}

vector<string> getCategoryColors() {
    return ::getCategoryColors();
}

vector<pair<string, double>> getLastSixMonthsSpending() {
    return ::getLastSixMonthsSpending();
}

// ============================================================
// CATEGORY FUNCTIONS
// ============================================================

vector<CategoryCardData> getCategoryCardData() {
    return ::getCategoryCardData();
}

double getCategoryAmount(const char* category) {
    return ::getCategoryAmount(string(category));
}

const char* getFormattedCategoryAmountQml(const char* category) {
    static string formatted = ::getFormattedCategoryAmount(string(category));
    return formatted.c_str();
}

bool hasCategoryExpenses(const char* category) {
    return ::hasCategoryExpenses(string(category));
}

vector<string> getUniqueCategories() {
    return ::getUniqueCategories();
}

int getCategoryCount() {
    return ::getCategoryCount();
}

double getCategoryPercentage(const char* category) {
    return ::getCategoryPercentage(string(category));
}

const char* getCategoryColor(const char* category) {
    static string color = ::getCategoryColor(string(category));
    return color.c_str();
}

const char* getTopCategoryQml() {
    static string top = ::getTopCategory();
    return top.c_str();
}

const char* getBottomCategoryQml() {
    static string bottom = ::getBottomCategory();
    return bottom.c_str();
}

// ============================================================
// HOMEPAGE FUNCTIONS
// ============================================================

const char* getWelcomeMessageQml() {
    static string msg = ::getWelcomeMessage();
    return msg.c_str();
}

double getCurrentMonthSpending() {
    return ::getCurrentMonthSpending();
}

const char* getFormattedCurrentMonthSpendingQml() {
    static string formatted = ::getFormattedCurrentMonthSpending();
    return formatted.c_str();
}

vector<RecentTransaction> getRecentTransactions(int count) {
    return ::getRecentTransactions(count);
}

bool hasTransactions() {
    return ::hasTransactions();
}

int getTotalExpenseCount() {
    return ::getTotalExpenseCount();
}

double getTotalSpending() {
    return ::getTotalSpending();
}

const char* getFormattedTotalSpendingQml() {
    static string formatted = ::getFormattedTotalSpending();
    return formatted.c_str();
}

const char* getUserDisplayNameQml() {
    static string name = ::getUserDisplayName();
    return name.c_str();
}

const char* getUserDisplayEmailQml() {
    static string email = ::getUserDisplayEmail();
    return email.c_str();
}

const char* getTimeBasedGreetingQml() {
    static string greeting = ::getTimeBasedGreeting();
    return greeting.c_str();
}

const char* getFullGreetingQml() {
    static string greeting = ::getFullGreeting();
    return greeting.c_str();
}

DashboardSummary getDashboardSummary() {
    return ::getDashboardSummary();
}

// ============================================================
// MONTH RESET FUNCTIONS
// ============================================================

vector<MonthlyArchive> getMonthlyArchives() {
    return ::getMonthlyArchives();
}

MonthlyArchive getMonthSummary(const char* month) {
    return ::getMonthSummary(string(month));
}

double getPreviousMonthSpending() {
    return ::getPreviousMonthSpending();
}

const char* getPreviousMonthNameQml() {
    static string name = ::getPreviousMonthName();
    return name.c_str();
}

MonthlyComparison getMonthComparison() {
    return ::getMonthComparison();
}

void clearArchives() {
    ::clearArchives();
}