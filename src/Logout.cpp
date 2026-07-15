#include "BackendManager.h"
#include "expense.h"
#include <string>

using namespace std;

extern User g_currentUser;

void logoutUser() {
    g_currentUser = User(); // Reset the current user to empty
}

const char* getCurrentUserProfileNameQml() {
    return g_currentUser.name.c_str();
}

const char* getCurrentUserProfileEmailQml() {
    return g_currentUser.email.c_str();
}