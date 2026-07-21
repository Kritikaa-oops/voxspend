#ifndef EDITPROFILE_CPP
#define EDITPROFILE_CPP

#include "BackendManager.h"
#include <string>

using namespace std;

bool updateUserProfile(const string& newName, const string& newEmail)
{
    return BackendManager{}.updateProfile(QString::fromStdString(newName), QString::fromStdString(newEmail));
}

string getCurrentUserProfileName()
{
    return BackendManager{}.currentUserName().toStdString();
}

string getCurrentUserProfileEmail()
{
    return BackendManager{}.currentUserEmail().toStdString();
}

string getLastAuthError()
{
    return BackendManager{}.getLastAuthError().toStdString();
}

void clearAuthError()
{
    BackendManager{}.clearAuthError();
}

#endif