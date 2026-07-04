#include "AuthManager.h"
#include <iostream>
#include <cctype>

AuthManager::AuthManager() {}

// ============ VALIDATION ============

bool AuthManager::validateEmail(const string& email) const {
    if (email.empty()) {
        cerr << "Error: Email cannot be empty." << endl;
        return false;
    }
    
    if (email.length() > 100) {
        cerr << "Error: Email too long." << endl;
        return false;
    }
    
    size_t atPos = email.find('@');
    if (atPos == string::npos) {
        cerr << "Error: Invalid email format (missing @)." << endl;
        return false;
    }
    
    string domain = email.substr(atPos);
    if (domain.find('.') == string::npos) {
        cerr << "Error: Invalid email format (missing domain)." << endl;
        return false;
    }
    
    return true;
}

bool AuthManager::validatePassword(const string& password) const {
    if (password.length() < 6) {
        cerr << "Error: Password must be at least 6 characters." << endl;
        return false;
    }
    
    if (password.length() > 30) {
        cerr << "Error: Password cannot exceed 30 characters." << endl;
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
    
    if (!hasUpper || !hasLower || !hasDigit) {
        cerr << "Error: Password must contain uppercase, lowercase, and digit." << endl;
        return false;
    }
    
    return true;
}

User* AuthManager::findUserByEmail(const string& email) {
    for (auto& user : m_users) {
        if (user.email == email) {
            return &user;
        }
    }
    return nullptr;
}

// ============ SIGNUP (signup.qml) ============

bool AuthManager::registerUser(const string& email, const string& password, const string& name) {
    if (!validateEmail(email)) {
        return false;
    }
    
    if (!validatePassword(password)) {
        return false;
    }
    
    if (name.empty()) {
        cerr << "Error: Name cannot be empty." << endl;
        return false;
    }
    
    if (findUserByEmail(email) != nullptr) {
        cerr << "Error: Email already registered." << endl;
        return false;
    }
    
    User newUser;
    newUser.email = email;
    newUser.password = password;
    newUser.name = name;
    m_users.push_back(newUser);
    
    cout << "✅ User registered: " << email << " (" << name << ")" << endl;
    return true;
}

// ============ LOGIN (login.qml) ============

bool AuthManager::loginUser(const string& email, const string& password) {
    if (email.empty() || password.empty()) {
        cerr << "Error: Email and password cannot be empty." << endl;
        return false;
    }
    
    User* user = findUserByEmail(email);
    
    if (user == nullptr) {
        cerr << "Error: Email not found." << endl;
        return false;
    }
    
    if (user->password != password) {
        cerr << "Error: Incorrect password." << endl;
        return false;
    }
    
    m_currentUser = *user;
    cout << "✅ Login successful! Welcome, " << user->name << "!" << endl;
    return true;
}

// ============ LOGOUT (logout.qml) ============

void AuthManager::logoutUser() {
    if (isUserLoggedIn()) {
        cout << "Goodbye, " << m_currentUser.name << "!" << endl;
        m_currentUser = User();
    }
}

bool AuthManager::isUserLoggedIn() const {
    return !m_currentUser.email.empty();
}

string AuthManager::getCurrentUserName() const {
    return m_currentUser.name;
}

string AuthManager::getCurrentUserEmail() const {
    return m_currentUser.email;
}

// ============ USER MANAGEMENT ============

void AuthManager::setUsers(const vector<User>& users) {
    m_users = users;
}

const vector<User>& AuthManager::getUsers() const {
    return m_users;
}