import QtQuick 2.15
import QtQuick.Controls 2.15

Window {
    id: appWindow
    width: 720; height: 720
    minimumWidth: 620; minimumHeight: 620
    visible: true; title: "VoxSpend200"; color: "#F5F7FB"

    StackView {
        id: stackView; anchors.fill: parent; initialItem: loginPage
        pushEnter: Transition {} pushExit: Transition {}
        popEnter: Transition {} popExit: Transition {}
        replaceEnter: Transition {} replaceExit: Transition {}
    }
    Component { id: loginPage; LoginPage {} }
    Component { id: signupPage; SignupPage {} }

    Component {
        id: homePage
        Item {
            id: shell; anchors.fill: parent
            property int currentTab: 0
            property var pages: [dashboardContent, activityContent, insightsContent, profileContent]
            Rectangle { anchors.fill: parent; color: "#F5F7FB" }
            Loader { anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: navBar.top; sourceComponent: shell.pages[shell.currentTab] }
            Rectangle {
                id: navBar; height: 76; anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom; color: "white"; border.color: "#E8EBF2"
                Row { anchors.fill: parent
                    Repeater { model: ListModel {
                        ListElement { icon: "home"; label: "Home" }
                        ListElement { icon: "activity"; label: "Activity" }
                        ListElement { icon: "chart"; label: "Insights" }
                        ListElement { icon: "user"; label: "Profile" }
                    }
                    Item { width: parent.width / 4; height: parent.height
                        Column { anchors.centerIn: parent; spacing: 3
                            NavIcon { name: model.icon; strokeColor: shell.currentTab === index ? "#6D4CC4" : "#8B96AD"; anchors.horizontalCenter: parent.horizontalCenter }
                            Text { text: model.label; color: shell.currentTab === index ? "#6D4CC4" : "#8B96AD"; font.pixelSize: 11; anchors.horizontalCenter: parent.horizontalCenter }
                        }
                        MouseArea { anchors.fill: parent; onClicked: shell.currentTab = index }
                    }
                    }
                }
            }
            Rectangle { width: 58; height: 58; radius: 29; color: "#6D4CC4"; anchors.horizontalCenter: parent.horizontalCenter; anchors.bottom: navBar.top; anchors.bottomMargin: -29
                NavIcon { name: "plus"; strokeColor: "white"; anchors.centerIn: parent }
                MouseArea { anchors.fill: parent; onClicked: stackView.push("AddExpense.qml") }
            }
        }
    }

    Component {
        id: dashboardContent
        Item {
            id: dashboardPage
            property var recentExpenses: { backend.dataRevision; return backend.getExpenses() }
            Rectangle { width: parent.width; height: 268; gradient: Gradient { GradientStop { position: 0; color: "#151C35" } GradientStop { position: 1; color: "#3F2D75" } }
                Column { anchors.centerIn: parent; spacing: 9
                    Image { source: "logo.png"; width: 80; height: 80; fillMode: Image.PreserveAspectFit; anchors.horizontalCenter: parent.horizontalCenter }
                    Text { text: "Your money, in focus"; color: "white"; font.pixelSize: 22; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter }
                    Rectangle { width: 278; height: 78; radius: 18; color: "white"; anchors.horizontalCenter: parent.horizontalCenter
                        Column { anchors.centerIn: parent; spacing: 3
                            Text { text: "THIS MONTH'S SPEND"; color: "#7A8498"; font.pixelSize: 10; font.letterSpacing: 1.1; anchors.horizontalCenter: parent.horizontalCenter }
                            Text { text: { backend.dataRevision; return "Rs " + backend.getMonthlyTotal().toFixed(2) } color: "#19213D"; font.pixelSize: 26; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter }
                        }
                    }
                }
            }
            Column { anchors.top: parent.top; anchors.topMargin: 292; anchors.left: parent.left; anchors.right: parent.right; anchors.margins: 24; spacing: 16
                Text { text: "Recent activity"; color: "#19213D"; font.pixelSize: 18; font.bold: true }
                Rectangle { visible: dashboardPage.recentExpenses.length === 0; width: parent.width; height: 116; radius: 18; color: "white"; border.color: "#E7EAF1"
                    Column { anchors.centerIn: parent; spacing: 5
                        Text { text: "No activity yet"; color: "#313B55"; font.pixelSize: 15; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter }
                        Text { text: "Add your first expense to start tracking."; color: "#7A8498"; font.pixelSize: 12; anchors.horizontalCenter: parent.horizontalCenter }
                    }
                }
                Repeater { model: dashboardPage.recentExpenses.slice(0, 3)
                    Rectangle { width: parent.width; height: 62; radius: 14; color: "white"; border.color: "#E7EAF1"
                        Rectangle { width: 34; height: 34; radius: 10; color: "#EEEBFA"; anchors.left: parent.left; anchors.leftMargin: 14; anchors.verticalCenter: parent.verticalCenter; NavIcon { name: "activity"; strokeColor: "#6D4CC4"; anchors.centerIn: parent } }
                        Column { anchors.left: parent.left; anchors.leftMargin: 60; anchors.right: parent.right; anchors.rightMargin: 130; anchors.verticalCenter: parent.verticalCenter; spacing: 2
                            Text { text: modelData.title; width: parent.width; elide: Text.ElideRight; color: "#27304A"; font.pixelSize: 13; font.bold: true }
                            Text { text: modelData.category + "  •  " + modelData.date; color: "#7A8498"; font.pixelSize: 10 }
                        }
                        Text { text: "- Rs " + Number(modelData.amount).toFixed(2); width: 116; horizontalAlignment: Text.AlignRight; elide: Text.ElideRight; color: "#C7354A"; font.pixelSize: 12; font.bold: true; anchors.right: parent.right; anchors.rightMargin: 14; anchors.verticalCenter: parent.verticalCenter }
                    }
                }
            }
        }
    }

    Component {
        id: activityContent
        Item {
            id: activityPage
            property var expenses: { backend.dataRevision; return backend.getExpenses() }
            Rectangle { width: parent.width; height: 128; color: "#151C35"
                Column { anchors.left: parent.left; anchors.leftMargin: 26; anchors.verticalCenter: parent.verticalCenter; spacing: 4
                    Text { text: "Activity"; color: "white"; font.pixelSize: 24; font.bold: true }
                    Text { text: "Every transaction, in one place."; color: "#B8B2CC"; font.pixelSize: 12 }
                }
            }
            Column { anchors.top: parent.top; anchors.topMargin: 152; anchors.left: parent.left; anchors.right: parent.right; anchors.margins: 24; spacing: 16
                TextField { width: parent.width; height: 46; placeholderText: "Search activity"; leftPadding: 16; background: Rectangle { radius: 12; color: "white"; border.color: "#E2E6EF" } }
                Row { spacing: 8
                    Repeater { model: ["All", "Food", "Travel", "Bills"]
                        Rectangle { width: filter.implicitWidth + 26; height: 32; radius: 16; color: index === 0 ? "#6D4CC4" : "#EEEBFA"
                            Text { id: filter; text: modelData; color: index === 0 ? "white" : "#5D527A"; font.pixelSize: 12; font.bold: true; anchors.centerIn: parent }
                        }
                    }
                }
                Rectangle { width: parent.width; height: 1; color: "#E2E6EF" }
                Column { visible: activityPage.expenses.length === 0; width: parent.width; topPadding: 82; spacing: 8
                    Rectangle { width: 54; height: 54; radius: 16; color: "#EEEBFA"; anchors.horizontalCenter: parent.horizontalCenter; NavIcon { name: "activity"; strokeColor: "#6D4CC4"; anchors.centerIn: parent } }
                    Text { text: "No activity yet"; color: "#27304A"; font.pixelSize: 17; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter }
                    Text { text: "Expenses you add will show up here."; color: "#7A8498"; font.pixelSize: 12; anchors.horizontalCenter: parent.horizontalCenter }
                }
            }
            ListView { anchors.top: parent.top; anchors.topMargin: 270; anchors.left: parent.left; anchors.leftMargin: 24; anchors.right: parent.right; anchors.rightMargin: 24; anchors.bottom: parent.bottom; anchors.bottomMargin: 24; model: activityPage.expenses; spacing: 8; clip: true
                delegate: Rectangle { width: ListView.view.width; height: 70; radius: 14; color: "white"; border.color: "#E4E7EF"
                    Rectangle { width: 38; height: 38; radius: 12; color: "#EEEBFA"; anchors.left: parent.left; anchors.leftMargin: 14; anchors.verticalCenter: parent.verticalCenter; NavIcon { name: "activity"; strokeColor: "#6D4CC4"; anchors.centerIn: parent } }
                    Column { anchors.left: parent.left; anchors.leftMargin: 64; anchors.right: parent.right; anchors.rightMargin: 148; anchors.verticalCenter: parent.verticalCenter; spacing: 3
                        Text { text: modelData.title; color: "#27304A"; font.pixelSize: 13; font.bold: true; width: parent.width; elide: Text.ElideRight }
                        Text { text: modelData.category + "  •  " + modelData.date; color: "#7A8498"; font.pixelSize: 11 }
                    }
                    Text { text: "- Rs " + Number(modelData.amount).toFixed(2); width: 126; horizontalAlignment: Text.AlignRight; elide: Text.ElideRight; color: "#C7354A"; font.pixelSize: 13; font.bold: true; anchors.right: parent.right; anchors.rightMargin: 14; anchors.verticalCenter: parent.verticalCenter }
                }
            }
        }
    }

    Component {
        id: insightsContent
        Item {
            id: insightsPage
            property var categoryTotals: { backend.dataRevision; return backend.getCategoryTotals() }
            property real maxCategoryAmount: {
                backend.dataRevision
                var highest = 0
                for (var i = 0; i < categoryTotals.length; ++i)
                    highest = Math.max(highest, Number(categoryTotals[i].amount))
                return highest
            }
            Rectangle { width: parent.width; height: 128; color: "#151C35"
                Column { anchors.left: parent.left; anchors.leftMargin: 26; anchors.verticalCenter: parent.verticalCenter; spacing: 4
                    Text { text: "Insights"; color: "white"; font.pixelSize: 24; font.bold: true }
                    Text { text: "A clear view of your spending patterns."; color: "#B8B2CC"; font.pixelSize: 12 }
                }
            }
            Column { anchors.top: parent.top; anchors.topMargin: 152; anchors.left: parent.left; anchors.right: parent.right; anchors.margins: 24; spacing: 16
                Rectangle { width: parent.width; height: 215; radius: 18; color: "white"; border.color: "#E4E7EF"
                    Column { anchors.fill: parent; anchors.margins: 20; spacing: 12
                        Text { text: "Spending by category"; color: "#27304A"; font.pixelSize: 16; font.bold: true }
                        Text { text: "This month"; color: "#7A8498"; font.pixelSize: 12 }
                        Repeater { model: insightsPage.categoryTotals
                            Row { width: parent.width; spacing: 10
                                Text { text: modelData.category; width: 80; color: "#566078"; font.pixelSize: 12 }
                                Rectangle { id: barTrack; width: parent.width - 125; height: 8; radius: 4; color: "#EEEBFA"
                                    Rectangle { width: insightsPage.maxCategoryAmount > 0 ? parent.width * Number(modelData.amount) / insightsPage.maxCategoryAmount : 0; height: parent.height; radius: 4; color: "#6D4CC4" }
                                }
                                Text { text: "Rs " + Number(modelData.amount).toFixed(2); color: "#7A8498"; font.pixelSize: 11 }
                            }
                        }
                    }
                }
                Rectangle { width: parent.width; height: 88; radius: 18; color: "#EEEBFA"
                    Column { anchors.centerIn: parent; spacing: 4
                        Text { text: { backend.dataRevision; return insightsPage.categoryTotals.length === 0 ? "No spending data yet" : backend.getExpenseCount() + " expenses recorded" } color: "#3C2B67"; font.pixelSize: 14; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter }
                        Text { text: { backend.dataRevision; return insightsPage.categoryTotals.length === 0 ? "Add expenses to see personalised trends." : "Current month: Rs " + backend.getMonthlyTotal().toFixed(2) } color: "#766C91"; font.pixelSize: 12; anchors.horizontalCenter: parent.horizontalCenter }
                    }
                }
            }
        }
    }

    Component {
        id: profileContent
        Item {
            Rectangle { width: parent.width; height: 190; color: "#151C35"
                Column { anchors.horizontalCenter: parent.horizontalCenter; anchors.bottom: parent.bottom; anchors.bottomMargin: 24; spacing: 6
                    Rectangle { width: 58; height: 58; radius: 29; color: "#A892E3"; anchors.horizontalCenter: parent.horizontalCenter; NavIcon { name: "user"; strokeColor: "#151C35"; anchors.centerIn: parent } }
                    Text { text: { backend.dataRevision; return backend.currentUserName() } color: "white"; font.pixelSize: 20; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter }
                }
            }
            Column { width: Math.min(parent.width - 48, 500); anchors.horizontalCenter: parent.horizontalCenter; anchors.top: parent.top; anchors.topMargin: 218; spacing: 14
                Rectangle { width: parent.width; height: 78; radius: 16; color: "white"; border.color: "#E4E7EF"
                    Column { anchors.left: parent.left; anchors.leftMargin: 18; anchors.verticalCenter: parent.verticalCenter; spacing: 4
                        Text { text: { backend.dataRevision; return backend.currentUserEmail() } color: "#313B55"; font.pixelSize: 14; font.bold: true }
                        Text { text: "Personal account"; color: "#7A8498"; font.pixelSize: 12 }
                    }
                }
                Text { text: "ACCOUNT"; color: "#667087"; font.pixelSize: 10; font.bold: true; font.letterSpacing: 1 }
                Rectangle { width: parent.width; height: 56; radius: 14; color: "white"; border.color: "#E4E7EF"
                    Text { text: "Edit profile"; anchors.left: parent.left; anchors.leftMargin: 18; anchors.verticalCenter: parent.verticalCenter; color: "#27304A"; font.pixelSize: 14; font.bold: true }
                    Text { text: "Manage"; anchors.right: parent.right; anchors.rightMargin: 18; anchors.verticalCenter: parent.verticalCenter; color: "#6D4CC4"; font.pixelSize: 12; MouseArea { anchors.fill: parent; onClicked: stackView.push("EditProfile.qml") } }
                }
                Rectangle { width: parent.width; height: 48; radius: 12; color: "#FFF1F3"; border.color: "#F3CCD3"
                    Text { text: "Sign out"; color: "#B72842"; font.pixelSize: 14; font.bold: true; anchors.centerIn: parent }
                    MouseArea { anchors.fill: parent; onClicked: signOutDialog.open() }
                }
            }
            Dialog { id: signOutDialog; modal: true; anchors.centerIn: parent; width: 340; title: "Sign out"
                contentItem: Column { spacing: 16; padding: 20
                    Text { width: parent.width - 40; text: "Do you really want to sign out of this account?"; wrapMode: Text.Wrap; color: "#313B55"; font.pixelSize: 14 }
                    Row { anchors.right: parent.right; spacing: 10
                        Button { text: "Cancel"; onClicked: signOutDialog.close() }
                        Button { text: "Sign out"; onClicked: { signOutDialog.close(); backend.logout(); stackView.replace("LoginPage.qml") } }
                    }
                }
            }
        }
    }
}
