import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    anchors.fill: parent; color: "#F5F7FB"
    Rectangle { width: parent.width; height: 104; color: "#151C35"
        Row { anchors.left: parent.left; anchors.leftMargin: 26; anchors.verticalCenter: parent.verticalCenter; spacing: 15
            Text { text: "Back"; color: "#C9C4DF"; font.pixelSize: 13; MouseArea { anchors.fill: parent; onClicked: stackView.pop() } }
            Rectangle { width: 1; height: 20; color: "#5E557A" }
            Column { spacing: 3
                Text { text: "Add expense"; color: "white"; font.pixelSize: 24; font.bold: true }
                Text { text: "Keep your spending record up to date."; color: "#B8B2CC"; font.pixelSize: 12 }
            }
        }
    }
    ScrollView {
        id: expenseScroll
        anchors.top: parent.top; anchors.topMargin: 104; anchors.bottom: parent.bottom; width: parent.width; clip: true
        contentWidth: availableWidth
        Column { width: Math.min(expenseScroll.availableWidth - 48, 540); anchors.horizontalCenter: parent.horizontalCenter; topPadding: 28; bottomPadding: 30; spacing: 14
            Rectangle { width: parent.width; height: 74; radius: 16; color: "#EEEBFA"
                Row { anchors.fill: parent; anchors.margins: 16; spacing: 12
                    Rectangle { width: 40; height: 40; radius: 12; color: "#6D4CC4"; anchors.verticalCenter: parent.verticalCenter; NavIcon { name: "plus"; strokeColor: "white"; anchors.centerIn: parent } }
                    Column { anchors.verticalCenter: parent.verticalCenter; spacing: 3
                        Text { text: "New transaction"; color: "#292044"; font.pixelSize: 14; font.bold: true }
                        Text { text: "Enter the details below."; color: "#766C91"; font.pixelSize: 11 }
                    }
                }
            }
            Text { text: "EXPENSE DETAILS"; color: "#667087"; font.pixelSize: 10; font.bold: true; font.letterSpacing: 1.1; topPadding: 6 }
            Rectangle { width: parent.width; height: 360; radius: 18; color: "white"; border.color: "#E4E7EF"
                Column { anchors.fill: parent; anchors.margins: 20; spacing: 9
                    Text { text: "TITLE"; color: "#667087"; font.pixelSize: 10; font.bold: true; font.letterSpacing: 1 }
                    TextField { id: titleField; width: parent.width; height: 40; placeholderText: "e.g. Groceries"; background: Rectangle { radius: 9; color: "#F7F8FC"; border.color: titleField.activeFocus ? "#6D4CC4" : "#E2E6EF"; border.width: titleField.activeFocus ? 2 : 1 } }
                    Text { text: "AMOUNT"; color: "#667087"; font.pixelSize: 10; font.bold: true; font.letterSpacing: 1 }
                    Row { width: parent.width; height: 40; spacing: 8
                        Rectangle { width: 56; height: parent.height; radius: 9; color: "#EEEBFA"; Text { text: "Rs"; color: "#6D4CC4"; font.bold: true; anchors.centerIn: parent } }
                        TextField { id: amountField; width: parent.width - 64; height: parent.height; placeholderText: "0.00"; inputMethodHints: Qt.ImhFormattedNumbersOnly; validator: DoubleValidator { bottom: 0 } background: Rectangle { radius: 9; color: "#F7F8FC"; border.color: amountField.activeFocus ? "#6D4CC4" : "#E2E6EF"; border.width: amountField.activeFocus ? 2 : 1 } }
                    }
                    Text { text: "CATEGORY"; color: "#667087"; font.pixelSize: 10; font.bold: true; font.letterSpacing: 1 }
                    ComboBox { id: categoryBox; width: parent.width; height: 40; model: ["Select category", "Food", "Transport", "Shopping", "Bills", "Other"]; background: Rectangle { radius: 9; color: "#F7F8FC"; border.color: "#E2E6EF" } }
                    Text { text: "NOTE"; color: "#667087"; font.pixelSize: 10; font.bold: true; font.letterSpacing: 1 }
                    TextField { id: noteField; width: parent.width; height: 40; placeholderText: "Optional note"; background: Rectangle { radius: 9; color: "#F7F8FC"; border.color: "#E2E6EF" } }
                }
            }
            Text { id: errorText; width: parent.width; text: ""; visible: text !== ""; color: "#C7354A"; font.pixelSize: 12; horizontalAlignment: Text.AlignHCenter }
            Rectangle { width: parent.width; height: 48; radius: 12; color: "#6D4CC4"
                Text { text: "Save expense"; color: "white"; font.pixelSize: 15; font.bold: true; anchors.centerIn: parent }
                MouseArea { anchors.fill: parent; onClicked: {
                    if (titleField.text === "") errorText.text = "Enter an expense title"
                    else if (amountField.text === "") errorText.text = "Enter an amount"
                    else if (categoryBox.currentIndex === 0) errorText.text = "Select a category"
                    else { var saved = backendManager.addExpense(titleField.text, parseFloat(amountField.text) || 0, categoryBox.currentText, Qt.formatDate(new Date(), "yyyy-MM-dd"), noteField.text); if (saved) { stackView.pop() } else { errorText.color = "#C7354A"; errorText.text = backendManager.getLastExpenseError() } }
                } }
            }
        }
    }
}
