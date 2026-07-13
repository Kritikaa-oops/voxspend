import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: editProfilePage
    anchors.fill: parent

    property string errorMessage: ""

    // ===== HEADER =====
    Rectangle {
        width: parent.width
        height: 180

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#8067B7" }
            GradientStop { position: 1.0; color: "#E6E6FA" }
        }

        // Back Button
        Rectangle {
            width: 40
            height: 40
            radius: 20
            color: "#20000000"

            anchors.left: parent.left
            anchors.top: parent.top
            anchors.margins: 16

            Text {
                text: "←"
                color: "white"
                font.pixelSize: 20
                anchors.centerIn: parent
            }

            MouseArea {
                anchors.fill: parent
                onClicked: window.activeView = "account"
            }
        }

        Text {
            text: "Edit Profile"
            color: "white"
            font.pixelSize: 20
            font.bold: true
            anchors.centerIn: parent
        }
    }

    // ===== FORM =====
    Column {
        width: parent.width - 32
        anchors.top: parent.top
        anchors.topMargin: 200
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 16

        // Name
        Text { text: "Full Name"; color: "#777"; font.pixelSize: 13 }
        Rectangle {
            width: parent.width
            height: 50
            radius: 10
            border.color: "#E0E0E0"

            TextField {
                id: nameInput
                anchors.fill: parent
                anchors.margins: 8
                text: "diya"
                background: null
            }
        }

        // Email
        Text { text: "Email"; color: "#777"; font.pixelSize: 13 }
        Rectangle {
            width: parent.width
            height: 50
            radius: 10
            border.color: "#E0E0E0"

            TextField {
                id: emailInput
                anchors.fill: parent
                anchors.margins: 8
                text: "diya@example.com"
                background: null
            }
        }

        // Error Message
        Text {
            text: editProfilePage.errorMessage
            color: "red"
            font.pixelSize: 12
            visible: text !== ""
        }

        Item { height: 10 }

        // ===== SAVE BUTTON =====
        Rectangle {
            width: parent.width
            height: 50
            radius: 10
            color: saveMouse.pressed ? "#6A55A3" : "#8067B7"

            Text {
                text: "Save Changes"
                color: "white"
                font.bold: true
                anchors.centerIn: parent
            }

            MouseArea {
                id: saveMouse
                anchors.fill: parent

                onClicked: {
                    if (nameInput.text === "" || emailInput.text === "") {
                        editProfilePage.errorMessage = "Fields cannot be empty"
                        return
                    }

                    editProfilePage.errorMessage = ""

                    console.log("Saved:", nameInput.text, emailInput.text)

                    // Navigate back to account page
                    window.activeView = "account"
                }
            }
        }
    }
}