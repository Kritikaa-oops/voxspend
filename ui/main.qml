import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: window
    width: 1024
    height: 680
    visible: true
    title: "VoxSpend"
    color: "#f6f7fb"

    property string activeView: "dashboard"

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            Layout.preferredWidth: 220
            Layout.fillHeight: true
            color: "#111"

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 14

                Label {
                    text: "VoxSpend"
                    color: "white"
                    font.pixelSize: 24
                    font.bold: true
                    Layout.bottomMargin: 12
                }

                Button {
                    text: "Dashboard"
                    Layout.fillWidth: true
                    highlighted: window.activeView === "dashboard"
                    onClicked: window.activeView = "dashboard"
                }

                Button {
                    text: "Add Expense"
                    Layout.fillWidth: true
                    highlighted: window.activeView === "add"
                    onClicked: window.activeView = "add"
                }

                Button {
                    text: "History"
                    Layout.fillWidth: true
                    highlighted: window.activeView === "history"
                    onClicked: window.activeView = "history"
                }

                Item {
                    Layout.fillHeight: true
                }

                Label {
                    text: expenseManager.currency + " " + expenseManager.totalSpent.toFixed(2)
                    color: "#d1d5db"
                    font.pixelSize: 18
                    font.bold: true
                }
            }
        }

        Loader {
            Layout.fillWidth: true
            Layout.fillHeight: true
            source: {
                if (window.activeView === "add") {
                    return "views/AddExpenseView.qml"
                }
                if (window.activeView === "history") {
                    return "views/HistoryView.qml"
                }
                return "views/DashboardView.qml"
            }
        }
    }
}
