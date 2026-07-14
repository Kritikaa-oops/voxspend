#ifndef AUTH_MANAGER_H
#define AUTH_MANAGER_H

#include "../expense.h"
#include <vector>
#include <string>

using namespace std;

// ============ GLOBAL DATA ============
extern vector<User> g_users;
extern User g_currentUser;
extern string g_lastAuthError;

// ============ LOGIN FUNCTIONS ============
bool loginUser(const string& email, const string& password);
bool isUserLoggedIn();
string getCurrentUserEmail();
string getCurrentUserName();
string getLastAuthError();
void clearAuthError();

// ============ LOGOUT FUNCTIONS ============
void logoutUser();
string getCurrentUserProfileName();
string getCurrentUserProfileEmail();

// ============ SIGNUP FUNCTIONS ============
bool registerUser(const string& name, const string& email, const string& password, const string& confirmPassword);
bool registerUserWithPhone(const string& name, const string& phone, const string& password, const string& confirmPassword);

// ============ EDIT PROFILE FUNCTIONS ============
bool updateUserProfile(const string& newName, const string& newEmail);

#endif