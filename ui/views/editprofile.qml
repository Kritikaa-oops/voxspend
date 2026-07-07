import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: editProfilePage
    anchors.fill: parent

    signal backClicked()
    signal saveClicked()

    // Header (Identical to your Account Page)
    Rectangle {
        id: header
        width: parent.width
        height: 180
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#8067B7" }
            GradientStop { position: 1.0; color: "#E6E6FA" }
        }

        Rectangle {
            width: 40; height: 40; radius: 20; color: "#20000000"
            anchors.left: parent.left; anchors.top: parent.top; anchors.leftMargin: 16; anchors.topMargin: 16
            Text { text: "←"; color: "white"; font.pixelSize: 20; anchors.centerIn: parent }
            MouseArea { anchors.fill: parent; onClicked: {window.activeView = "account"} }
        }

        Text { text: "Edit Profile"; color: "white"; font.pixelSize: 20; font.bold: true; anchors.centerIn: parent }
    }

    // Input Form Area
    Column {
        width: parent.width - 32
        anchors.top: header.bottom; anchors.topMargin: 20; anchors.horizontalCenter: parent.horizontalCenter
        spacing: 20

        // Helper for Inputs
        Component {
            id: inputFieldTemplate
            Column {
                spacing: 8
                property alias label: lbl.text
                property alias text: input.text
                Text { id: lbl; font.pixelSize: 14; color: "#777777" }
                Rectangle {
                    width: parent.width; height: 50; radius: 10; border.color: "#E0E0E0"; border.width: 1; color: "white"
                    TextField {
                        id: input
                        anchors.fill: parent; anchors.margins: 5
                        background: null
                        verticalAlignment: TextInput.AlignVCenter
                        font.pixelSize: 16
                    }
                }
            }
        }

        Loader { width: parent.width; sourceComponent: inputFieldTemplate; onLoaded: { item.label = "Full Name"; item.text = "diya" } }
        Loader { width: parent.width; sourceComponent: inputFieldTemplate; onLoaded: { item.label = "Email Address"; item.text = "diya@example.com" } }

        Item { height: 10 } // Spacer

        // Save Button
        Rectangle {
            width: parent.width; height: 50; radius: 10
            color: "#8067B7" // Matches header gradient
            Text { text: "Save Changes"; color: "white"; font.bold: true; anchors.centerIn: parent }
            MouseArea { anchors.fill: parent; onClicked: editProfilePage.saveClicked() }
        }
    }
}