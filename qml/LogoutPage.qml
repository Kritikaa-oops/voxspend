import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    anchors.fill: parent; color: "#F5F7FB"
    Rectangle { width: parent.width; height: 170; color: "#151C35"
        Row { anchors.left: parent.left; anchors.leftMargin: 26; anchors.top: parent.top; anchors.topMargin: 24; spacing: 15
            Text { text: "Back"; color: "#C9C4DF"; font.pixelSize: 13; MouseArea { anchors.fill: parent; onClicked: stackView.pop() } }
            Rectangle { width: 1; height: 20; color: "#5E557A" }
            Text { text: "Profile"; color: "white"; font.pixelSize: 15; font.bold: true }
        }
        Column { anchors.horizontalCenter: parent.horizontalCenter; anchors.bottom: parent.bottom; anchors.bottomMargin: 22; spacing: 5
            Rectangle { width: 58; height: 58; radius: 29; color: "#A892E3"; anchors.horizontalCenter: parent.horizontalCenter; NavIcon { name: "user"; strokeColor: "#151C35"; anchors.centerIn: parent } }
            Text { text: "Diya"; color: "white"; font.pixelSize: 20; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter }
        }
    }
    Column { width: Math.min(parent.width - 48, 500); anchors.horizontalCenter: parent.horizontalCenter; anchors.top: parent.top; anchors.topMargin: 202; spacing: 14
        Rectangle { width: parent.width; height: 78; radius: 16; color: "white"; border.color: "#E4E7EF"
            Column { anchors.left: parent.left; anchors.leftMargin: 18; anchors.verticalCenter: parent.verticalCenter; spacing: 4
                Text { text: "diya@example.com"; color: "#313B55"; font.pixelSize: 14; font.bold: true }
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
            MouseArea { anchors.fill: parent; onClicked: stackView.replace("LoginPage.qml") }
        }
    }
}
