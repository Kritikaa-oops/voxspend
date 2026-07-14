#include "AuthManager.h"
#include <iostream>
#include <cctype>

User* findUserByEmail(const string& email);

bool isValidPassword(const string& password) {
    if (password.length() < 6 || password.length() > 30) return false;
    bool hasUpper = false, hasLower = false, hasDigit = false;
    for (char c : password) {
        if (isupper(c)) hasUpper = true;
        if (islower(c)) hasLower = true;
        if (isdigit(c)) hasDigit = true;
    }
    return hasUpper && hasLower && hasDigit;
}

bool isValidName(const string& name) {
    if (name.length() < 2 || name.length() > 50) return false;
    for (char c : name) {
        if (!isalpha(c) && c != ' ' && c != '-' && c != '\'') return false;
    }
    return true;
}

bool isValidEmail(const string& email) {
    if (email.empty()) return false;
    size_t atPos = email.find('@');
    if (atPos == string::npos || atPos == 0 || atPos + 1 >= email.length()) return false;
    size_t dotPos = email.find('.', atPos + 1);
    if (dotPos == string::npos || dotPos + 1 >= email.length()) return false;
    for (char c : email) {
        if (isspace(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

bool registerUser(const string& name, const string& email, const string& password, const string& confirmPassword) {
    if (!isValidName(name)) {
        g_lastAuthError = "Name must be 2-50 characters.";
        return false;
    }
    if (!isValidEmail(email)) {
        g_lastAuthError = "Invalid email format.";
        return false;
    }
    if (findUserByEmail(email) != nullptr) {
        g_lastAuthError = "Email already registered.";
        return false;
    }
    if (!isValidPassword(password)) {
        g_lastAuthError = "Password must be 6+ chars with uppercase, lowercase, digit.";
        return false;
    }
    if (password != confirmPassword) {
        g_lastAuthError = "Passwords do not match.";
        return false;
    }
    User newUser;
    newUser.name = name;
    newUser.email = email;
    newUser.password = password;
    g_users.push_back(newUser);
    g_lastAuthError = "";
    return true;
}

bool registerUserWithPhone(const string& name, const string& phone, const string& password, const string& confirmPassword) {
    // Similar implementation with phone validation
    g_lastAuthError = "Phone registration not implemented yet.";
    return false;
}