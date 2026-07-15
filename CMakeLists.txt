cmake_minimum_required(VERSION 3.16)

project(VoxSpend200 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Gui Qml Sql)

qt_standard_project_setup(REQUIRES 6.11.1)
set(CMAKE_AUTOMOC ON)

set(PROJECT_SOURCES
    src/main.cpp
    src/BackendManager.cpp
    src/QmlIntegration.cpp
    src/Login.cpp
    src/Logout.cpp
    src/EditProfile.cpp
    src/Category.cpp
    src/Charts.cpp
    src/HomePage.cpp
    src/AddExpense.cpp
    src/Signup.cpp
    src/Transaction.cpp
    include/BackendManager.h
    include/Category.h
    include/expense.h
)

qt_add_executable(appVoxSpend200 ${PROJECT_SOURCES})

qt_add_qml_module(appVoxSpend200
    URI com.voxspend.backend
    VERSION 1.0
    QML_FILES
        qml/Main.qml
        qml/NavIcon.qml
        qml/AddExpense.qml
        qml/CategoryCard.qml
        qml/ChartsPage.qml
        qml/EditProfile.qml
        qml/LoginPage.qml
        qml/LogoutPage.qml
        qml/SignupPage.qml
        qml/SummaryPage.qml
        qml/TransactionPage.qml
)

target_include_directories(appVoxSpend200 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(appVoxSpend200 PRIVATE Qt6::Gui Qt6::Qml Qt6::Sql)
