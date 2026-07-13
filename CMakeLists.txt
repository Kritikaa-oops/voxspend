cmake_minimum_required(VERSION 3.16)

project(VoxSpend1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.11.1)

qt_add_executable(appVoxSpend1
main.cpp
)

qt_add_qml_module(appVoxSpend1
URI VoxSpend1
VERSION 1.0
QML_FILES
Main.qml
LoginPage.qml
SignupPage.qml
LogoutPage.qml
EditProfile.qml
AddExpense.qml
TransactionPage.qml
SummaryPage.qml
CategoryCard.qml
ChartsPage.qml
RESOURCES logo.png
QML_FILES TransactionPage.qml
QML_FILES SummaryPage.qml
QML_FILES CategoryCard.qml
QML_FILES ChartsPage.qml
QML_FILES LoginPage.qml
QML_FILES LogoutPage.qml
QML_FILES SignupPage.qml
QML_FILES EditProfile.qml

)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appVoxSpend1 PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appVoxSpend1
MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
MACOSX_BUNDLE TRUE
WIN32_EXECUTABLE TRUE
)

target_link_libraries(appVoxSpend1
PRIVATE Qt6::Quick
)

install(TARGETS appVoxSpend1
BUNDLE DESTINATION .
LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
