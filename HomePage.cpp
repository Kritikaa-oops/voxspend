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

// ============ GLOBAL DATA (Shared with all files) ============
extern vector<Expense> g_expenses;
extern User g_currentUser;
extern int g_nextId;

// ============ MONTH RESET DATA ============
static vector<MonthlyArchive> g_archives;
static string g_currentMonth = "";
static bool g_monthResetTriggered = false;

// ============ MONTH RESET HELPER FUNCTIONS ============

string getCurrentMonthKey() {
    time_t now = time(nullptr);
    struct tm* tm = localtime(&now);
    char monthKey[8];
    snprintf(monthKey, sizeof(monthKey), "%04d-%02d", 
             tm->tm_year + 1900, tm->tm_mon + 1);
    return string(monthKey);
}

bool isNewMonth() {
    if (g_currentMonth.empty()) {
        g_currentMonth = getCurrentMonthKey();
        return false;
    }
    return g_currentMonth != getCurrentMonthKey();
}

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
    
    MonthlyArchive archive;
    archive.month = g_currentMonth;
    archive.archivedExpenses = g_expenses;
    
    double total = 0.0;
    for (const auto& exp : g_expenses) {
        total += exp.amount;
    }
    archive.totalSpent = total;
    
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

string getWelcomeMessage() {
    if (!g_currentUser.email.empty()) {
        return "Welcome, " + g_currentUser.name + "!";
    }
    return "Welcome to VoxSpend";
}

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

vector<RecentTransaction> getRecentTransactions(int count) {
    vector<RecentTransaction> result;
    
    vector<Expense> sorted = g_expenses;
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

bool hasTransactions() {
    return !g_expenses.empty();
}

int getTotalExpenseCount() {
    return g_expenses.size();
}

double getTotalSpending() {
    double total = 0.0;
    for (const auto& expense : g_expenses) {
        total += expense.amount;
    }
    return total;
}

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

string getUserDisplayName() {
    if (!g_currentUser.email.empty()) {
        return g_currentUser.name;
    }
    return "Guest";
}

string getUserDisplayEmail() {
    if (!g_currentUser.email.empty()) {
        return g_currentUser.email;
    }
    return "guest@example.com";
}

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

string getFullGreeting() {
    string greeting = getTimeBasedGreeting();
    string name = getUserDisplayName();
    
    if (name != "Guest") {
        return greeting + ", " + name + "!";
    }
    return greeting + "!";
}

DashboardSummary getDashboardSummary() {
    DashboardSummary summary;
    summary.totalSpent = getTotalSpending();
    summary.totalTransactions = getTotalExpenseCount();
    summary.currentMonthSpent = getCurrentMonthSpending();
    
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

vector<MonthlyArchive> getMonthlyArchives() {
    return g_archives;
}

MonthlyArchive getMonthSummary(const string& month) {
    for (const auto& archive : g_archives) {
        if (archive.month == month) {
            return archive;
        }
    }
    return MonthlyArchive();
}

double getPreviousMonthSpending() {
    if (g_archives.empty()) {
        return 0.0;
    }
    return g_archives.back().totalSpent;
}

string getPreviousMonthName() {
    if (g_archives.empty()) {
        return "No previous month";
    }
    return g_archives.back().month;
}

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

void clearArchives() {
    g_archives.clear();
    g_currentMonth = getCurrentMonthKey();
    cout << "All archives cleared." << endl;
}

// ============ QML EXPOSED FUNCTIONS (with Qml suffix) ============

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