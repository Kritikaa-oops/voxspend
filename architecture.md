# VoxSpend - Architecture Design Document

**Project Code:** Engg102

**Academic Year/Semester:** I Year / II Semester (Computer Science)

**Institution:** Kathmandu University, Department of Computer Science and Engineering

**Submission Date:** April 27, 2026

**Authors:** Kritika Chaulagain (Roll 23), Ritu Kandel (Roll 35), Deepti Khatri (Roll 45), Diya Khatri (Roll 46), Aayushma Kiju (Roll 47)

**Submitted to:** Mr. Suman Shrestha

---

## 1. Executive Overview

VoxSpend is an offline-first, highly responsive personal finance tracker designed specifically for university students in Nepal to bridge the budgeting "effort gap." While original conceptualizations included a voice-first entry mechanism, this finalized architecture pivots to a **highly optimized, manual UI-driven application**. This shift eliminates external audio-processing dependencies and thread-racing complexities, redirecting system resources toward guaranteeing instant data persistence, high visual responsiveness, and absolute local privacy.

### Tech Stack Blueprint

* **Frontend User Interface:** Qt Quick / QML (Declarative UI Framework)
* **Core Application Logic:** C++17 (Object-Oriented, Type-Safe Native Engine)


* **Data Persistence Layer:** JSON Local File Database (`QJsonDocument` / `QFile` Serialization)
* **Build Automation System:** CMake (3.16+)

---

## 2. Core Architectural Principles

To deliver a lightweight, secure tool capable of running smoothly on low-end hardware common in student hostels (e.g., Intel Core i3 / 4GB RAM systems), the architecture adheres to three core paradigms:

1. **Strict Model-View-Controller (MVC) Separation:** The UI layer (QML) remains completely decoupled from data storage and business rules. It communicates with the C++ engine strictly via Qt's asynchronous **Signals and Slots** mechanism and type-exposed properties.


2. **Offline-First & Privacy by Design:** Financial data is never transmitted over a network. Data processing, calculation, and persistence occur 100% on the local host machine, maintaining full performance without internet dependencies.


3. **Low-Overhead Data Serialization:** Eschewing heavy external relational databases (like SQL servers), VoxSpend reads a single, organized JSON ledger directly into memory on system boot, performing ultra-fast in-memory lookup and modifications before writing cleanly back to disk.



---

## 3. Detailed Component Decomposition

### 3.1. Presentation Layer (Frontend - QML)

The UI is built using Qt Quick and QML to deliver a modern, fluid visual experience. It is divided into two sub-modules:

* **Views (Full Screens):**
* `DashboardView.qml`: Displays dynamic financial health summaries, visual budget indicators, and spending graphs.


* `HistoryView.qml`: A scrollable transactional ledger implementing list view delegates for modifying or reviewing entries.


* `AddExpenseView.qml`: A form containing standardized inputs, dynamic validations, and category assignments.




* **Components (Reusable Widgets):**
* `CustomTextField.qml`: Standardized user entry boxes equipped with instantaneous character-type validation (e.g., rejecting text in numeric amount fields).


* `BudgetProgressBar.qml`: A smart visual gauge that dynamically changes colors (Green $\rightarrow$ Amber $\rightarrow$ Red) based on whether spending has crossed the midpoint or reached its maximum ceiling.


* `ExpenseCard.qml`: A modular card layout displaying itemized transaction details inside the history list.





### 3.2. Business Logic Layer (Backend - C++)

The native engine manages data transformations, structural evaluation, and UI state routing:

* **`ExpenseItem` (Data Model):** A Plain Old C++ Object (POCO) encapsulating single transaction tokens: UUID, numeric Amount, String Category (Food, Travel, Utilities, etc.), Date, and Description.


* **`ExpenseManager` (Application Controller):** The central structural hub inheriting from `QObject`. It contains methods exposed as `Q_INVOKABLE` or `public slots` to receive data signals directly from QML views, processes limits, and initiates file synchronization.



### 3.3. Storage Layer (Data Access - C++/JSON)

* **`JsonStorage` (Data Access Object):** Interacts natively with the device operating system using `QFile` streams. It converts collections of C++ objects into structured `QJsonArray` profiles and vice versa.



---

## 4. Comprehensive Directory Structure

The physical organization of project code maps explicitly to our conceptual tiers, fostering code reusability and isolated testing:

```text
VoxSpend/
|-- CMakeLists.txt                 # Global build instructions linking Qt6 modules
|-- README.md                      # Basic installation and compiler setup overview
|-- assets/                        # Compiled static production elements
|   `-- icons/                     # UI icons
|-- src/                           # Native C++ backend tiers
|   |-- main.cpp                   # App bootstrap; registers C++ controllers to the QML engine
|   |-- database/                  # File I/O streams and serialization framework
|   |   |-- json_storage.h         # Headers defining read/write disk cycles
|   |   `-- json_storage.cpp       # Mapping routines using QJsonDocument
|   |-- controllers/               # Business logic and signal coordination
|   |   |-- expense_manager.h      # Core manager definition containing exposed properties
|   |   `-- expense_manager.cpp    # Active math logic, sorting, and limit validations
|   `-- models/                    # Object structure representations
|       |-- expense_item.h         # Object representation data tokens
|       `-- expense_item.cpp       # Getter/setter declarations for single items
`-- ui/                            # QML declarative frontend tier
    |-- main.qml                   # Primary window wrapper and theme variables
    |-- qml.qrc                    # Resource compilation file mapping internal UI paths
    |-- components/                # Autonomous, reusable widget objects
    |   |-- CustomTextField.qml    # Validating text input wrapper
    |   |-- BudgetProgressBar.qml  # Dynamic contextual state-switching gauge
    |   `-- ExpenseCard.qml        # Item list delegate widget
    `-- views/                     # Dedicated screen architectures
        |-- DashboardView.qml      # Main view containing interactive reports and totals
        |-- HistoryView.qml        # Chronological ledger view displaying past entries
        `-- AddExpenseView.qml     # Manual structured data-entry matrix
```

---

## 5. System Data Flow

The following text-based sequence traces the linear operational execution when a user logs an expense, highlighting how data traverses the application boundary from QML to C++ and out to disk.

```text
User Interface (QML)                 Core Engine (C++)                 Storage File (Disk)
        |                                    |                                  |
        | 1. Submit add expense form        |                                  |
        |----------------------------------->|                                  |
        |                                    | 2. addExpense(...) validates     |
        |                                    |    amount, category, and date    |
        |                                    |                                  |
        |                                    | 3. Create ExpenseItem            |
        |                                    |                                  |
        |                                    | 4. Send ledger to JsonStorage    |
        |                                    |--------------------------------->|
        |                                    |                                  | 5. Write data.json
        |                                    |<---------------------------------|
        |                                    | 6. Emit dataChanged()            |
        |<-----------------------------------|                                  |
        | 7. Dashboard and history refresh   |                                  |
        |                                    |                                  |
```

---

## 6. Local Database Schema (`data.json`)

To maximize performance, transactions are nested sequentially within a root-level master ledger array. Budget configurations are declared as an independent object block for instant parsing extraction on boot.

```json
{
  "budget_settings": {
    "monthly_limit": 15000.00,
    "currency": "NPR",
    "last_updated": "2026-06-16"
  },
  "expenses": [
    {
      "id": "f81d4fae-7dec-11d0-a765-00a0c91e6bf6",
      "amount": 120.00,
      "category": "Transport",
      "date": "2026-06-15",
      "description": "Local auto fare to Kathmandu University gate"
    },
    {
      "id": "c9a64fde-1234-5678-abcd-ef0123456789",
      "amount": 250.00,
      "category": "Food",
      "date": "2026-06-16",
      "description": "Lunch at canteen (Khaja)"
    }
  ]
}

```

---

## 7. Build and Execution Map

The software relies on standard, non-proprietary compilation chains using standard cross-platform definitions.

### 7.1. Hardware Optimization Thresholds

* **Minimum Target RAM:** 4 Gigabytes


* **Disk Storage Footprint:** < 50 Megabytes (Highly compact binary payload)


* **Compiler Standard:** C++17 Standard ISO Target (`set(CMAKE_CXX_STANDARD 17)`)



### 7.2. Conceptual Core CMake Directives (`CMakeLists.txt`)

```cmake
cmake_minimum_required(VERSION 3.16)
project(VoxSpend VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick)

set(PROJECT_SOURCES
    src/main.cpp
    src/database/json_storage.cpp
    src/database/json_storage.h
    src/controllers/expense_manager.cpp
    src/controllers/expense_manager.h
    src/models/expense_item.cpp
    src/models/expense_item.h
    ui/qml.qrc
)

qt_add_executable(VoxSpend ${PROJECT_SOURCES})

target_link_libraries(VoxSpend PRIVATE Qt6::Core Qt6::Gui Qt6::Quick)

```