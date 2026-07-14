#ifndef BACKEND_MANAGER_H
#define BACKEND_MANAGER_H

// ============ SHARED STRUCTS ============
#include "expense.h"

// ============ AUTHENTICATION ============
#include "auth/AuthManager.h"
#include "auth/Login.cpp"
#include "auth/Logout.cpp"
#include "auth/Signup.cpp"
#include "auth/EditProfile.cpp"

// ============ EXPENSE ============
#include "expense/ExpenseManager.h"
#include "expense/AddExpense.cpp"

// ============ TRANSACTION ============
#include "transaction/TransactionManager.h"
#include "transaction/Transaction.cpp"

// ============ HOMEPAGE ============
#include "HomePage.h"
#include "HomePage.cpp"

#endif