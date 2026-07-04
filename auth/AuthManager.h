#ifndef AUTH_MANAGER_H
#define AUTH_MANAGER_H

#include "../expense.h"
#include <vector>
#include <string>

using namespace std;

class AuthManager {
private:
    vector<User> m_users;
    User m_currentUser;
    
public:
    AuthManager();
    
    // ============ LOGIN (login.qml) ============
    bool loginUser(const string& email, const string& password);
    bool isUserLoggedIn() const;
    
    // ============ LOGOUT (logout.qml) ============
    void logoutUser();
    string getCurrentUserName() const;
    string getCurrentUserEmail() const;
    
    // ============ SIGNUP (signup.qml) ============
    bool registerUser(const string& email, const string& password, const string& name);
    bool validateEmail(const string& email) const;
    bool validatePassword(const string& password) const;
    User* findUserByEmail(const string& email);
    
    // ============ USER MANAGEMENT ============
    void setUsers(const vector<User>& users);
    const vector<User>& getUsers() const;
};

#endif