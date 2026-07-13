import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    anchors.fill: parent

    // 🌈 Background
    Rectangle {
        anchors.fill: parent
        color: "#F4F6FA"

        Column {
            anchors.fill: parent
            spacing: 0

            // ===========================
            // 🔷 TOP HEADER
            // ===========================
            Rectangle {
                width: parent.width
                height: 240

                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#5C3B8A" }
                    GradientStop { position: 1.0; color: "#8E7CC3" }
                }

                Column {
                    anchors.centerIn: parent
                    spacing: 8

                    Text {
                        text: "Create Account"
                        color: "white"
                        font.pixelSize: 22
                        font.bold: true
                    }

                    Text {
                        text: "Join VoxSpend"
                        color: "#E0E0E0"
                        font.pixelSize: 14
                    }
                }
            }

            // ===========================
            // 🧾 SIGNUP CARD
            // ===========================
            Rectangle {
                width: parent.width - 60
                height: 380
                radius: 18
                color: "white"

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: -50

                border.color: "#dddddd"

                Column {
                    anchors.fill: parent
                    anchors.margins: 25
                    spacing: 16

                    // 👤 NAME
                    Column {
                        spacing: 4
                        Text { text: "Full Name"; color: "#555"; font.pixelSize: 13 }

                        TextField {
                            width: parent.width
                            height: 42
                            placeholderText: "Enter your name"
                        }
                    }

                    // 📧 EMAIL
                    Column {
                        spacing: 4
                        Text { text: "Email"; color: "#555"; font.pixelSize: 13 }

                        TextField {
                            width: parent.width
                            height: 42
                            placeholderText: "Enter your email"
                        }
                    }

                    // 🔒 PASSWORD
                    Column {
                        spacing: 4
                        Text { text: "Password"; color: "#555"; font.pixelSize: 13 }

                        TextField {
                            width: parent.width
                            height: 42
                            echoMode: TextInput.Password
                            placeholderText: "Create password"
                        }
                    }

                    // 🔒 CONFIRM PASSWORD
                    Column {
                        spacing: 4
                        Text { text: "Confirm Password"; color: "#555"; font.pixelSize: 13 }

                        TextField {
                            width: parent.width
                            height: 42
                            echoMode: TextInput.Password
                            placeholderText: "Re-enter password"
                        }
                    }

                    // 🟣 SIGNUP BUTTON
                    Rectangle {
                        width: parent.width
                        height: 48
                        radius: 10
                        color: "#5C3B8A"

                        Text {
                            anchors.centerIn: parent
                            text: "Sign Up"
                            color: "white"
                            font.pixelSize: 16
                            font.bold: true
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                // 👉 After signup go to login
                                stackView.push(loginPage)
                            }
                        }
                    }

                    // 🔁 BACK TO LOGIN
                    Row {
                        anchors.horizontalCenter: parent.horizontalCenter
                        spacing: 5

                        Text {
                            text: "Already have an account?"
                            color: "#777"
                            font.pixelSize: 12
                        }

                        Text {
                            text: "Login"
                            color: "#5C3B8A"
                            font.bold: true
                            font.pixelSize: 12

                            MouseArea {
                                anchors.fill: parent
                                onClicked: stackView.pop()
                            }
                        }
                    }
                }
            }
        }
    }
}