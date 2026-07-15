import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    anchors.fill: parent; color: "#F5F7FB"
    ListModel { id: transactionModel }
    Rectangle { width: parent.width; height: 104; color: "#151C35"
        Row { anchors.left: parent.left; anchors.leftMargin: 26; anchors.verticalCenter: parent.verticalCenter; spacing: 15
            Text { text: "Back"; color: "#C9C4DF"; font.pixelSize: 13; MouseArea { anchors.fill: parent; onClicked: stackView.pop() } }
            Rectangle { width: 1; height: 20; color: "#5E557A" }
            Column { spacing: 3
                Text { text: "Activity"; color: "white"; font.pixelSize: 24; font.bold: true }
                Text { text: "Every transaction, in one place."; color: "#B8B2CC"; font.pixelSize: 12 }
            }
        }
    }
    Column { anchors.top: parent.top; anchors.topMargin: 104; anchors.left: parent.left; anchors.right: parent.right; anchors.margins: 24; spacing: 16
        TextField { id: searchField; width: parent.width; height: 46; placeholderText: "Search activity"; leftPadding: 16; background: Rectangle { radius: 12; color: "white"; border.color: "#E2E6EF" } }
        Row { spacing: 8
            Repeater { model: ["All", "Food", "Travel", "Bills"]
                Rectangle { width: filterText.implicitWidth + 26; height: 32; radius: 16; color: index === 0 ? "#6D4CC4" : "#EEEBFA"
                    Text { id: filterText; text: modelData; color: index === 0 ? "white" : "#5D527A"; font.pixelSize: 12; font.bold: true; anchors.centerIn: parent }
                }
            }
        }
        Rectangle { width: parent.width; height: 1; color: "#E2E6EF" }
        Item { width: parent.width; height: 270; visible: transactionModel.count === 0
        Column { anchors.centerIn: parent; width: parent.width; spacing: 8
            Rectangle { width: 54; height: 54; radius: 16; color: "#EEEBFA"; anchors.horizontalCenter: parent.horizontalCenter; NavIcon { name: "activity"; strokeColor: "#6D4CC4"; anchors.centerIn: parent } }
            Text { text: "No activity yet"; color: "#27304A"; font.pixelSize: 17; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter }
            Text { text: "Expenses you add will show up here."; color: "#7A8498"; font.pixelSize: 12; anchors.horizontalCenter: parent.horizontalCenter }
        }
        }
        ListView { width: parent.width; height: parent.height - 210; visible: transactionModel.count > 0; model: transactionModel; spacing: 8
            delegate: Rectangle { width: parent.width; height: 72; radius: 14; color: "white"; border.color: "#E4E7EF" }
        }
    }
}
