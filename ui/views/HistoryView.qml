import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../components"

Page {
    padding: 28
    background: Rectangle { color: "#f6f7fb" }

    ColumnLayout {
        anchors.fill: parent
        spacing: 18

        Label {
            text: "History"
            color: "#1e2430"
            font.pixelSize: 30
            font.bold: true
        }

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 10
            clip: true
            model: expenseManager.expenses

            delegate: ExpenseCard {
                width: ListView.view.width
                expenseId: modelData.id
                amount: modelData.amount
                category: modelData.category
                date: modelData.date
                description: modelData.description
                currency: expenseManager.currency
                onRemoveRequested: expenseManager.removeExpense(expenseId)
            }

            Label {
                anchors.centerIn: parent
                visible: expenseManager.expenses.length === 0
                text: "No expenses yet"
                color: "#6d7482"
                font.pixelSize: 18
            }
        }
    }
}
