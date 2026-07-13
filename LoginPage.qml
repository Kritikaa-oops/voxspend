import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    anchors.fill: parent

    Rectangle {
        anchors.fill: parent
        color: "#F4F6FA"

        Column {
            anchors.fill: parent
            spacing: 0

            Rectangle {
                width: parent.width
                height: 260
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#5C3B8A" }
                    GradientStop { position: 1.0; color: "#8E7CC3" }
                }

                Column {
                    anchors.centerIn: parent
                    spacing: 10

                    Image {
                        source: "logo.png"
                        width: 120; height: 120
                        fillMode: Image.PreserveAspectFit
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Text {
                        text: "Welcome Back"
                        color: "white"
                        font.pixelSize: 22; font.bold: true
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Text {
                        text: "Login to continue"
                        color: "#E0E0E0"
                        font.pixelSize: 14
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }
            }

            Rectangle {
                width: parent.width - 60
                height: 320
                radius: 18; color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: -60
                border.color: "#dddddd"

                Column {
                    anchors.fill: parent
                    anchors.margins: 25
                    spacing: 18

                    Column {
                        width: parent.width; spacing: 5
                        Text { text: "Email"; color: "#555"; font.pixelSize: 13 }
                        TextField {
                            width: parent.width; height: 42
                            placeholderText: "Enter your email"
                            font.pixelSize: 14
                        }
                    }

                    Column {
                        width: parent.width; spacing: 5
                        Text { text: "Password"; color: "#555"; font.pixelSize: 13 }
                        TextField {
                            width: parent.width; height: 42
                            placeholderText: "Enter your password"
                            echoMode: TextInput.Password
                            font.pixelSize: 14
                        }
                    }

                    Rectangle {
                        width: parent.width; height: 48; radius: 10
                        color: "#5C3B8A"

                        Text {
                            anchors.centerIn: parent
                            text: "Login"; color: "white"
                            font.pixelSize: 16; font.bold: true
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: stackView.replace(homePage)
                        }
                    }

                    Row {
                        anchors.horizontalCenter: parent.horizontalCenter
                        spacing: 5

                        Text { text: "Don't have an account?"; color: "#777"; font.pixelSize: 12 }
                        Text {
                            text: "Sign up"; color: "#5C3B8A"; font.bold: true; font.pixelSize: 12
                            MouseArea {
                                anchors.fill: parent
                                onClicked: stackView.push(signupPage)
                            }
                        }
                    }
                }
            }
        }
    }
}