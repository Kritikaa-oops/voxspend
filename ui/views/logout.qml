import QtQuick 2.15
import QtQuick.Controls 2.15

Item{
    id: logoutPage
    anchors.fill: parent

    // Header
    Rectangle {
        id: header
        width: parent.width
        height: 200

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#8067B7" }
            GradientStop { position: 1.0; color: "#E6E6FA" }
        }

        Column {
            anchors.centerIn: parent
            spacing: 8

            Text {
                text: "My Account"
                color: "white"
                font.pixelSize: 24
                font.bold: true
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Text {
                text: "Manage your account"
                color: "#F5F5F5"
                font.pixelSize: 13
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }

    // Main Card
    Rectangle {
        width: parent.width - 40
        height: 320
        radius: 16
        color: "white"
        border.color: "#E0E0E0"
        border.width: 1

        anchors.top: header.bottom
        anchors.topMargin: -20
        anchors.horizontalCenter: parent.horizontalCenter

        Column {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 20

            Rectangle {
                width: 90
                height: 90
                radius: 45
                color: "#E8F5E9"
                anchors.horizontalCenter: parent.horizontalCenter

                Text {
                    anchors.centerIn: parent
                    text: "👤"
                    font.pixelSize: 40
                }
            }

            Text {
                text: "diya"
                font.pixelSize: 22
                font.bold: true
                color: "#333333"
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Text {
                text: "diya@example.com"
                font.pixelSize: 14
                color: "#777777"
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Rectangle {
                width: parent.width
                height: 50
                radius: 12
                color: "#8067B7"

                Text {
                    anchors.centerIn: parent
                    text: "Logout"
                    color: "white"
                    font.bold: true
                    font.pixelSize: 16
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("User Logged Out")

                        // Example navigation
                        // stackView.replace(Qt.resolvedUrl("Login.qml"))

                        // Or if using Loader:
                        // loader.source = "Login.qml"
                    }
                }
            }
        }
    }

    // Footer
    Row {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 5

        Text {
            text: "Want to continue?"
            color: "#777777"
            font.pixelSize: 13
        }

        Text {
            text: "Go Back"
            color: "#8067B7"
            font.bold: true
            font.pixelSize: 13

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("Go Back")
                    window.activeView = "account"
                }
            }
        }
    }
}
