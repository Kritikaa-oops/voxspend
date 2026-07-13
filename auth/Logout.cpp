#ifndef LOGOUT_CPP
#define LOGOUT_CPP

#include "../expense.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

// ============ GLOBAL DATA (Shared with Login.cpp) ============
extern vector<User> g_users;
extern User g_currentUser;
extern string g_lastAuthError;

// ============ LOGOUT FUNCTIONS (BACKEND VERSION) ============

void logoutUser() {
    if (!g_currentUser.email.empty()) {
        cout << "========================================" << endl;
        cout << "  Goodbye, " << g_currentUser.name << "!" << endl;
        cout << "========================================" << endl;
        
        g_currentUser.email = "";
        g_currentUser.password = "";
        g_currentUser.name = "";
        
        g_lastAuthError = "";
    }
}

string getCurrentUserProfileName() {
    if (g_currentUser.email.empty()) {
        return "Guest";
    }
    return g_currentUser.name;
}

string getCurrentUserProfileEmail() {
    if (g_currentUser.email.empty()) {
        return "guest@example.com";
    }
    return g_currentUser.email;
}

// ============ QML EXPOSED FUNCTIONS (with Qml suffix) ============

const char* getCurrentUserProfileNameQml() {
    static string name = getCurrentUserProfileName();
    return name.c_str();
}

const char* getCurrentUserProfileEmailQml() {
    static string email = getCurrentUserProfileEmail();
    return email.c_str();
}

#endif