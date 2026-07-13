import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    anchors.fill: parent

    Rectangle {
        width: parent.width
        height: 200

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#8067B7" }
            GradientStop { position: 1.0; color: "#E6E6FA" }
        }

        Text {
            text: "My Account"
            anchors.centerIn: parent
            color: "white"
            font.pixelSize: 22
            font.bold: true
        }
    }

    Rectangle {
        width: parent.width - 40
        height: 250
        radius: 16
        color: "white"
        border.color: "#E0E0E0"

        anchors.top: parent.top
        anchors.topMargin: 150
        anchors.horizontalCenter: parent.horizontalCenter

        Column {
            anchors.centerIn: parent
            spacing: 16

            Text {
                text: "diya"
                font.pixelSize: 20
                font.bold: true
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Text {
                text: "diya@example.com"
                color: "#777"
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Rectangle {
                width: 150
                height: 45
                radius: 10
                color: logoutMouse.pressed ? "#6A55A3" : "#8067B7"

                Text {
                    text: "Logout"
                    anchors.centerIn: parent
                    color: "white"
                }

                MouseArea {
                    id: logoutMouse
                    anchors.fill: parent
                    onClicked: window.activeView = "login"
                }
            }
        }
    }
}