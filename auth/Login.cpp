#include "AuthManager.h"
#include <iostream>
#include <cctype>

// ============ GLOBAL DATA ============
vector<User> g_users;
User g_currentUser;
string g_lastAuthError = "";

// ============ PRIVATE HELPERS ============

bool isValidEmail(const string& email) {
    if (email.empty() || email.length() > 100) return false;
    size_t atPos = email.find('@');
    if (atPos == string::npos) return false;
    string domain = email.substr(atPos);
    if (domain.find('.') == string::npos) return false;
    return true;
}

User* findUserByEmail(const string& email) {
    for (auto& user : g_users) {
        if (user.email == email) return &user;
    }
    return nullptr;
}

// ============ LOGIN FUNCTIONS ============

bool loginUser(const string& email, const string& password) {
    if (email.empty() || password.empty()) {
        g_lastAuthError = "Email and password cannot be empty.";
        return false;
    }
    if (!isValidEmail(email)) {
        g_lastAuthError = "Invalid email format.";
        return false;
    }
    User* user = findUserByEmail(email);
    if (user == nullptr) {
        g_lastAuthError = "Email not found.";
        return false;
    }
    if (user->password != password) {
        g_lastAuthError = "Incorrect password.";
        return false;
    }
    g_currentUser = *user;
    g_lastAuthError = "";
    return true;
}

bool isUserLoggedIn() {
    return !g_currentUser.email.empty();
}

string getCurrentUserEmail() {
    return g_currentUser.email;
}

string getCurrentUserName() {
    return g_currentUser.name;
}

string getLastAuthError() {
    return g_lastAuthError;
}

void clearAuthError() {
    g_lastAuthError = "";
}