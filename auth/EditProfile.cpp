#include "AuthManager.h"
#include <iostream>

// Simple local validation for user name: length between 2 and 50
static bool isValidName(const std::string& name) {
    size_t len = name.size();
    return len >= 2 && len <= 50;
}

// Simple local validation for email: must contain one '@' and at least one '.' after '@'
static bool isValidEmail(const std::string& email) {
    auto atPos = email.find('@');
    if (atPos == std::string::npos) return false;
    // ensure there's something before and after '@'
    if (atPos == 0 || atPos + 1 >= email.size()) return false;
    auto dotPos = email.find('.', atPos + 1);
    if (dotPos == std::string::npos) return false;
    // ensure at least one character between @ and . and after .
    if (dotPos == atPos + 1) return false;
    if (dotPos + 1 >= email.size()) return false;
    return true;
}

bool updateUserProfile(const string& newName, const string& newEmail) {
    if (g_currentUser.email.empty()) {
        g_lastAuthError = "No user logged in.";
        return false;
    }
    if (!isValidName(newName)) {
        g_lastAuthError = "Name must be 2-50 characters.";
        return false;
    }
    if (!isValidEmail(newEmail)) {
        g_lastAuthError = "Invalid email format.";
        return false;
    }
    if (newEmail != g_currentUser.email) {
        User* existing = findUserByEmail(newEmail);
        if (existing != nullptr && existing->email != g_currentUser.email) {
            g_lastAuthError = "Email already registered to another user.";
            return false;
        }
    }
    for (auto& user : g_users) {
        if (user.email == g_currentUser.email) {
            user.name = newName;
            user.email = newEmail;
            break;
        }
    }
    g_currentUser.name = newName;
    g_currentUser.email = newEmail;
    g_lastAuthError = "";
    return true;
}

// Helper to find a user by email in the global user list
static User* findUserByEmail(const std::string& email) {
    for (auto& user : g_users) {
        if (user.email == email) return &user;
    }
    return nullptr;
}