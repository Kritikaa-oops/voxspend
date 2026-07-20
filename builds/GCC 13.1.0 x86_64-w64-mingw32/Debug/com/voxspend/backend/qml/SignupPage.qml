import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    anchors.fill: parent
    property string authError: ""
    Rectangle { anchors.fill: parent; color: "#F5F7FB" }
    Rectangle { width: parent.width; height: 210; gradient: Gradient { GradientStop { position: 0; color: "#151C35" } GradientStop { position: 1; color: "#49337B" } }
        Column { anchors.centerIn: parent; spacing: 7
            Text { text: "Create your account"; color: "white"; font.pixelSize: 27; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter }
            Text { text: "A clearer view of every rupee."; color: "#C9C4DF"; font.pixelSize: 14; anchors.horizontalCenter: parent.horizontalCenter }
        }
    }
    Rectangle { width: Math.min(parent.width - 64, 440); height: 480; radius: 22; color: "white"; border.color: "#E5E8F0"; anchors.horizontalCenter: parent.horizontalCenter; anchors.top: parent.top; anchors.topMargin: 150
        Column { anchors.fill: parent; anchors.margins: 28; spacing: 10
            Text { text: "Get started"; color: "#19213D"; font.pixelSize: 21; font.bold: true }
            Text { text: "Set up your personal spending space."; color: "#7A8498"; font.pixelSize: 12; bottomPadding: 6 }
            Text { text: "FULL NAME"; color: "#606B80"; font.pixelSize: 10; font.bold: true; font.letterSpacing: 1 }
            TextField { id: nameField; width: parent.width; height: 42; placeholderText: "Your name"; onTextChanged: authError = ""; background: Rectangle { radius: 10; color: "#F7F8FC"; border.color: "#E2E6EF" } }
            Text { text: "EMAIL ADDRESS"; color: "#606B80"; font.pixelSize: 10; font.bold: true; font.letterSpacing: 1 }
            TextField { id: emailField; width: parent.width; height: 42; placeholderText: "name@example.com"; onTextChanged: authError = ""; background: Rectangle { radius: 10; color: "#F7F8FC"; border.color: "#E2E6EF" } }
            Text { text: "PASSWORD"; color: "#606B80"; font.pixelSize: 10; font.bold: true; font.letterSpacing: 1 }
            TextField { id: passwordField; width: parent.width; height: 42; echoMode: TextInput.Password; placeholderText: "Create a password"; onTextChanged: authError = ""; background: Rectangle { radius: 10; color: "#F7F8FC"; border.color: "#E2E6EF" } }
            Text { text: "CONFIRM PASSWORD"; color: "#606B80"; font.pixelSize: 10; font.bold: true; font.letterSpacing: 1 }
            TextField { id: confirmPasswordField; width: parent.width; height: 42; echoMode: TextInput.Password; placeholderText: "Repeat password"; onTextChanged: authError = ""; background: Rectangle { radius: 10; color: "#F7F8FC"; border.color: "#E2E6EF" } }
            Text { width: parent.width; text: authError; visible: text !== ""; color: "#C7354A"; font.pixelSize: 11; wrapMode: Text.Wrap }
            Rectangle { width: parent.width; height: 46; radius: 12; color: "#6D4CC4"; Text { anchors.centerIn: parent; text: "Create account"; color: "white"; font.bold: true } MouseArea { anchors.fill: parent; onClicked: { if (backend.signup(nameField.text, emailField.text, passwordField.text, confirmPasswordField.text)) stackView.replace(homePage); else authError = backend.getLastAuthError() } } }
        }
    }
    Text { anchors.horizontalCenter: parent.horizontalCenter; anchors.bottom: parent.bottom; anchors.bottomMargin: 20; text: "Already have an account?  Sign in"; color: "#6D4CC4"; font.pixelSize: 12; MouseArea { anchors.fill: parent; onClicked: stackView.pop() } }
}
