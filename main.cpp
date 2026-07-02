// main.cpp - Minimal test
#include "expense_logic.h"
#include <iostream>

using namespace std;

int main() {
    cout << "=== VOXSPEND LOGIN/SIGNUP TEST ===" << endl;
    
    // Register user
    cout << "\n1. Registering user..." << endl;
    if (registerUser("testuser", "TestPass123")) {
        cout << "   ✅ Registration successful!" << endl;
    }
    
    // Login
    cout << "\n2. Logging in..." << endl;
    if (loginUser("testuser", "TestPass123")) {
        cout << "   ✅ Login successful!" << endl;
        cout << "   Welcome, " << currentUser.username << endl;
    }
    
    // Add expense
    cout << "\n3. Adding expense..." << endl;
    if (addExpense("Food", 500, "2026-07-02", "Lunch")) {
        cout << "   ✅ Expense added!" << endl;
        cout << "   Total spending: Rs." << getTotalExpense() << endl;
    }
    
    // Logout
    cout << "\n4. Logging out..." << endl;
    logoutUser();
    cout << "   ✅ Logged out!" << endl;
    
    cout << "\n=== TEST COMPLETED ===" << endl;
    return 0;
}
