#include "expense_logic.h"
#include <algorithm>
#include <iostream>
#include <cctype>

vector<Expense> allExpenses;
vector<User> allUsers;
User currentUser;
static int nextId = 1;

// ============ EXPENSE FUNCTIONS ============

bool addExpense(const string& category, double amount, const string& date, const string& description) {
    if (amount <= 0) {
        cerr << "Error: Amount must be positive." << endl;
        return false;
    }
    
    if (category.empty()) {
        cerr << "Error: Category cannot be empty." << endl;
        return false;
    }
    
    if (date.empty()) {
        cerr << "Error: Date cannot be empty." << endl;
        return false;
    }
    
    Expense newExpense;
    newExpense.id = nextId++;
    newExpense.category = category;
    newExpense.amount = amount;
    newExpense.date = date;
    newExpense.description = description;
    
    allExpenses.push_back(newExpense);
    return true;
}

bool deleteExpense(int id) {
    size_t sizeBefore = allExpenses.size();
    
    allExpenses.erase(
        remove_if(allExpenses.begin(), allExpenses.end(),
                  [id](const Expense& e) { return e.id == id; }),
        allExpenses.end()
    );
    
    return allExpenses.size() < sizeBefore;
}

bool editExpense(int id, const string& newCategory, double newAmount, const string& newDescription) {
    for (auto& expense : allExpenses) {
        if (expense.id == id) {
            if (newAmount <= 0) {
                cerr << "Error: Amount must be positive." << endl;
                return false;
            }
            
            if (newCategory.empty()) {
                cerr << "Error: Category cannot be empty." << endl;
                return false;
            }
            
            expense.category = newCategory;
            expense.amount = newAmount;
            expense.description = newDescription;
            return true;
        }
    }
    
    cerr << "Error: Expense with ID " << id << " not found." << endl;
    return false;
}

Expense* findExpenseById(int id) {
    for (auto& expense : allExpenses) {
        if (expense.id == id) {
            return &expense;
        }
    }
    return nullptr;
}

double getTotalForCategory(const string& category) {
    double total = 0.0;
    
    for (const auto& expense : allExpenses) {
        if (expense.category == category) {
            total += expense.amount;
        }
    }
    
    return total;
}

double getTotalExpense() {
    double total = 0.0;
    
    for (const auto& expense : allExpenses) {
        total += expense.amount;
    }
    
    return total;
}

vector<Expense>& getExpenses() {
    return allExpenses;
}

void setExpenses(const vector<Expense>& expenses) {
    allExpenses = expenses;
    
    int maxId = 0;
    for (const auto& expense : allExpenses) {
        if (expense.id > maxId) {
            maxId = expense.id;
        }
    }
    nextId = maxId + 1;
}

void clearExpenses() {
    allExpenses.clear();
    nextId = 1;
}

int generateNextId() {
    return nextId;
}

// ============ USER AUTHENTICATION FUNCTIONS (UPDATED) ============

bool validateEmail(const string& email) {
    if (email.empty()) {
        cerr << "Error: Email cannot be empty." << endl;
        return false;
    }
    
    if (email.length() > 100) {
        cerr << "Error: Email too long." << endl;
        return false;
    }
    
    // Check for @ symbol
    size_t atPos = email.find('@');
    if (atPos == string::npos) {
        cerr << "Error: Invalid email format (missing @)." << endl;
        return false;
    }
    
    // Check for dot after @
    string domain = email.substr(atPos);
    if (domain.find('.') == string::npos) {
        cerr << "Error: Invalid email format (missing domain)." << endl;
        return false;
    }
    
    return true;
}

bool validatePassword(const string& password) {
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

User* findUserByEmail(const string& email) {
    for (auto& user : allUsers) {
        if (user.email == email) {
            return &user;
        }
    }
    return nullptr;
}

bool registerUser(const string& email, const string& password, const string& name) {
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
    allUsers.push_back(newUser);
    
    cout << "User registered successfully: " << email << " (" << name << ")" << endl;
    return true;
}

bool loginUser(const string& email, const string& password) {
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
    
    currentUser = *user;
    cout << "Login successful! Welcome, " << user->name << "!" << endl;
    return true;
}

bool isUserLoggedIn() {
    return !currentUser.email.empty();
}

void logoutUser() {
    if (isUserLoggedIn()) {
        cout << "Goodbye, " << currentUser.name << "!" << endl;
        currentUser.email = "";
        currentUser.password = "";
        currentUser.name = "";
    }
}

string getCurrentUserName() {
    return currentUser.name;
}

string getCurrentUserEmail() {
    return currentUser.email;
}
