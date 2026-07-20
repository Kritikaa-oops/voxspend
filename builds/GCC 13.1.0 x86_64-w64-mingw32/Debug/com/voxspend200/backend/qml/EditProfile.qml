import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: page; anchors.fill: parent; color: "#F5F7FB"; property string errorMessage: ""
    Rectangle { width: parent.width; height: 104; color: "#151C35"
        Row { anchors.left: parent.left; anchors.leftMargin: 26; anchors.verticalCenter: parent.verticalCenter; spacing: 15
            Text { text: "Back"; color: "#C9C4DF"; font.pixelSize: 13; MouseArea { anchors.fill: parent; onClicked: stackView.pop() } }
            Rectangle { width: 1; height: 20; color: "#5E557A" }
            Column { spacing: 3
                Text { text: "Edit profile"; color: "white"; font.pixelSize: 24; font.bold: true }
                Text { text: "Update how your account appears."; color: "#B8B2CC"; font.pixelSize: 12 }
            }
        }
    }
    Column { width: Math.min(parent.width - 48, 500); anchors.horizontalCenter: parent.horizontalCenter; anchors.top: parent.top; anchors.topMargin: 138; spacing: 12
        Rectangle { width: parent.width; height: 270; radius: 18; color: "white"; border.color: "#E4E7EF"
            Column { anchors.fill: parent; anchors.margins: 22; spacing: 10
                Text { text: "PERSONAL DETAILS"; color: "#667087"; font.pixelSize: 10; font.bold: true; font.letterSpacing: 1 }
                Text { text: "FULL NAME"; color: "#667087"; font.pixelSize: 10; font.bold: true; font.letterSpacing: 1 }
                TextField { id: nameInput; width: parent.width; height: 42; text: backend.currentUserName(); background: Rectangle { radius: 10; color: "#F7F8FC"; border.color: "#E2E6EF" } }
                Text { text: "EMAIL ADDRESS"; color: "#667087"; font.pixelSize: 10; font.bold: true; font.letterSpacing: 1 }
                TextField { id: emailInput; width: parent.width; height: 42; text: backend.currentUserEmail(); background: Rectangle { radius: 10; color: "#F7F8FC"; border.color: "#E2E6EF" } }
                Text { text: page.errorMessage; color: "#C7354A"; visible: text !== ""; font.pixelSize: 11 }
            }
        }
        Rectangle { width: parent.width; height: 48; radius: 12; color: "#1E3A8A"
            Text { text: "Save changes"; color: "white"; font.pixelSize: 15; font.bold: true; anchors.centerIn: parent }
            MouseArea { anchors.fill: parent; onClicked: { if (backend.updateProfile(nameInput.text, emailInput.text)) stackView.pop(); else page.errorMessage = backend.getLastAuthError() } }
        }
    }
}
