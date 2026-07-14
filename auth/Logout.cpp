#include "AuthManager.h"
#include <iostream>

void logoutUser() {
    if (!g_currentUser.email.empty()) {
        g_currentUser.email = "";
        g_currentUser.password = "";
        g_currentUser.name = "";
        g_lastAuthError = "";
    }
}

string getCurrentUserProfileName() {
    if (g_currentUser.email.empty()) return "Guest";
    return g_currentUser.name;
}

string getCurrentUserProfileEmail() {
    if (g_currentUser.email.empty()) return "guest@example.com";
    return g_currentUser.email;
}