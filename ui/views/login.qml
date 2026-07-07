import QtQuick 2.15
import QtQuick.Controls 2.15
import com.voxspend.backend 1.0

Item {
    id: signupRoot
    anchors.fill: parent
    property string errorMessage:""
    AuthManager{
        id: authBackend
        Component.onCompleted: {
            console.log("success")
        }
    }

    // 1. Top Header Component
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
            Image {
                id: voxspend
                source: "../../assets/icons/VoxSpend Logo (1).png"
                width: 300
                height: 200
                anchors.horizontalCenter: parent.horizontalCenter

            }

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
            // --- Error Message Box ---
                Rectangle {
                    id: errorBox
                    width: parent.width
                    height: errorMessage !== "" ? 45 : 0  // Drops to 0 height when there's no error
                    color: "#FFEEEE"                     // Soft red background
                    border.color: "#FF4D4D"              // Red outline
                    border.width: 1
                    radius: 8
                    visible: errorMessage !== ""         // Only visible if there is a message
                    clip: true                           // Keeps text hidden while collapsing

                    // Smoothly slides open or closed when the message changes
                    Behavior on height {
                        NumberAnimation { duration: 200 }
                    }

                    Text {
                        text: errorMessage
                        color: "#D32F2F"                 // Easy-to-read dark red text
                        font.pixelSize: 13
                        font.bold: true
                        anchors.centerIn: parent
                    }
                }

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
                color: "#8067B7"

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
                        var loginSuccessful = authBackend.loginUser(emailInput.text,passwordInput.text)
                        if (loginSuccessful){
                            console.log("successful")
                            errorMessage = ""
                        }
                        else{
                            console.log("fail")
                            errorMessage = "Invalid email or password. Please try again."
                        }

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
            color: "#8067B7"
            font.bold: true
            font.pixelSize: 13

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    window.activeView = "signup"
                    console.log("Go to Sign Up Page");

                }
            }
        }
    }
}
