#include "HomePage.h"
#include "auth/AuthManager.h"
#include "expense/ExpenseManager.h"
#include "transaction/TransactionManager.h"
#include <algorithm>
#include <ctime>
#include <map>

string getCurrentMonthKey() {
    time_t now = time(nullptr);
    struct tm* tm = localtime(&now);
    char monthKey[8];
    snprintf(monthKey, sizeof(monthKey), "%04d-%02d", tm->tm_year + 1900, tm->tm_mon + 1);
    return string(monthKey);
}

static vector<MonthlyArchive> g_archives;
static string g_currentMonth = "";

bool resetMonthIfNeeded() {
    string current = getCurrentMonthKey();
    if (g_currentMonth.empty()) { g_currentMonth = current; return false; }
    if (g_currentMonth == current) return false;
    MonthlyArchive archive;
    archive.month = g_currentMonth;
    archive.archivedExpenses = g_expenses;
    double total = 0;
    for (const auto& e : g_expenses) total += e.amount;
    archive.totalSpent = total;
    g_archives.push_back(archive);
    g_expenses.clear();
    g_nextId = 1;
    g_currentMonth = current;
    return true;
}

// ============ HOMEPAGE FUNCTIONS ============

string getWelcomeMessage() {
    if (!g_currentUser.email.empty()) return "Welcome, " + g_currentUser.name + "!";
    return "Welcome to VoxSpend";
}

double getCurrentMonthSpending() {
    resetMonthIfNeeded();
    double total = 0;
    string month = getCurrentMonthKey();
    for (const auto& e : g_expenses) {
        if (e.date.substr(0, 7) == month) total += e.amount;
    }
    return total;
}

string getFormattedCurrentMonthSpending() {
    double amount = getCurrentMonthSpending();
    return "Rs" + to_string((int)amount);
}

vector<RecentTransaction> getRecentTransactions(int count) {
    vector<RecentTransaction> result;
    vector<Expense> sorted = g_expenses;
    sort(sorted.begin(), sorted.end(), [](const Expense& a, const Expense& b) { return a.id > b.id; });
    int c = min(count, (int)sorted.size());
    for (int i = 0; i < c; i++) {
        RecentTransaction rt;
        rt.id = sorted[i].id;
        rt.title = sorted[i].description;
        rt.category = sorted[i].category;
        rt.amount = sorted[i].amount;
        rt.date = sorted[i].date;
        result.push_back(rt);
    }
    return result;
}

bool hasTransactions() { return !g_expenses.empty(); }

int getTotalExpenseCount() { return g_expenses.size(); }

double getTotalSpending() {
    double total = 0;
    for (const auto& e : g_expenses) total += e.amount;
    return total;
}

string getUserDisplayName() {
    if (!g_currentUser.email.empty()) return g_currentUser.name;
    return "Guest";
}

string getUserDisplayEmail() {
    if (!g_currentUser.email.empty()) return g_currentUser.email;
    return "guest@example.com";
}

string getTimeBasedGreeting() {
    time_t now = time(nullptr);
    struct tm* tm = localtime(&now);
    int hour = tm->tm_hour;
    if (hour < 12) return "Good Morning";
    if (hour < 17) return "Good Afternoon";
    if (hour < 21) return "Good Evening";
    return "Good Night";
}

string getFullGreeting() {
    return getTimeBasedGreeting() + ", " + getUserDisplayName() + "!";
}

DashboardSummary getDashboardSummary() {
    DashboardSummary ds;
    ds.totalSpent = getTotalSpending();
    ds.totalTransactions = getTotalExpenseCount();
    ds.currentMonthSpent = getCurrentMonthSpending();
    return ds;
}

// ============ MONTH RESET FUNCTIONS ============

vector<MonthlyArchive> getMonthlyArchives() { return g_archives; }

double getPreviousMonthSpending() {
    if (g_archives.empty()) return 0;
    return g_archives.back().totalSpent;
}

string getPreviousMonthName() {
    if (g_archives.empty()) return "No previous month";
    return g_archives.back().month;
}

MonthlyComparison getMonthComparison() {
    MonthlyComparison mc;
    mc.currentMonth = getCurrentMonthKey();
    mc.currentSpent = getCurrentMonthSpending();
    if (!g_archives.empty()) {
        mc.previousMonth = g_archives.back().month;
        mc.previousSpent = g_archives.back().totalSpent;
        mc.difference = mc.currentSpent - mc.previousSpent;
    }
    return mc;
}

void clearArchives() {
    g_archives.clear();
    g_currentMonth = getCurrentMonthKey();
}