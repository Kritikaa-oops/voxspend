#ifndef LOGIN_CPP
#define LOGIN_CPP

#include "../expense.h"
#include <vector>
#include <string>
#include <iostream>
#include <cctype>

using namespace std;

// ============ GLOBAL DATA ============
extern vector<User> g_users;
extern User g_currentUser;
extern string g_lastAuthError;

// ============ PRIVATE HELPER FUNCTIONS ============

bool isValidEmail(const string& email) {
    if (email.empty() || email.length() > 100) {
        return false;
    }
    
    size_t atPos = email.find('@');
    if (atPos == string::npos) {
        return false;
    }
    
    string domain = email.substr(atPos);
    if (domain.find('.') == string::npos) {
        return false;
    }
    
    return true;
}

User* findUserByEmail(const string& email) {
    for (auto& user : g_users) {
        if (user.email == email) {
            return &user;
        }
    }
    return nullptr;
}

// ============ LOGIN FUNCTIONS (BACKEND VERSION) ============

bool loginUser(const string& email, const string& password) {
    if (email.empty() || password.empty()) {
        g_lastAuthError = "Email and password cannot be empty.";
        cerr << "Error: " << g_lastAuthError << endl;
        return false;
    }
    
    if (!isValidEmail(email)) {
        g_lastAuthError = "Invalid email format.";
        cerr << "Error: " << g_lastAuthError << endl;
        return false;
    }
    
    User* user = findUserByEmail(email);
    
    if (user == nullptr) {
        g_lastAuthError = "Email not found.";
        cerr << "Error: " << g_lastAuthError << endl;
        return false;
    }
    
    if (user->password != password) {
        g_lastAuthError = "Incorrect password.";
        cerr << "Error: " << g_lastAuthError << endl;
        return false;
    }
    
    g_currentUser = *user;
    
    cout << "========================================" << endl;
    cout << "  ✅ LOGIN SUCCESSFUL" << endl;
    cout << "========================================" << endl;
    cout << "  Welcome, " << g_currentUser.name << "!" << endl;
    cout << "  Email: " << g_currentUser.email << endl;
    cout << "========================================" << endl;
    
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

// ============ QML EXPOSED FUNCTIONS (with Qml suffix) ============

const char* getCurrentUserNameQml() {
    static string name = getCurrentUserName();
    return name.c_str();
}

const char* getCurrentUserEmailQml() {
    static string email = getCurrentUserEmail();
    return email.c_str();
}

const char* getLastAuthErrorQml() {
    static string error = getLastAuthError();
    return error.c_str();
}

#endif