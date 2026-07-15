#include "expense.h"
#include "BackendManager.h"
#include <vector>
#include <string>

using namespace std;

// EXTERN REFERENCES: Borrows allocations safely from BackendManager.cpp
extern vector<User> g_users;
extern User g_currentUser;
extern string g_lastAuthError;
extern vector<Expense> g_expenses;
extern int g_nextId;
extern string g_lastExpenseError;

// FORWARD DECLARATIONS ONLY: No code bodies here, preventing collisions!
bool isUserLoggedIn();
const char* getCurrentUserNameQml();
const char* getCurrentUserEmailQml();
const char* getLastAuthErrorQml();
void clearAuthError();
void logoutUser();
const char* getCurrentUserProfileNameQml();
const char* getCurrentUserProfileEmailQml();

bool verifySystemInitialization() {
    return true;
}