#include"BackendManager.h"
#include "expense.h"
#include <string>

using namespace std;

// =========================================================================
// OOP CONCEPT: Global State & Object Reference
// References the active User object instance defined across the application
// =========================================================================
extern User g_currentUser;

// =========================================================================
// OOP CONCEPT: Object Re-initialization & Encapsulation
// Resets the active session by overwriting g_currentUser with a fresh, empty User object
// =========================================================================
void logoutUser() {
    g_currentUser = User(); // Reset current user session state back to default empty object
}

// =========================================================================
// OOP CONCEPT: Accessors / Getter Methods for QML Bridge
// Converts C++ std::string properties to C-style strings (const char*) for UI rendering
// =========================================================================

// Safe getter returning logged-in user's name to QML
const char* getCurrentUserProfileNameQml() {
    return g_currentUser.name.c_str();
}

// Safe getter returning logged-in user's email to QML
const char* getCurrentUserProfileEmailQml() {
    return g_currentUser.email.c_str();
}