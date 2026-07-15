# VoxSpend200: UI, Backend, and Database Architecture

## 1. Overview

VoxSpend200 is a Qt Quick desktop application with three layers:

```text
QML UI pages
    ↓  Q_INVOKABLE method calls
BackendManager (C++)
    ↓  prepared SQL queries
SQLite database
    ↑  QVariantList / QString / number results
QML UI pages
```

The application uses a local SQLite database. It persists user accounts and expenses between application runs. Each expense belongs to the authenticated user through `expenses.user_id`.

| Layer | Main files | Responsibility |
| --- | --- | --- |
| UI | `Main.qml`, `LoginPage.qml`, `SignupPage.qml`, `AddExpense.qml`, `EditProfile.qml` | Screens, user input, navigation, UI error messages |
| Bridge | `main.cpp` | Creates one C++ backend object and exposes it to all QML pages |
| Application logic | `BackendManager.h`, `BackendManager.cpp` | Validation, authentication session, logging, database queries |
| Storage | `voxspend200.sqlite` | Persistent `users` and `expenses` tables |

## 2. How QML reaches C++

`main.cpp` creates one `BackendManager` instance and exposes it under two QML names:

```cpp
BackendManager backend;

engine.rootContext()->setContextProperty("backend", &backend);
engine.rootContext()->setContextProperty("backendManager", &backend);
```

Therefore every QML page can call public `Q_INVOKABLE` methods:

```qml
backend.login(emailField.text, passwordField.text)
backend.signup(nameField.text, emailField.text,
               passwordField.text, confirmPasswordField.text)
backendManager.addExpense(titleField.text, amount,
                          categoryBox.currentText, date, noteField.text)
```

`backend` and `backendManager` currently refer to the same C++ object. New QML should prefer `backend`; `backendManager` remains available for the existing Add Expense page.

## 3. Database setup

The database is initialized by the `BackendManager` constructor:

```cpp
BackendManager::BackendManager(QObject* parent) : QObject(parent)
{
    m_databaseReady = initializeDatabase();
}
```

The file is created in Qt's application-data directory, not inside the source repository:

```cpp
const QString folder =
    QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
QDir().mkpath(folder);
return folder + "/voxspend200.sqlite";
```

### Tables

```sql
CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    email TEXT NOT NULL UNIQUE COLLATE NOCASE,
    password_salt TEXT NOT NULL,
    password_hash TEXT NOT NULL,
    created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE expenses (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    title TEXT NOT NULL,
    amount REAL NOT NULL CHECK(amount > 0),
    category TEXT NOT NULL,
    expense_date TEXT NOT NULL,
    note TEXT,
    created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY(user_id) REFERENCES users(id) ON DELETE CASCADE
);
```

The critical relationship is `expenses.user_id → users.id`. It prevents account A from reading account B's expenses because every expense query is filtered by the signed-in `m_currentUserId`.

## 4. Authentication flow

### Signup

1. The user fills in name, email, password, and confirmation in `SignupPage.qml`.
2. The page calls `backend.signup(...)`.
3. `BackendManager::signup()` validates all fields, hashes the password with a generated salt, and inserts a user row.
4. The newly created user becomes the current session and QML opens the dashboard.

Real QML usage:

```qml
if (backend.signup(nameField.text, emailField.text,
                   passwordField.text, confirmPasswordField.text)) {
    stackView.replace(homePage)
} else {
    authError = backend.getLastAuthError()
}
```

Real backend validation:

```cpp
if (password.length() < 8) {
    setAuthError("Password must contain at least 8 characters.");
    return false;
}
if (password != confirmPassword) {
    setAuthError("Passwords do not match.");
    return false;
}
```

The database insert uses bound values rather than string concatenation:

```cpp
query.prepare("INSERT INTO users (name, email, password_salt, password_hash) "
              "VALUES (?, ?, ?, ?)");
query.addBindValue(name);
query.addBindValue(email);
query.addBindValue(salt);
query.addBindValue(passwordHash(password, salt));
```

### Login

`LoginPage.qml` calls the backend and shows its error in the page rather than navigating on failure:

```qml
if (backend.login(emailField.text, passwordField.text)) {
    stackView.replace(homePage)
} else {
    authError = backend.getLastAuthError()
}
```

The backend reads the user by email, hashes the entered password with the stored salt, and compares hashes:

```cpp
query.prepare("SELECT id, name, email, password_salt, password_hash "
              "FROM users WHERE email = ?");
query.addBindValue(email);

if (!query.next() ||
    passwordHash(password, query.value(3).toString()) != query.value(4).toString()) {
    setAuthError("Email or password is incorrect.");
    return false;
}
```

On success, the backend stores the user ID in `m_currentUserId`. This is the authorization value used by every expense query.

## 5. Expense flow

### Add Expense page

`AddExpense.qml` validates its visible form, then sends the values to C++:

```qml
var saved = backendManager.addExpense(
    titleField.text,
    parseFloat(amountField.text) || 0,
    categoryBox.currentText,
    Qt.formatDate(new Date(), "yyyy-MM-dd"),
    noteField.text)

if (saved) {
    errorText.color = "#287A4B"
    errorText.text = "Expense saved."
} else {
    errorText.color = "#C7354A"
    errorText.text = backendManager.getLastExpenseError()
}
```

The C++ method prevents unauthenticated writes and inserts the current session's user ID:

```cpp
if (m_currentUserId < 0) {
    g_lastExpenseError = "Sign in before adding an expense.";
    return false;
}

query.prepare("INSERT INTO expenses "
              "(user_id, title, amount, category, expense_date, note) "
              "VALUES (?, ?, ?, ?, ?, ?)");
query.addBindValue(m_currentUserId);
query.addBindValue(title.trimmed());
query.addBindValue(amount);
```

## 6. Dashboard tabs and real data

`Main.qml` owns the persistent bottom navigation. The four tabs are loaded inside one shell; therefore Home, Activity, Insights, and Profile keep the bottom bar visible. Dedicated flows such as Add Expense and Edit Profile are opened with `StackView.push()` and provide a Back action.

| Tab | Backend method | Data returned |
| --- | --- | --- |
| Home | `getMonthlyTotal()` | Current signed-in user's spending for the current month |
| Activity | `getExpenses()` | `QVariantList` of the current user's expenses |
| Insights | `getCategoryTotals()`, `getExpenseCount()`, `getMonthlyTotal()` | Category totals, number of expenses, monthly total |
| Profile | `currentUserName()`, `currentUserEmail()` | Current session identity |

### Home total

```qml
Text {
    text: "Rs " + backend.getMonthlyTotal().toFixed(2)
}
```

The corresponding SQL is scoped by `user_id` and current month:

```sql
SELECT COALESCE(SUM(amount), 0)
FROM expenses
WHERE user_id = ?
  AND substr(expense_date, 1, 7) = strftime('%Y-%m', 'now', 'localtime');
```

### Activity list

`getExpenses()` returns a list of maps with `title`, `amount`, `category`, `date`, and `note`. The QML list delegate reads one map at a time:

```qml
ListView {
    model: activityPage.expenses
    delegate: Rectangle {
        Text { text: modelData.title }
        Text { text: modelData.category + "  •  " + modelData.date }
        Text { text: "- Rs " + Number(modelData.amount).toFixed(2) }
    }
}
```

The backend query is always user-scoped:

```sql
SELECT id, title, amount, category, expense_date, COALESCE(note, '')
FROM expenses
WHERE user_id = ?
ORDER BY expense_date DESC, id DESC;
```

### Insights

```qml
property var categoryTotals: backend.getCategoryTotals()

Repeater {
    model: insightsPage.categoryTotals
    Row {
        Text { text: modelData.category }
        Text { text: "Rs " + Number(modelData.amount).toFixed(2) }
    }
}
```

`getCategoryTotals()` uses `GROUP BY category`, again constrained to the authenticated user's ID.

### Profile update

`EditProfile.qml` starts with the current backend values:

```qml
TextField { text: backend.currentUserName() }
TextField { text: backend.currentUserEmail() }
```

Saving calls:

```qml
if (backend.updateProfile(nameInput.text, emailInput.text))
    stackView.pop()
else
    page.errorMessage = backend.getLastAuthError()
```

The backend updates the `users` row belonging to `m_currentUserId`, then updates the active in-memory session.

## 7. Error handling and logging

Errors are handled in two places:

1. **QML** clears an old error when the user edits a field and displays the new backend message directly below the form.
2. **C++** performs the authoritative validation and returns `false` on failure. It exposes the user-safe message through `getLastAuthError()` or `getLastExpenseError()`.

Examples of log messages written through Qt logging:

```cpp
qInfo().noquote() << "Account created for" << email;
qInfo().noquote() << "Sign in succeeded for" << email;
qWarning().noquote() << "Authentication failed:" << message;
```

Passwords and password hashes are never written to the log.

## 8. Presentation walkthrough

For a live presentation:

1. Create an account with a new email.
2. Show a validation failure (for example, mismatched passwords).
3. Create the account successfully and point out the automatic dashboard entry.
4. Add an expense such as `Lunch`, `450`, `Food`.
5. Open Activity to show the database-backed transaction.
6. Open Insights to show the category total and count.
7. Open Profile to show the authenticated email, then edit the name or email.
8. Sign out and sign back in to demonstrate persistent SQLite storage.

## 9. Next backend steps

- Add password-reset and password-change flows.
- Add date range and category filtering to Activity.
- Add edit/delete expense operations with ownership checks.
- Add budget tables and category limits.
- Replace direct QML refreshes with `BackendManager` signals so open tabs refresh immediately after saving.
- For production deployment, use a stronger password-hashing/KDF policy and platform-secure secret storage where appropriate.
