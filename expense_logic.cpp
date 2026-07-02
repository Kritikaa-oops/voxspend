#include "expense_logic.h"
#include <algorithm>
#include <iostream>
#include <cctype>

vector<Expense> allExpenses;
vector<User> allUsers;
User currentUser;
static int nextId = 1;

// ============ EXPENSE FUNCTIONS (MINIMAL - REQUIRED FOR COMPILATION) ============

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

// ============ LOGIN/SIGNUP FUNCTIONS ============

bool validateUsername(const string& username) {
    if (username.length() < 3) {
        cerr << "Error: Username must be at least 3 characters." << endl;
        return false;
    }
    
    if (username.length() > 20) {
        cerr << "Error: Username cannot exceed 20 characters." << endl;
        return false;
    }
    
    for (char c : username) {
        if (!isalnum(c) && c != '_') {
            cerr << "Error: Username can only contain letters, numbers, and underscores." << endl;
            return false;
        }
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

User* findUserByUsername(const string& username) {
    for (auto& user : allUsers) {
        if (user.username == username) {
            return &user;
        }
    }
    return nullptr;
}

bool registerUser(const string& username, const string& password) {
    if (!validateUsername(username)) {
        return false;
    }
    
    if (!validatePassword(password)) {
        return false;
    }
    
    if (findUserByUsername(username) != nullptr) {
        cerr << "Error: Username already exists." << endl;
        return false;
    }
    
    User newUser;
    newUser.username = username;
    newUser.password = password;
    allUsers.push_back(newUser);
    
    cout << "User registered successfully: " << username << endl;
    return true;
}

bool loginUser(const string& username, const string& password) {
    if (username.empty() || password.empty()) {
        cerr << "Error: Username and password cannot be empty." << endl;
        return false;
    }
    
    User* user = findUserByUsername(username);
    
    if (user == nullptr) {
        cerr << "Error: Username not found." << endl;
        return false;
    }
    
    if (user->password != password) {
        cerr << "Error: Incorrect password." << endl;
        return false;
    }
    
    currentUser = *user;
    cout << "Login successful! Welcome, " << username << "!" << endl;
    return true;
}

bool isUserLoggedIn() {
    return !currentUser.username.empty();
}

void logoutUser() {
    if (isUserLoggedIn()) {
        cout << "Goodbye, " << currentUser.username << "!" << endl;
        currentUser.username = "";
        currentUser.password = "";
    }
}
