import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    anchors.fill: parent
    property string authError: ""
    Rectangle { anchors.fill: parent; color: "#F5F7FB" }
    Rectangle { width: parent.width; height: 260; gradient: Gradient { GradientStop { position: 0; color: "#151C35" } GradientStop { position: 1; color: "#49337B" } }
        Column { anchors.centerIn: parent; spacing: 8
            Image { source: "logo.png"; width: 76; height: 76; fillMode: Image.PreserveAspectFit; anchors.horizontalCenter: parent.horizontalCenter }
            Text { text: "Welcome back"; color: "white"; font.pixelSize: 28; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter }
            Text { text: "Sign in to manage your spending."; color: "#C9C4DF"; font.pixelSize: 14; anchors.horizontalCenter: parent.horizontalCenter }
        }
    }
    Rectangle { width: Math.min(parent.width - 64, 440); height: 370; radius: 22; color: "white"; border.color: "#E5E8F0"; anchors.horizontalCenter: parent.horizontalCenter; anchors.top: parent.top; anchors.topMargin: 208
        Column { anchors.fill: parent; anchors.margins: 30; spacing: 16
            Text { text: "Sign in"; color: "#19213D"; font.pixelSize: 21; font.bold: true }
            Text { text: "Use your VoxSpend account to continue."; color: "#7A8498"; font.pixelSize: 12 }
            Text { text: "EMAIL ADDRESS"; color: "#606B80"; font.pixelSize: 10; font.bold: true; font.letterSpacing: 1 }
            TextField { id: emailField; width: parent.width; height: 46; placeholderText: "name@example.com"; color: "#19213D"; font.pixelSize: 14; onTextChanged: authError = ""; background: Rectangle { radius: 10; color: "#F7F8FC"; border.color: emailField.activeFocus ? "#6D4CC4" : "#E2E6EF"; border.width: emailField.activeFocus ? 2 : 1 } }
            Text { text: "PASSWORD"; color: "#606B80"; font.pixelSize: 10; font.bold: true; font.letterSpacing: 1 }
            TextField { id: passwordField; width: parent.width; height: 46; placeholderText: "Enter your password"; echoMode: TextInput.Password; color: "#19213D"; font.pixelSize: 14; onTextChanged: authError = ""; background: Rectangle { radius: 10; color: "#F7F8FC"; border.color: passwordField.activeFocus ? "#6D4CC4" : "#E2E6EF"; border.width: passwordField.activeFocus ? 2 : 1 } }
            Text { width: parent.width; text: authError; visible: text !== ""; color: "#C7354A"; font.pixelSize: 12; wrapMode: Text.Wrap }
            Rectangle { width: parent.width; height: 48; radius: 12; color: "#6D4CC4"; Text { anchors.centerIn: parent; text: "Sign in"; color: "white"; font.pixelSize: 15; font.bold: true } MouseArea { anchors.fill: parent; onClicked: { if (backend.login(emailField.text, passwordField.text)) stackView.replace(homePage); else authError = backend.getLastAuthError() } } }
        }
    }
    Row { anchors.horizontalCenter: parent.horizontalCenter; anchors.bottom: parent.bottom; anchors.bottomMargin: 24; spacing: 5
        Text { text: "New to VoxSpend?"; color: "#7A8498"; font.pixelSize: 12 }
        Text { text: "Create an account"; color: "#6D4CC4"; font.pixelSize: 12; font.bold: true; MouseArea { anchors.fill: parent; onClicked: stackView.push(signupPage) } }
    }
}
