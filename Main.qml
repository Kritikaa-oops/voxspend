import QtQuick 2.15
import QtQuick.Controls 2.15

Window{
    width:400;
    height:750;
    visible:true;
    title:"Voxspend";



    // 1. Top Header Component (Matches your homepage header style)
    Rectangle {
        id: header
        width: parent.width
        height: 200
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#4CAF50" }
            GradientStop { position: 1.0; color: "#E9F9E5" }
        }
    }



    StackView{
            id:stackView
            anchors.top: header.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            initialItem: "Login.qml"




        Column {
            anchors.centerIn: parent
            spacing: 8

            Text {
                text: "Create Account"
                color: "white"
                font.pixelSize: 24
                font.bold: true
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Text {
                text: "Sign up to start tracking your spendings"
                color: "black"
                font.pixelSize: 13
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }


    // 2. Input Fields Container (Form Box)
    Rectangle {
        width: parent.width - 40 // Gives 20px padding on left and right
        height: 380
        radius: 16
        color: "#ffffff"
        anchors.top: header.bottom
        anchors.topMargin: -20 // Pulls the card slightly up into the gradient for a modern look
        anchors.horizontalCenter: parent.horizontalCenter

        // Subtle shadow simulation using borders since you are a beginner
        border.color: "#E0E0E0"
        border.width: 1

        Column {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 16

            // --- Fulls Name Input ---
            Column {
                width: parent.width
                spacing: 6
                Text { text: "Full Name"; color: "#555"; font.pixelSize: 12; font.bold: true }
                TextField {
                    id: nameInput
                    width: parent.width
                    placeholderText: "Enter your full name"
                    selectByMouse: true
                }
            }

            // --- Email Input ---
            Column {
                width: parent.width
                spacing: 6
                Text { text: "Email Address"; color: "#555"; font.pixelSize: 12; font.bold: true }
                TextField {
                    id: emailInput
                    width: parent.width
                    placeholderText: "name@example.com"
                    selectByMouse: true
                }
            }

            // --- Password Input ---
            Column {
                width: parent.width
                spacing: 6
                Text { text: "Password"; color: "#555"; font.pixelSize: 12; font.bold: true }
                TextField {
                    id: passwordInput
                    width: parent.width
                    placeholderText: "Min. 8 characters"
                    echoMode: TextField.Password // Hides the password typing
                    selectByMouse: true
                }
            }

            // Space holder to push the button down slightly
            Item { width: 1; height: 10 }

            // --- Sign Up Button ---
            Rectangle {
                width: parent.width
                height: 48
                radius: 12
                color: "#4CAF50" // VoxSpend theme primary green

                Text {
                    text: "Sign Up"
                    color: "white"
                    font.bold: true
                    font.pixelSize: 16
                    anchors.centerIn: parent
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        // Beginner Note: This is where you would handle authentication
                        console.log("Signing up user:", nameInput.text, emailInput.text)

                        // After signing up, go to home page
                        // Assuming you navigate using your StackView:

                    }
                }
            }
        }
    }

    // 3. Footer Area (For existing users)
    Row {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 5

        Text {
            text: "Already have an account?"
            color: "#777"
            font.pixelSize: 13
        }

        Text {
            text: "Login"
            color: "#4CAF50"
            font.bold: true
            font.pixelSize: 13

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("Go to Login Page")
                    stackView.push(Qt.resolvedUrl("Login.qml"));
                }
            }
        }
    }
}
