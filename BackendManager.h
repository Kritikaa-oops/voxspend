#ifndef BACKEND_MANAGER_H
#define BACKEND_MANAGER_H

// ============ SHARED STRUCTS ============
#include "expense.h"

// ============ AUTHENTICATION MODULE ============
#include "auth/Login.cpp"
#include "auth/Logout.cpp"
#include "auth/Signup.cpp"
#include "auth/EditProfile.cpp"

// ============ EXPENSE MODULE ============
#include "expense/AddExpense.cpp"

// ============ TRANSACTION MODULE ============
#include "transaction/Transaction.cpp"
#include "transaction/Charts.cpp"
#include "transaction/Category.cpp"

// ============ HOMEPAGE MODULE ============
#include "HomePage.cpp"

// ============ GLOBAL DATA DECLARATIONS ============
extern vector<User> g_users;
extern User g_currentUser;
extern string g_lastAuthError;

extern vector<Expense> g_expenses;
extern int g_nextId;
extern string g_lastExpenseError;

#endif