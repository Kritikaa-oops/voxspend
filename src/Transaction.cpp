#include "expense.h"
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

extern vector<Expense> g_expenses;
extern string g_lastExpenseError;

// Forward declare the bridge handlers instead of redefining the math engines
void deleteExpense(int id) {
    auto it = remove_if(g_expenses.begin(), g_expenses.end(),
                        [id](const Expense& e) { return e.id == id; });
    if (it != g_expenses.end()) {
        g_expenses.erase(it, g_expenses.end());
        g_lastExpenseError = "";
    } else {
        g_lastExpenseError = "Expense item not found.";
    }
}

vector<Expense> getRecentExpenses(int count) {
    vector<Expense> recent = g_expenses;
    // Sort in reverse order (newest first) assuming sequential IDs
    sort(recent.begin(), recent.end(), [](const Expense& a, const Expense& b) {
        return a.id > b.id;
    });

    if ((int)recent.size() > count) {
        recent.resize(count);
    }
    return recent;
}