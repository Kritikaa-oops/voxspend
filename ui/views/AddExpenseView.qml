import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../components"

Page {
    padding: 28
    background: Rectangle { color: "#f6f7fb" }

    ColumnLayout {
        width: Math.min(parent.width, 560)
        spacing: 14

        Label {
            text: "Add Expense"
            color: "#1e2430"
            font.pixelSize: 30
            font.bold: true
            Layout.bottomMargin: 8
        }

        CustomTextField {
            id: amountField
            Layout.fillWidth: true
            placeholderText: "Amount"
            numeric: true
        }

        ComboBox {
            id: categoryField
            Layout.fillWidth: true
            model: ["Food", "Transport", "Books", "Utilities", "Rent", "Other"]
        }

        CustomTextField {
            id: descriptionField
            Layout.fillWidth: true
            placeholderText: "Description"
        }

        CustomTextField {
            id: dateField
            Layout.fillWidth: true
            placeholderText: "Date (YYYY-MM-DD)"
            text: Qt.formatDate(new Date(), "yyyy-MM-dd")
        }

        Button {
            text: "Save Expense"
            Layout.preferredWidth: 160
            onClicked: {
                if (expenseManager.addExpense(Number(amountField.text), categoryField.currentText, descriptionField.text, dateField.text)) {
                    amountField.clear()
                    descriptionField.clear()
                    dateField.text = Qt.formatDate(new Date(), "yyyy-MM-dd")
                }
            }
        }
    }
}
