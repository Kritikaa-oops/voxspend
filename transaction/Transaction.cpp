#include "TransactionManager.h"
#include "ExpenseManager.h"
#include <algorithm>
#include <map>

// ============ TRANSACTION FUNCTIONS ============

vector<Expense> getExpenses() { return g_expenses; }

bool deleteExpense(int id) {
    size_t before = g_expenses.size();
    g_expenses.erase(remove_if(g_expenses.begin(), g_expenses.end(),
        [id](const Expense& e) { return e.id == id; }), g_expenses.end());
    if (g_expenses.size() < before) return true;
    g_lastExpenseError = "Expense not found";
    return false;
}

bool editExpense(int id, const string& title, double amount, const string& category, const string& date, const string& note) {
    for (auto& e : g_expenses) {
        if (e.id == id) {
            e.category = category;
            e.amount = amount;
            e.date = date;
            e.description = title + (note.empty() ? "" : " - " + note);
            return true;
        }
    }
    g_lastExpenseError = "Expense not found";
    return false;
}

int getExpenseCount() { return g_expenses.size(); }

double getTotalExpenses() {
    double total = 0;
    for (const auto& e : g_expenses) total += e.amount;
    return total;
}

double getTotalForCategory(const string& category) {
    double total = 0;
    for (const auto& e : g_expenses) {
        if (e.category == category) total += e.amount;
    }
    return total;
}

vector<Expense> getRecentExpenses(int count) {
    vector<Expense> sorted = g_expenses;
    sort(sorted.begin(), sorted.end(), [](const Expense& a, const Expense& b) { return a.id > b.id; });
    int c = min(count, (int)sorted.size());
    return vector<Expense>(sorted.begin(), sorted.begin() + c);
}

// ============ CHART FUNCTIONS ============

vector<pair<string, double>> getCategoryWiseSummary() {
    map<string, double> totals;
    for (const auto& e : g_expenses) totals[e.category] += e.amount;
    vector<pair<string, double>> result(totals.begin(), totals.end());
    sort(result.begin(), result.end(), [](auto& a, auto& b) { return a.second > b.second; });
    return result;
}

double getHighestExpense() {
    if (g_expenses.empty()) return 0;
    double max = g_expenses[0].amount;
    for (const auto& e : g_expenses) if (e.amount > max) max = e.amount;
    return max;
}

double getAverageExpense() {
    if (g_expenses.empty()) return 0;
    return getTotalExpenses() / g_expenses.size();
}

string getHighestCategory() {
    auto summary = getCategoryWiseSummary();
    if (summary.empty()) return "No data";
    return summary[0].first;
}

// ============ CATEGORY FUNCTIONS ============

vector<CategoryCardData> getCategoryCardData() {
    vector<CategoryCardData> result;
    auto totals = getCategoryWiseSummary();
    double total = getTotalExpenses();
    for (const auto& p : totals) {
        CategoryCardData d;
        d.name = p.first;
        d.amount = p.second;
        d.percentage = (total > 0) ? (p.second / total) * 100 : 0;
        result.push_back(d);
    }
    return result;
}

double getCategoryAmount(const string& category) {
    return getTotalForCategory(category);
}