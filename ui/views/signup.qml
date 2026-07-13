import QtQuick 2.15
import QtQuick.Controls 2.15
import com.voxspend.backend 1.0

Item {
    id: signupRoot
    anchors.fill: parent
    property string errorMessage:""
    AuthManager{
        id: authBackend
    }




    // 1. Top Header Component (Matches your homepage header style)
    Rectangle {
        id: header
        width: parent.width
        height: 320
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#8067B7" }
            GradientStop { position: 1.0; color: "#E6E6FA" }
        }
    }

    Column {
            width: parent.width
            y:25
            spacing: 6
            Image {
                id: voxspend
                source: "../../assets/icons/VoxSpend Logo (1).png"
                width: 200
                height: 150
                fillMode: Image.PreserveAspectFit
                anchors.horizontalCenter: parent.horizontalCenter

            }

            Text {
                text: "Create Account"
                color: "white"
                font.pixelSize: 20
                font.bold: true
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Text {
                text: "Sign up to start tracking your spendings"
                color: "#E6E6FA"
                font.pixelSize: 18
                anchors.horizontalCenter: parent.horizontalCenter
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
                color: "#8067B7" // VoxSpend theme primary green

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
                        console.log("Signing up user:", nameInput.text)
                        var signupSuccessful = authBackend.registerUser(emailInput.text,passwordInput.text,nameInput.text)
                        if (signupSuccessful){
                            console.log("success")

                        window.activeView = "dashboard"
                        }else{
                            console.log("fail")
                        }


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
            color: "#8067B7"
            font.bold: true
            font.pixelSize: 13

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("Go to Login Page")
                    window.activeView = "login"
                }
            }
        }
    }
}
