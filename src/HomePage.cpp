#ifndef HOMEPAGE_CPP
#define HOMEPAGE_CPP

#include "expense.h"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <map>

using namespace std;

// =========================================================================
// OOP CONCEPT: Global State & Shared Data References
// External instances shared across modules (User state, Expense collection)
// =========================================================================
extern vector<Expense> g_expenses;
extern User g_currentUser;
extern int g_nextId;

// =========================================================================
// MONTH RESET DATA
// Static variables tracking monthly archived spending and reset flags
// =========================================================================
static vector<MonthlyArchive> g_archives;
static string g_currentMonth = "";
static bool g_monthResetTriggered = false;

// ============ MONTH RESET HELPER FUNCTIONS ============

// Formats and returns current system year-month key (YYYY-MM)
string getCurrentMonthKey() {
    time_t now = time(nullptr);
    struct tm* tm = localtime(&now);
    char monthKey[8];
    snprintf(monthKey, sizeof(monthKey), "%04d-%02d", 
             tm->tm_year + 1900, tm->tm_mon + 1);
    return string(monthKey);
}

// Checks if calendar month has changed compared to last logged month
bool isNewMonth() {
    if (g_currentMonth.empty()) {
        g_currentMonth = getCurrentMonthKey();
        return false;
    }
    return g_currentMonth != getCurrentMonthKey();
}

// OOP CONCEPT: Automated State Management & Object Archiving
// Archives current month expenses into a MonthlyArchive object when a new month begins
bool resetMonthIfNeeded() {
    if (!isNewMonth()) {
        return false;
    }
    
    cout << "========================================" << endl;
    cout << "  🔄 MONTHLY RESET TRIGGERED" << endl;
    cout << "========================================" << endl;
    cout << "  Previous Month: " << g_currentMonth << endl;
    cout << "  Current Month:  " << getCurrentMonthKey() << endl;
    cout << "  Archived " << g_expenses.size() << " expenses." << endl;
    cout << "========================================" << endl;
    
    // Instantiate archive object and capture snapshot of expenses
    MonthlyArchive archive;
    archive.month = g_currentMonth;
    archive.archivedExpenses = g_expenses;
    
    double total = 0.0;
    for (const auto& exp : g_expenses) {
        total += exp.amount;
    }
    archive.totalSpent = total;
    
    // Store archive in list and reset active month state
    g_archives.push_back(archive);
    
    g_expenses.clear();
    g_nextId = 1;
    
    g_currentMonth = getCurrentMonthKey();
    g_monthResetTriggered = true;
    
    cout << "✅ Month reset complete!" << endl;
    cout << "   New month: " << g_currentMonth << endl;
    return true;
}

// ============ HOMEPAGE FUNCTIONS (BACKEND VERSION) ============

// Returns personalized welcome message using user object state
string getWelcomeMessage() {
    if (!g_currentUser.email.empty()) {
        return "Welcome, " + g_currentUser.name + "!";
    }
    return "Welcome to VoxSpend";
}

// Calculates sum of expenses logged in current month
double getCurrentMonthSpending() {
    resetMonthIfNeeded();
    
    double total = 0.0;
    string currentMonth = getCurrentMonthKey();
    
    for (const auto& expense : g_expenses) {
        if (expense.date.substr(0, 7) == currentMonth) {
            total += expense.amount;
        }
    }
    return total;
}

// Helper function to format currency with thousand separators (e.g., Rs10,000)
string getFormattedCurrentMonthSpending() {
    double amount = getCurrentMonthSpending();
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

// OOP CONCEPT: Data Transformation & Collection Manipulation
// Sorts expenses in reverse order and constructs RecentTransaction objects for display
vector<RecentTransaction> getRecentTransactions(int count) {
    vector<RecentTransaction> result;
    
    vector<Expense> sorted = g_expenses;
    // Sort transactions by highest ID (most recent first)
    sort(sorted.begin(), sorted.end(),
         [](const Expense& a, const Expense& b) {
             return a.id > b.id;
         });
    
    int displayCount = min(count, (int)sorted.size());
    
    for (int i = 0; i < displayCount; i++) {
        RecentTransaction trans;
        trans.id = sorted[i].id;
        trans.title = sorted[i].description;
        trans.category = sorted[i].category;
        trans.amount = sorted[i].amount;
        trans.date = sorted[i].date;
        
        // Formatting amount string with commas
        string amountStr = to_string((int)sorted[i].amount);
        int len = amountStr.length();
        string formatted = "";
        for (int j = 0; j < len; j++) {
            if (j > 0 && (len - j) % 3 == 0) {
                formatted += ",";
            }
            formatted += amountStr[j];
        }
        trans.formattedAmount = formatted;
        
        result.push_back(trans);
    }
    
    return result;
}

// Checks if any expenses are logged
bool hasTransactions() {
    return !g_expenses.empty();
}

// Returns total count of expense records
int getTotalExpenseCount() {
    return g_expenses.size();
}

// Sums all expenses recorded across lifetime
double getTotalSpending() {
    double total = 0.0;
    for (const auto& expense : g_expenses) {
        total += expense.amount;
    }
    return total;
}

// Formats total lifetime spending into formatted currency string
string getFormattedTotalSpending() {
    double amount = getTotalSpending();
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

// Safe getter for user display name
string getUserDisplayName() {
    if (!g_currentUser.email.empty()) {
        return g_currentUser.name;
    }
    return "Guest";
}

// Safe getter for user email
string getUserDisplayEmail() {
    if (!g_currentUser.email.empty()) {
        return g_currentUser.email;
    }
    return "guest@example.com";
}

// Generates greeting based on system hour (Morning / Afternoon / Evening / Night)
string getTimeBasedGreeting() {
    time_t now = time(nullptr);
    struct tm* tm = localtime(&now);
    int hour = tm->tm_hour;
    
    if (hour < 12) {
        return "Good Morning";
    } else if (hour < 17) {
        return "Good Afternoon";
    } else if (hour < 21) {
        return "Good Evening";
    } else {
        return "Good Night";
    }
}

// Combines time-based greeting with user display name
string getFullGreeting() {
    string greeting = getTimeBasedGreeting();
    string name = getUserDisplayName();
    
    if (name != "Guest") {
        return greeting + ", " + name + "!";
    }
    return greeting + "!";
}

// =========================================================================
// OOP CONCEPT: Aggregation & Data Transfer Object (DTO)
// Computes metrics across expenses and bundles them into DashboardSummary object
// =========================================================================
DashboardSummary getDashboardSummary() {
    DashboardSummary summary;
    summary.totalSpent = getTotalSpending();
    summary.totalTransactions = getTotalExpenseCount();
    summary.currentMonthSpent = getCurrentMonthSpending();
    
    // Count distinct categories used
    vector<string> categories;
    for (const auto& expense : g_expenses) {
        bool found = false;
        for (const auto& cat : categories) {
            if (cat == expense.category) {
                found = true;
                break;
            }
        }
        if (!found) {
            categories.push_back(expense.category);
        }
    }
    summary.categoryCount = categories.size();
    
    // Determine category with highest total spending using std::map
    if (!g_expenses.empty()) {
        map<string, double> categoryTotals;
        for (const auto& expense : g_expenses) {
            categoryTotals[expense.category] += expense.amount;
        }
        
        string topCat = "";
        double maxAmount = 0;
        for (const auto& pair : categoryTotals) {
            if (pair.second > maxAmount) {
                maxAmount = pair.second;
                topCat = pair.first;
            }
        }
        summary.topCategory = topCat;
    } else {
        summary.topCategory = "No data";
    }
    
    return summary;
}

// ============ MONTH RESET FUNCTIONS ============

// Accessor returning historical monthly archive collection
vector<MonthlyArchive> getMonthlyArchives() {
    return g_archives;
}

// Searches and returns archive object for specific month
MonthlyArchive getMonthSummary(const string& month) {
    for (const auto& archive : g_archives) {
        if (archive.month == month) {
            return archive;
        }
    }
    return MonthlyArchive();
}

// Returns total spending recorded in previous archived month
double getPreviousMonthSpending() {
    if (g_archives.empty()) {
        return 0.0;
    }
    return g_archives.back().totalSpent;
}

// Returns label/key for previous month
string getPreviousMonthName() {
    if (g_archives.empty()) {
        return "No previous month";
    }
    return g_archives.back().month;
}

// Computes month-over-month spending difference and percentage comparison
MonthlyComparison getMonthComparison() {
    MonthlyComparison comp;
    comp.currentMonth = getCurrentMonthKey();
    comp.currentSpent = getCurrentMonthSpending();
    
    if (!g_archives.empty()) {
        comp.previousMonth = g_archives.back().month;
        comp.previousSpent = g_archives.back().totalSpent;
        comp.difference = comp.currentSpent - comp.previousSpent;
        comp.percentageChange = (comp.previousSpent > 0) ? 
            (comp.difference / comp.previousSpent) * 100.0 : 0.0;
    } else {
        comp.previousMonth = "No data";
        comp.previousSpent = 0;
        comp.difference = 0;
        comp.percentageChange = 0;
    }
    
    return comp;
}

// Resets archive store
void clearArchives() {
    g_archives.clear();
    g_currentMonth = getCurrentMonthKey();
    cout << "All archives cleared." << endl;
}

// =========================================================================
// OOP CONCEPT: Interface Bridge / QML Wrappers
// Exposes standard C++ strings as C-strings (const char*) for QML UI binding
// =========================================================================

const char* getWelcomeMessageQml() {
    static string msg = getWelcomeMessage();
    return msg.c_str();
}

const char* getFormattedCurrentMonthSpendingQml() {
    static string formatted = getFormattedCurrentMonthSpending();
    return formatted.c_str();
}

const char* getFormattedTotalSpendingQml() {
    static string formatted = getFormattedTotalSpending();
    return formatted.c_str();
}

const char* getUserDisplayNameQml() {
    static string name = getUserDisplayName();
    return name.c_str();
}

const char* getUserDisplayEmailQml() {
    static string email = getUserDisplayEmail();
    return email.c_str();
}

const char* getTimeBasedGreetingQml() {
    static string greeting = getTimeBasedGreeting();
    return greeting.c_str();
}

const char* getFullGreetingQml() {
    static string greeting = getFullGreeting();
    return greeting.c_str();
}

const char* getPreviousMonthNameQml() {
    static string name = getPreviousMonthName();
    return name.c_str();
}

#endif