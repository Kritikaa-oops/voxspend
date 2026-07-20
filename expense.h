#ifndef EXPENSE_H
#define EXPENSE_H

#include <string>

using namespace std;

struct Expense {
    int id;
    string category;
    double amount;
    string date;
    string description;
};

struct Budget {
    string category;
    double limit;
};

struct User {
    string username;
    string password;
};

#endif