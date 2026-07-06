#ifndef BACKEND_MANAGER_H
#define BACKEND_MANAGER_H

// ============ AUTHENTICATION ============
#include "auth/AuthManager.h"

// ============ EXPENSE MODULES ============
#include "expense/AddExpenseManager.h"
#include "expense/DashboardManager.h"

// ============ GLOBAL INSTANCES ============
extern AuthManager g_authManager;
extern AddExpenseManager g_addExpenseManager;
extern DashboardManager g_dashboardManager;

#endif
