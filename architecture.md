VoxSpend-Expense-Tracker/
│
├── .git/                               # Git repository
├── .gitignore                          # Git ignore file
├── README.md                           # Project documentation
├── LICENSE                             # License file
├── CMakeLists.txt                      # CMake build configuration
├── VoxSpend.pro                        # Qt project file
│
├── docs/                               # Documentation
│   ├── architecture.md                 # Architecture overview
│   ├── api_reference.md                # API documentation
│   ├── setup_guide.md                  # Setup instructions
│   ├── user_manual.md                  # User guide
│   └── diagrams/                       # UML and flow diagrams
│       ├── class_diagram.puml
│       ├── sequence_diagram.puml
│       └── architecture_diagram.png
│
├── src/                                # Source code
│   ├── main.cpp                        # Application entry point
│   │
│   ├── backend/                        # Backend Core Logic (YOUR ROLE)
│   │   ├── expense/                    # Expense module
│   │   │   ├── Expense.h
│   │   │   ├── Expense.cpp
│   │   │   ├── ExpenseManager.h
│   │   │   └── ExpenseManager.cpp
│   │   │
│   │   ├── budget/                     # Budget module
│   │   │   ├── BudgetManager.h
│   │   │   ├── BudgetManager.cpp
│   │   │   ├── BudgetCategory.h
│   │   │   └── BudgetCategory.cpp
│   │   │
│   │   ├── category/                   # Category module
│   │   │   ├── Category.h
│   │   │   ├── Category.cpp
│   │   │   └── CategoryManager.h
│   │   │
│   │   └── utils/                      # Utility functions
│   │       ├── Helpers.h
│   │       ├── Helpers.cpp
│   │       ├── DateUtils.h
│   │       └── DateUtils.cpp
│   │
│   ├── ui/                             # Frontend - UI Screens
│   │   ├── mainwindow/                 # Main window
│   │   │   ├── MainWindow.h
│   │   │   ├── MainWindow.cpp
│   │   │   └── MainWindow.ui
│   │   │
│   │   ├── dashboard/                  # Dashboard screen
│   │   │   ├── DashboardWidget.h
│   │   │   ├── DashboardWidget.cpp
│   │   │   └── DashboardWidget.ui
│   │   │
│   │   ├── expense/                    # Expense screens
│   │   │   ├── AddExpenseDialog.h
│   │   │   ├── AddExpenseDialog.cpp
│   │   │   ├── AddExpenseDialog.ui
│   │   │   ├── EditExpenseDialog.h
│   │   │   ├── EditExpenseDialog.cpp
│   │   │   ├── EditExpenseDialog.ui
│   │   │   └── ExpenseListView.h
│   │   │
│   │   ├── budget/                     # Budget screens
│   │   │   ├── BudgetScreen.h
│   │   │   ├── BudgetScreen.cpp
│   │   │   ├── BudgetScreen.ui
│   │   │   └── BudgetWidget.h
│   │   │
│   │   ├── reports/                    # Reports screens
│   │   │   ├── ReportsScreen.h
│   │   │   ├── ReportsScreen.cpp
│   │   │   └── ReportsScreen.ui
│   │   │
│   │   └── history/                    # History screens
│   │       ├── HistoryScreen.h
│   │       ├── HistoryScreen.cpp
│   │       └── HistoryScreen.ui
│   │
│   ├── controllers/                    # UI Controllers & Logic
│   │   ├── AppController.h
│   │   ├── AppController.cpp
│   │   ├── DashboardController.h
│   │   ├── DashboardController.cpp
│   │   ├── ExpenseController.h
│   │   ├── ExpenseController.cpp
│   │   ├── BudgetController.h
│   │   └── BudgetController.cpp
│   │
│   ├── storage/                        # JSON Data Storage
│   │   ├── JSONManager.h
│   │   ├── JSONManager.cpp
│   │   ├── StorageInterface.h
│   │   ├── FileManager.h
│   │   └── FileManager.cpp
│   │
│   ├── history/                        # History & Alarm System
│   │   ├── HistoryManager.h
│   │   ├── HistoryManager.cpp
│   │   ├── AlarmSystem.h
│   │   ├── AlarmSystem.cpp
│   │   ├── NotificationManager.h
│   │   └── NotificationManager.cpp
│   │
│   └── models/                         # Data Models
│       ├── ExpenseModel.h
│       ├── ExpenseModel.cpp
│       ├── BudgetModel.h
│       ├── BudgetModel.cpp
│       └── CategoryModel.h
│
├── include/                            # Public headers
│   ├── VoxSpend_global.h
│   └── api/
│       ├── ExpenseAPI.h
│       ├── BudgetAPI.h
│       └── ReportAPI.h
│
├── resources/                          # Resources
│   ├── icons/                          # Icon files
│   │   ├── add.png
│   │   ├── delete.png
│   │   ├── edit.png
│   │   ├── settings.png
│   │   └── logo.png
│   │
│   ├── styles/                         # Stylesheets
│   │   ├── dark_style.qss
│   │   ├── light_style.qss
│   │   └── main_style.qss
│   │
│   └── fonts/                          # Custom fonts
│       └── Roboto/
│
├── tests/                              # Unit tests
│   ├── backend/
│   │   ├── test_expense.cpp
│   │   ├── test_expense_manager.cpp
│   │   └── test_budget_manager.cpp
│   │
│   ├── storage/
│   │   └── test_json_manager.cpp
│   │
│   └── ui/
│       └── test_controllers.cpp
│
├── data/                               # Data files
│   └── expenses.json                   # Expense data storage
│
└── scripts/                            # Build scripts
    ├── build.sh
    ├── test.sh
    └── deploy.sh
