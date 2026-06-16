import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../components"

Page {
    padding: 28
    background: Rectangle { color: "#f6f7fb" }

    ColumnLayout {
        anchors.fill: parent
        spacing: 20

        Label {
            text: "Dashboard"
            color: "#1e2430"
            font.pixelSize: 30
            font.bold: true
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 16

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 128
                color: "white"
                radius: 8
                border.color: "#e0e4ec"

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 20
                    Label { text: "Total Spent"; color: "#6d7482"; font.pixelSize: 14 }
                    Label {
                        text: expenseManager.currency + " " + expenseManager.totalSpent.toFixed(2)
                        color: "#1e2430"
                        font.pixelSize: 30
                        font.bold: true
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 128
                color: "white"
                radius: 8
                border.color: "#e0e4ec"

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 20
                    Label { text: "Monthly Limit"; color: "#6d7482"; font.pixelSize: 14 }
                    Label {
                        text: expenseManager.currency + " " + expenseManager.monthlyLimit.toFixed(2)
                        color: "#1e2430"
                        font.pixelSize: 30
                        font.bold: true
                    }
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 140
            color: "white"
            radius: 8
            border.color: "#e0e4ec"

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 12

                Label {
                    text: "Budget Usage"
                    color: "#1e2430"
                    font.pixelSize: 18
                    font.bold: true
                }

                BudgetProgressBar {
                    Layout.fillWidth: true
                    value: expenseManager.totalSpent
                    maximum: expenseManager.monthlyLimit
                }

                Label {
                    text: Math.round((expenseManager.totalSpent / expenseManager.monthlyLimit) * 100) + "% of monthly limit used"
                    color: "#6d7482"
                    font.pixelSize: 14
                }
            }
        }

        Item { Layout.fillHeight: true }
    }
}
