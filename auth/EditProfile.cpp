#ifndef EDITPROFILE_CPP
#define EDITPROFILE_CPP

#include "../expense.h"
#include <vector>
#include <string>
#include <iostream>
#include <cctype>

using namespace std;

// ============ GLOBAL DATA (Shared with Login.cpp) ============
extern vector<User> g_users;
extern User g_currentUser;
extern string g_lastAuthError;

// ============ PRIVATE HELPER FUNCTIONS (Shared) ============

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

bool isValidName(const string& name) {
    if (name.empty() || name.length() < 2 || name.length() > 50) {
        return false;
    }
    
    for (char c : name) {
        if (!isalpha(c) && c != ' ' && c != '-' && c != '\'') {
            return false;
        }
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

// ============ EDIT PROFILE FUNCTIONS (EditProfile.qml) ============

bool updateUserProfile(const string& newName, const string& newEmail) {
    // Check if user is logged in
    if (g_currentUser.email.empty()) {
        g_lastAuthError = "No user is currently logged in.";
        cerr << "Error: " << g_lastAuthError << endl;
        return false;
    }
    
    // Validate new name
    if (!isValidName(newName)) {
        g_lastAuthError = "Name must be 2-50 characters (letters, spaces, hyphens, apostrophes only).";
        cerr << "Error: " << g_lastAuthError << endl;
        return false;
    }
    
    // Validate new email
    if (!isValidEmail(newEmail)) {
        g_lastAuthError = "Please enter a valid email address.";
        cerr << "Error: " << g_lastAuthError << endl;
        return false;
    }
    
    // Check if email is already used by another user (only if email changed)
    if (newEmail != g_currentUser.email) {
        User* existingUser = findUserByEmail(newEmail);
        if (existingUser != nullptr && existingUser->email != g_currentUser.email) {
            g_lastAuthError = "Email already registered to another account.";
            cerr << "Error: " << g_lastAuthError << endl;
            return false;
        }
    }
    
    // Update user in the global users list
    for (auto& user : g_users) {
        if (user.email == g_currentUser.email) {
            user.name = newName;
            user.email = newEmail;
            break;
        }
    }
    
    // Update current user session
    g_currentUser.name = newName;
    g_currentUser.email = newEmail;
    
    cout << "========================================" << endl;
    cout << "  ✅ PROFILE UPDATED SUCCESSFULLY" << endl;
    cout << "========================================" << endl;
    cout << "  New Name:  " << g_currentUser.name << endl;
    cout << "  New Email: " << g_currentUser.email << endl;
    cout << "========================================" << endl;
    
    g_lastAuthError = "";
    return true;
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

string getLastAuthError() {
    return g_lastAuthError;
}

void clearAuthError() {
    g_lastAuthError = "";
}

#endif