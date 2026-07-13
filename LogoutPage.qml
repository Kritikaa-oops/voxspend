import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt.labs.platform 1.1

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
        height: 420
        radius: 16; color: "white"; border.color: "#E0E0E0"
        anchors.top: parent.top; anchors.topMargin: 150
        anchors.horizontalCenter: parent.horizontalCenter

        Column {
            anchors.centerIn: parent
            spacing: 16

            // ===== PROFILE PICTURE SELECTION AREA =====
            Rectangle {
                id: profileImageContainer
                width: 100
                height: 100
                radius: 50
                color: "#E6E6FA"
                border.color: "#8067B7"
                border.width: 2
                anchors.horizontalCenter: parent.horizontalCenter
                clip: true

                Text {
                    id: placeholderIcon
                    text: "📷"
                    font.pixelSize: 32
                    anchors.centerIn: parent
                    visible: userProfileImage.status !== Image.Ready
                }

                Image {
                    id: userProfileImage
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectCrop
                    source: ""
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: imagePicker.open()
                }
            }

            // ===== USER DETAILS =====
            Text { text: "diya"; font.pixelSize: 20; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter }
            Text { text: "diya@example.com"; color: "#777"; anchors.horizontalCenter: parent.horizontalCenter }

            // ===== POSITION SPACER =====
            Item {
                width: 1
                height: 25
            }

            // ===== ACTION BUTTONS =====
            Rectangle {
                width: 180; height: 45; radius: 10
                color: "#E9F9E5"; border.color: "#543D6F"; border.width: 1
                Text { text: "Edit Profile"; anchors.centerIn: parent; color: "#543D6F"; font.bold: true }
                MouseArea {
                    anchors.fill: parent
                    onClicked: stackView.push("EditProfile.qml")
                }
            }

            Rectangle {
                width: 180; height: 45; radius: 10
                color: "#8067B7"
                Text { text: "Logout"; anchors.centerIn: parent; color: "white"; font.bold: true }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        // Clears back-history and drops the user squarely onto the login window
                        stackView.replace("LoginPage.qml")
                    }
                }
            }
        }
    }

    // ===== FILE PICKER DIALOG =====
    FileDialog {
        id: imagePicker
        title: "Choose Profile Picture"
        nameFilters: [ "Image files (*.png *.jpg *.jpeg)" ]
        onAccepted: {
            userProfileImage.source = imagePicker.file
        }
    }
}