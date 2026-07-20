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
                id: navBar; height: 82; anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom; color: "white"; border.color: "#E8EBF2"
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
            Rectangle { width: 62; height: 62; radius: 31; color: "#1E3A8A"; anchors.horizontalCenter: parent.horizontalCenter; anchors.bottom: navBar.top; anchors.bottomMargin: -31
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
            Rectangle { width: parent.width; height: 268; gradient: Gradient { GradientStop { position: 0; color: "#0F172A" } GradientStop { position: 1; color: "#1E3A8A" } }
                Column { anchors.centerIn: parent; spacing: 9
                    Image { source: "file:///C:/Users/dell/voxspend200/assets/logo.png"; width: 128; height: 128; fillMode: Image.PreserveAspectFit; anchors.horizontalCenter: parent.horizontalCenter }
                    Text { text: "Your money, in focus"; color: "white"; font.pixelSize: 22; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter }
                    Rectangle { width: 292; height: 84; radius: 20; color: "white"; anchors.horizontalCenter: parent.horizontalCenter
                        Column { anchors.centerIn: parent; spacing: 3
                            Text { text: "THIS MONTH'S SPEND"; color: "#7A8498"; font.pixelSize: 10; font.letterSpacing: 1.1; anchors.horizontalCenter: parent.horizontalCenter }
                            Text { text: { backend.dataRevision; return "Rs " + backend.getMonthlyTotal().toFixed(2) } color: "#19213D"; font.pixelSize: 26; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter }
                        }
                    }
                }
            }
            Column { anchors.top: parent.top; anchors.topMargin: 292; anchors.left: parent.left; anchors.right: parent.right; anchors.margins: 24; spacing: 16
                Text { text: "Recent activity"; color: "#19213D"; font.pixelSize: 18; font.bold: true }
                Rectangle { visible: dashboardPage.recentExpenses.length === 0; width: parent.width; height: 122; radius: 20; color: "white"; border.color: "#E7EAF1"
                    Column { anchors.centerIn: parent; spacing: 5
                        Text { text: "No activity yet"; color: "#313B55"; font.pixelSize: 15; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter }
                        Text { text: "Add your first expense to start tracking."; color: "#7A8498"; font.pixelSize: 12; anchors.horizontalCenter: parent.horizontalCenter }
                    }
                }
                Repeater { model: dashboardPage.recentExpenses.slice(0, 3)
                    Rectangle { width: parent.width; height: 62; radius: 14; color: "white"; border.color: "#E7EAF1"
                        Rectangle { width: 34; height: 34; radius: 10; color: "#E8F0FF"; anchors.left: parent.left; anchors.leftMargin: 14; anchors.verticalCenter: parent.verticalCenter; NavIcon { name: "activity"; strokeColor: "#1E3A8A"; anchors.centerIn: parent } }
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
            property string activeFilter: "All"
            property string searchText: ""
            property var expenses: { backend.dataRevision; return backend.getExpenses() }
            property var filteredExpenses: {
                backend.dataRevision
                var result = []
                var needle = String(activeFilter).toLowerCase()
                var query = String(searchText).trim().toLowerCase()
                for (var i = 0; i < expenses.length; ++i) {
                    var entry = expenses[i]
                    var category = String(entry.category)
                    var normalized = category.toLowerCase()
                    var title = String(entry.title).toLowerCase()
                    var note = String(entry.note || "").toLowerCase()
                    var date = String(entry.date).toLowerCase()
                    var matchesFilter = needle === "all"
                        || normalized === needle
                        || (needle === "travel" && (normalized === "travel" || normalized === "transport"))
                        || (needle === "shopping" && normalized === "shopping")
                        || (needle === "other" && normalized === "other")
                        || (needle === "food" && normalized === "food")
                    var matchesQuery = query === ""
                        || title.indexOf(query) !== -1
                        || normalized.indexOf(query) !== -1
                        || note.indexOf(query) !== -1
                        || date.indexOf(query) !== -1
                    if (matchesFilter && matchesQuery) {
                        result.push(entry)
                    }
                }
                return result
            }
            Rectangle { width: parent.width; height: 128; color: "#151C35"
                Column { anchors.left: parent.left; anchors.leftMargin: 26; anchors.verticalCenter: parent.verticalCenter; spacing: 4
                    Text { text: "Activity"; color: "white"; font.pixelSize: 24; font.bold: true }
                    Text { text: "Every transaction, in one place."; color: "#B8B2CC"; font.pixelSize: 12 }
                }
            }
            Column { anchors.top: parent.top; anchors.topMargin: 152; anchors.left: parent.left; anchors.right: parent.right; anchors.margins: 24; spacing: 16
                TextField { id: activitySearch; width: parent.width; height: 46; placeholderText: "Search activity"; leftPadding: 16; background: Rectangle { radius: 12; color: "white"; border.color: "#E2E6EF" } onTextChanged: activityPage.searchText = text }
                Row { spacing: 8
                    Repeater { model: ["All", "Food", "Travel", "Shopping", "Other"]
                        Rectangle { width: filterText.implicitWidth + 26; height: 32; radius: 16; color: activityPage.activeFilter === modelData ? "#1E3A8A" : "#E8F0FF"
                            Text { id: filterText; text: modelData; color: activityPage.activeFilter === modelData ? "white" : "#5D527A"; font.pixelSize: 12; font.bold: true; anchors.centerIn: parent }
                            MouseArea { anchors.fill: parent; onClicked: activityPage.activeFilter = modelData }
                        }
                    }
                }
                Rectangle { width: parent.width; height: 1; color: "#E2E6EF" }
                Column { visible: activityPage.filteredExpenses.length === 0; width: parent.width; topPadding: 82; spacing: 8
                    Rectangle { width: 54; height: 54; radius: 16; color: "#E8F0FF"; anchors.horizontalCenter: parent.horizontalCenter; NavIcon { name: "activity"; strokeColor: "#1E3A8A"; anchors.centerIn: parent } }
                    Text { text: "No activity yet"; color: "#27304A"; font.pixelSize: 17; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter }
                    Text { text: "Expenses you add will show up here."; color: "#7A8498"; font.pixelSize: 12; anchors.horizontalCenter: parent.horizontalCenter }
                }
            }
            ListView { anchors.top: parent.top; anchors.topMargin: 270; anchors.left: parent.left; anchors.leftMargin: 24; anchors.right: parent.right; anchors.rightMargin: 24; anchors.bottom: parent.bottom; anchors.bottomMargin: 24; model: activityPage.filteredExpenses; spacing: 8; clip: true
                delegate: Rectangle { width: ListView.view.width; height: 90; radius: 14; color: "white"; border.color: "#E4E7EF"
                    Rectangle { width: 38; height: 38; radius: 12; color: "#E8F0FF"; anchors.left: parent.left; anchors.leftMargin: 14; anchors.verticalCenter: parent.verticalCenter; NavIcon { name: "activity"; strokeColor: "#1E3A8A"; anchors.centerIn: parent } }
                    Column { anchors.left: parent.left; anchors.leftMargin: 64; anchors.right: parent.right; anchors.rightMargin: 152; anchors.verticalCenter: parent.verticalCenter; spacing: 3
                        Text { text: modelData.title; color: "#27304A"; font.pixelSize: 13; font.bold: true; width: parent.width; elide: Text.ElideRight }
                        Text { text: modelData.category + "  •  " + modelData.date; color: "#7A8498"; font.pixelSize: 11 }
                        Text { visible: String(modelData.note || "").trim() !== ""; text: String(modelData.note || "").trim(); color: "#7A8498"; font.pixelSize: 10; width: parent.width; elide: Text.ElideRight }
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
            property var chartData: []
            property var colorMap: ({ "Food": "#F97316", "Travel": "#10B981", "Shopping": "#3B82F6", "Other": "#E11D48" })
            property real maxCategoryAmount: {
                backend.dataRevision
                var highest = 0
                for (var i = 0; i < categoryTotals.length; ++i)
                    highest = Math.max(highest, Number(categoryTotals[i].amount))
                return highest
            }
            function refreshChartData() {
                var data = []
                var total = 0
                for (var i = 0; i < categoryTotals.length; ++i)
                    total += Number(categoryTotals[i].amount)
                if (total <= 0) {
                    chartData = data
                    return
                }
                for (i = 0; i < categoryTotals.length; ++i) {
                    var amount = Number(categoryTotals[i].amount)
                    if (amount <= 0) continue
                    data.push({
                        label: String(categoryTotals[i].category),
                        value: amount,
                        color: colorMap[String(categoryTotals[i].category)] || "#6D4CC4"
                    })
                }
                chartData = data
            }
            Component.onCompleted: refreshChartData()
            onCategoryTotalsChanged: refreshChartData()
            Rectangle { width: parent.width; height: 128; color: "#151C35"
                Column { anchors.left: parent.left; anchors.leftMargin: 26; anchors.verticalCenter: parent.verticalCenter; spacing: 4
                    Text { text: "Insights"; color: "white"; font.pixelSize: 24; font.bold: true }
                    Text { text: "A clear view of your spending patterns."; color: "#B8B2CC"; font.pixelSize: 12 }
                }
            }
            Column { anchors.top: parent.top; anchors.topMargin: 152; anchors.left: parent.left; anchors.right: parent.right; anchors.margins: 24; spacing: 16
                Rectangle { width: parent.width; height: 220; radius: 20; color: "white"; border.color: "#E4E7EF"
                    Column { anchors.fill: parent; anchors.margins: 20; spacing: 12
                        Text { text: "Spending by category"; color: "#27304A"; font.pixelSize: 16; font.bold: true }
                        Text { text: "This month"; color: "#7A8498"; font.pixelSize: 12 }
                        Repeater { model: insightsPage.categoryTotals
                            Row { width: parent.width; spacing: 10
                                Text { text: modelData.category; width: 80; color: "#566078"; font.pixelSize: 12 }
                                Rectangle { id: barTrack; width: parent.width - 125; height: 8; radius: 4; color: "#EEEBFA"
                                    Rectangle { width: insightsPage.maxCategoryAmount > 0 ? parent.width * Number(modelData.amount) / insightsPage.maxCategoryAmount : 0; height: parent.height; radius: 4; color: "#1E3A8A" }
                                }
                                Text { text: "Rs " + Number(modelData.amount).toFixed(2); color: "#7A8498"; font.pixelSize: 11 }
                            }
                        }
                    }
                }
                Rectangle { width: parent.width; height: 252; radius: 20; color: "white"; border.color: "#E4E7EF"
                    Column { anchors.fill: parent; anchors.margins: 16; spacing: 10
                        Text { text: "Expense distribution"; color: "#27304A"; font.pixelSize: 16; font.bold: true }
                        Row { anchors.horizontalCenter: parent.horizontalCenter; spacing: 12
                            Canvas { id: pieCanvas; width: 150; height: 150; onPaint: {
                                var ctx = getContext("2d")
                                var centerX = width / 2
                                var centerY = height / 2
                                var radius = Math.min(width, height) * 0.34
                                var startAngle = -Math.PI / 2
                                ctx.clearRect(0, 0, width, height)
                                var total = 0
                                for (var i = 0; i < insightsPage.chartData.length; ++i)
                                    total += Number(insightsPage.chartData[i].value)
                                if (total <= 0) {
                                    ctx.beginPath()
                                    ctx.arc(centerX, centerY, radius, 0, 2 * Math.PI)
                                    ctx.strokeStyle = "#E4E7EF"
                                    ctx.lineWidth = 2
                                    ctx.stroke()
                                    ctx.fillStyle = "#F5F7FB"
                                    ctx.fill()
                                    return
                                }
                                for (i = 0; i < insightsPage.chartData.length; ++i) {
                                    var slice = insightsPage.chartData[i]
                                    var endAngle = startAngle + (Number(slice.value) / total) * 2 * Math.PI
                                    ctx.beginPath()
                                    ctx.moveTo(centerX, centerY)
                                    ctx.arc(centerX, centerY, radius, startAngle, endAngle)
                                    ctx.closePath()
                                    ctx.fillStyle = slice.color
                                    ctx.fill()
                                    ctx.lineWidth = 2
                                    ctx.strokeStyle = "#FFFFFF"
                                    ctx.stroke()
                                    startAngle = endAngle
                                }
                                ctx.beginPath()
                                ctx.arc(centerX, centerY, radius * 0.5, 0, 2 * Math.PI)
                                ctx.fillStyle = "#FFFFFF"
                                ctx.fill()
                            }
                            Component.onCompleted: requestPaint()
                            onWidthChanged: requestPaint()
                            onHeightChanged: requestPaint()
                            }
                            Column { spacing: 6
                                Repeater { model: insightsPage.chartData
                                    Row { spacing: 6
                                        Rectangle { width: 10; height: 10; radius: 3; color: modelData.color; anchors.verticalCenter: parent.verticalCenter }
                                        Text { text: modelData.label + " • Rs " + Number(modelData.value).toFixed(2); color: "#566078"; font.pixelSize: 10 }
                                    }
                                }
                                Text { visible: insightsPage.chartData.length === 0; text: "Add expenses to see a pie chart."; color: "#7A8498"; font.pixelSize: 10 }
                            }
                        }
                    }
                }
                Rectangle { width: parent.width; height: 94; radius: 18; color: "#E8F0FF"
                    Column { anchors.centerIn: parent; spacing: 4
                        Text { text: { backend.dataRevision; return insightsPage.categoryTotals.length === 0 ? "No spending data yet" : backend.getExpenseCount() + " expenses recorded" } color: "#1E3A8A"; font.pixelSize: 14; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter }
                        Text { text: { backend.dataRevision; return insightsPage.categoryTotals.length === 0 ? "Add expenses to see personalised trends." : "Current month: Rs " + backend.getMonthlyTotal().toFixed(2) } color: "#766C91"; font.pixelSize: 12; anchors.horizontalCenter: parent.horizontalCenter }
                    }
                }
            }
        }
    }

    Component {
        id: profileContent
        Item {
            Rectangle { width: parent.width; height: 196; color: "#151C35"
                Column { anchors.horizontalCenter: parent.horizontalCenter; anchors.bottom: parent.bottom; anchors.bottomMargin: 24; spacing: 6
                    Rectangle { width: 58; height: 58; radius: 29; color: "#93C5FD"; anchors.horizontalCenter: parent.horizontalCenter; NavIcon { name: "user"; strokeColor: "#0F172A"; anchors.centerIn: parent } }
                    Text { text: { backend.dataRevision; return backend.currentUserName() } color: "white"; font.pixelSize: 20; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter }
                }
            }
            Column { width: Math.min(parent.width - 48, 500); anchors.horizontalCenter: parent.horizontalCenter; anchors.top: parent.top; anchors.topMargin: 218; spacing: 14
                Rectangle { width: parent.width; height: 84; radius: 18; color: "white"; border.color: "#E4E7EF"
                    Column { anchors.left: parent.left; anchors.leftMargin: 18; anchors.verticalCenter: parent.verticalCenter; spacing: 4
                        Text { text: { backend.dataRevision; return backend.currentUserEmail() } color: "#313B55"; font.pixelSize: 14; font.bold: true }
                        Text { text: "Personal account"; color: "#7A8498"; font.pixelSize: 12 }
                    }
                }
                Text { text: "ACCOUNT"; color: "#667087"; font.pixelSize: 10; font.bold: true; font.letterSpacing: 1 }
                Rectangle { width: parent.width; height: 60; radius: 16; color: "white"; border.color: "#E4E7EF"
                    Text { text: "Edit profile"; anchors.left: parent.left; anchors.leftMargin: 18; anchors.verticalCenter: parent.verticalCenter; color: "#27304A"; font.pixelSize: 14; font.bold: true }
                    Text { text: "Manage"; anchors.right: parent.right; anchors.rightMargin: 18; anchors.verticalCenter: parent.verticalCenter; color: "#1E3A8A"; font.pixelSize: 12; MouseArea { anchors.fill: parent; onClicked: stackView.push("EditProfile.qml") } }
                }
                Rectangle { width: parent.width; height: 48; radius: 12; color: "#FFF1F3"; border.color: "#F3CCD3"
                    Text { text: "Reset expense"; color: "#B72842"; font.pixelSize: 14; font.bold: true; anchors.centerIn: parent }
                    MouseArea { anchors.fill: parent; onClicked: resetExpenseDialog.open() }
                }
                Rectangle { width: parent.width; height: 48; radius: 12; color: "#FFF1F3"; border.color: "#F3CCD3"
                    Text { text: "Sign out"; color: "#B72842"; font.pixelSize: 14; font.bold: true; anchors.centerIn: parent }
                    MouseArea { anchors.fill: parent; onClicked: signOutDialog.open() }
                }
            }
            Dialog { id: resetExpenseDialog; modal: true; anchors.centerIn: parent; width: 340; title: "Reset expense"
                contentItem: Column { spacing: 16; padding: 20
                    Text { width: parent.width - 40; text: "Reset all expenses for this account? This action cannot be undone."; wrapMode: Text.Wrap; color: "#313B55"; font.pixelSize: 14 }
                    Row { anchors.right: parent.right; spacing: 10
                        Button { text: "Cancel"; onClicked: resetExpenseDialog.close() }
                        Button { text: "Reset"; onClicked: { resetExpenseDialog.close(); backend.resetExpenses(); } }
                    }
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
