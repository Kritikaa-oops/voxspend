import QtQuick 2.15
import QtQuick.Controls 2.15

Window{
    width:400;
    height:750;
    visible:true;


    // 1. Top Header Component
    Rectangle {
        id: header
        width: parent.width
        height: 200
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#4CAF50" }
            GradientStop { position: 1.0; color: "#E9F9E5" }
        }

        Column {
            anchors.centerIn: parent
            spacing: 8

            Text {
                text: "Welcome Back"
                color: "white"
                font.pixelSize: 24
                font.bold: true
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Text {
                text: "Login to track your spendings"
                color: "#666"
                font.pixelSize: 13
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }

    // 2. Input Fields Container (Form Box)
    Rectangle {
        width: parent.width - 40
        height: 280 // Shorter height since there are fewer fields
        radius: 16
        color: "#ffffff"
        border.color: "#E0E0E0"
        border.width: 1
        anchors.top: header.bottom
        anchors.topMargin: -20
        anchors.horizontalCenter: parent.horizontalCenter

        Column {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 20

            // --- Email Input ---
            TextField {
                id: emailInput
                width: parent.width
                placeholderText: "Email Address"
                selectByMouse: true
            }

            // --- Password Input ---
            TextField {
                id: passwordInput
                width: parent.width
                placeholderText: "Password"
                echoMode: TextField.Password
                selectByMouse: true
            }

            // --- Login Button ---
            Rectangle {
                width: parent.width
                height: 48
                radius: 12
                color: "#4CAF50"

                Text {
                    text: "Login"
                    color: "white"
                    font.bold: true
                    font.pixelSize: 16
                    anchors.centerIn: parent
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("Logging in user:", emailInput.text)
                        // Action: stackView.push(homePage)
                    }
                }
            }
        }
    }

    // 3. Footer Area (For new users)
    Row {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 5

        Text {
            text: "Don't have an account?"
            color: "#777"
            font.pixelSize: 13
        }

        Text {
            text: "Sign Up"
            color: "#4CAF50"
            font.bold: true
            font.pixelSize: 13

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    stackView.push(Qt.resolvedUrl("Main.qml"));
                    console.log("Go to Sign Up Page");

                }
            }
        }
    }
}
