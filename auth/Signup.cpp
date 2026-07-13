#ifndef SIGNUP_CPP
#define SIGNUP_CPP

#include "../expense.h"
#include <vector>
#include <string>
#include <iostream>
#include <cctype>
#include <regex>

using namespace std;

// ============ GLOBAL DATA (Shared with Login.cpp) ============
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

bool isValidPhoneNumber(const string& phone) {
    if (phone.empty()) {
        return false;
    }
    
    // Remove spaces, hyphens, parentheses
    string cleaned = phone;
    cleaned.erase(remove_if(cleaned.begin(), cleaned.end(), 
        [](char c) { return c == ' ' || c == '-' || c == '(' || c == ')' || c == '+'; }), 
        cleaned.end());
    
    // Check if contains only digits
    for (char c : cleaned) {
        if (!isdigit(c)) {
            return false;
        }
    }
    
    // Phone number should be between 7 and 15 digits
    return cleaned.length() >= 7 && cleaned.length() <= 15;
}

bool isValidPassword(const string& password) {
    if (password.length() < 6) {
        return false;
    }
    
    if (password.length() > 30) {
        return false;
    }
    
    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    
    for (char c : password) {
        if (isupper(c)) hasUpper = true;
        if (islower(c)) hasLower = true;
        if (isdigit(c)) hasDigit = true;
    }
    
    return hasUpper && hasLower && hasDigit;
}

bool isValidName(const string& name) {
    if (name.empty()) {
        return false;
    }
    
    if (name.length() < 2) {
        return false;
    }
    
    if (name.length() > 50) {
        return false;
    }
    
    // Check if name contains only letters, spaces, hyphens, and apostrophes
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

User* findUserByPhone(const string& phone) {
    for (auto& user : g_users) {
        if (user.phone == phone) {
            return &user;
        }
    }
    return nullptr;
}

// ============ SIGNUP FUNCTIONS (SignupPage.qml) ============

bool registerUser(const string& name, const string& email, const string& password, const string& confirmPassword) {
    // Validate name
    if (!isValidName(name)) {
        g_lastAuthError = "Please enter a valid name (min 2 characters, letters only).";
        cerr << "Error: " << g_lastAuthError << endl;
        return false;
    }
    
    // Validate email
    if (!isValidEmail(email)) {
        g_lastAuthError = "Please enter a valid email address.";
        cerr << "Error: " << g_lastAuthError << endl;
        return false;
    }
    
    // Check if email already exists
    if (findUserByEmail(email) != nullptr) {
        g_lastAuthError = "Email already registered. Please use a different email.";
        cerr << "Error: " << g_lastAuthError << endl;
        return false;
    }
    
    // Validate password
    if (!isValidPassword(password)) {
        g_lastAuthError = "Password must be at least 6 characters with uppercase, lowercase, and digit.";
        cerr << "Error: " << g_lastAuthError << endl;
        return false;
    }
    
    // Check if passwords match
    if (password != confirmPassword) {
        g_lastAuthError = "Passwords do not match. Please re-enter.";
        cerr << "Error: " << g_lastAuthError << endl;
        return false;
    }
    
    // Create new user
    User newUser;
    newUser.name = name;
    newUser.email = email;
    newUser.password = password;
    newUser.phone = "";  // Optional - can be set later
    newUser.profilePicture = "";  // Optional - can be set later
    
    g_users.push_back(newUser);
    
    cout << "========================================" << endl;
    cout << "  ✅ USER REGISTERED SUCCESSFULLY" << endl;
    cout << "========================================" << endl;
    cout << "  Name:   " << newUser.name << endl;
    cout << "  Email:  " << newUser.email << endl;
    cout << "========================================" << endl;
    
    g_lastAuthError = "";
    return true;
}

// Optional: Register with phone number instead of email
bool registerUserWithPhone(const string& name, const string& phone, const string& password, const string& confirmPassword) {
    // Validate name
    if (!isValidName(name)) {
        g_lastAuthError = "Please enter a valid name (min 2 characters, letters only).";
        cerr << "Error: " << g_lastAuthError << endl;
        return false;
    }
    
    // Validate phone
    if (!isValidPhoneNumber(phone)) {
        g_lastAuthError = "Please enter a valid phone number (7-15 digits).";
        cerr << "Error: " << g_lastAuthError << endl;
        return false;
    }
    
    // Check if phone already exists
    if (findUserByPhone(phone) != nullptr) {
        g_lastAuthError = "Phone number already registered. Please use a different number.";
        cerr << "Error: " << g_lastAuthError << endl;
        return false;
    }
    
    // Validate password
    if (!isValidPassword(password)) {
        g_lastAuthError = "Password must be at least 6 characters with uppercase, lowercase, and digit.";
        cerr << "Error: " << g_lastAuthError << endl;
        return false;
    }
    
    // Check if passwords match
    if (password != confirmPassword) {
        g_lastAuthError = "Passwords do not match. Please re-enter.";
        cerr << "Error: " << g_lastAuthError << endl;
        return false;
    }
    
    // Create new user
    User newUser;
    newUser.name = name;
    newUser.email = "";  // Optional - can be set later
    newUser.phone = phone;
    newUser.password = password;
    newUser.profilePicture = "";
    
    g_users.push_back(newUser);
    
    cout << "========================================" << endl;
    cout << "  ✅ USER REGISTERED SUCCESSFULLY" << endl;
    cout << "========================================" << endl;
    cout << "  Name:   " << newUser.name << endl;
    cout << "  Phone:  " << newUser.phone << endl;
    cout << "========================================" << endl;
    
    g_lastAuthError = "";
    return true;
}

// ============ GETTER FUNCTIONS ============

string getLastAuthError() {
    return g_lastAuthError;
}

void clearAuthError() {
    g_lastAuthError = "";
}

#endif