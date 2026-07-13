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

        // Back Button to safely escape deep tab view nesting
        Rectangle {
            width: 36; height: 36; radius: 18
            color: "white"; opacity: 0.85
            anchors.left: parent.left; anchors.leftMargin: 16
            anchors.verticalCenter: parent.verticalCenter
            Text { text: "←"; color: "#543D6F"; font.pixelSize: 18; font.bold: true; anchors.centerIn: parent }
            MouseArea { anchors.fill: parent; onClicked: stackView.pop() }
        }
    }

    Rectangle {
        width: parent.width - 40
        height: 300
        radius: 16; color: "white"; border.color: "#E0E0E0"
        anchors.top: parent.top; anchors.topMargin: 150
        anchors.horizontalCenter: parent.horizontalCenter

        Column {
            anchors.centerIn: parent
            spacing: 20

            Text { text: "diya"; font.pixelSize: 20; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter }
            Text { text: "diya@example.com"; color: "#777"; anchors.horizontalCenter: parent.horizontalCenter }

            // Edit Profile Button Action
            Rectangle {
                width: 180; height: 45; radius: 10
                color: "#E9F9E5"; border.color: "#543D6F"; border.width: 1
                Text { text: "Edit Profile"; anchors.centerIn: parent; color: "#543D6F"; font.bold: true }
                MouseArea {
                    anchors.fill: parent
                    onClicked: stackView.push("EditProfile.qml")
                }
            }

            // Logout Action Button
            Rectangle {
                width: 180; height: 45; radius: 10
                color: "#8067B7"
                Text { text: "Logout"; anchors.centerIn: parent; color: "white"; font.bold: true }
                MouseArea {
                    anchors.fill: parent
                    onClicked: stackView.clear() // Clear user stack history back to login state
                }
            }
        }
    }
}