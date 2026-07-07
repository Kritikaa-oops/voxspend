import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: accountPage
    anchors.fill: parent

    signal logoutClicked()
    signal backClicked()
    signal profileClicked()
    signal settingsClicked()

    // Inline template blueprint
    Component {
        id: menuOptionTemplate
        Rectangle {
            id: optionRect
            width: parent.width
            height: 56
            radius: 12
            color: optionMouse.containsPress ? "#F5F5F5" : "white"
            border.color: "#E0E0E0"
            border.width: 1

            property string icon: ""
            property string title: ""
            signal clicked()

            Row {
                anchors.left: parent.left
                anchors.leftMargin: 16
                anchors.verticalCenter: parent.verticalCenter
                spacing: 16

                Text { text: optionRect.icon; font.pixelSize: 20; anchors.verticalCenter: parent.verticalCenter }
                Text { text: optionRect.title; color: "#333333"; font.pixelSize: 15; anchors.verticalCenter: parent.verticalCenter }
            }
                Text { text: "›"; color: "#BDBDBD"; font.pixelSize: 22; anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter }

            MouseArea { id: optionMouse; anchors.fill: parent; onClicked: optionRect.clicked() }
        }
    }

    // Header Background
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
            MouseArea { anchors.fill: parent; onClicked:{window.activeView = "dashboard"} }
        }

        Text { text: "Account Settings"; color: "white"; font.pixelSize: 20; font.bold: true; anchors.centerIn: parent }
    }

    // Profile Card Overlap
    Rectangle {
        id: profileCard
        width: parent.width - 32; height: 100; radius: 12; color: "white"; border.color: "#E0E0E0"; border.width: 1
        anchors.top: header.bottom; anchors.topMargin: -30; anchors.horizontalCenter: parent.horizontalCenter

        Row {
            anchors.fill: parent; anchors.margins: 16; spacing: 16
            Rectangle {
                width: 60; height: 60; radius: 30; color: "#E8F5E9"
                Text { anchors.centerIn: parent; text: "👤"; font.pixelSize: 28 }
            }
            Column {
                spacing: 4; anchors.verticalCenter: parent.verticalCenter
                Text { text: "diya"; font.pixelSize: 18; font.bold: true; color: "#333333" }
                Text { text: "diya@example.com"; font.pixelSize: 13; color: "#777777" }
            }
        }
    }

    // Options Menu List
    Column {
        width: parent.width - 32
        anchors.top: profileCard.bottom; anchors.topMargin: 24; anchors.horizontalCenter: parent.horizontalCenter
        spacing: 8

        // Option 1 using Loader
        Loader {
            width: parent.width; sourceComponent: menuOptionTemplate
            onLoaded: { item.icon = "✏️"; item.title = "Edit Profile"; item.clicked.connect(function() { window.activeView = "Editprofile"})}
        }

        // Option 2 using Loader
        //Loader {
            //width: parent.width; sourceComponent: menuOptionTemplate
           // onLoaded: { item.icon = "⚙️"; item.title = "Preferences & Settings"; item.clicked.connect(accountPage.settingsClicked) }
       // }

        Item { width: parent.width; height: 16 }

        // Logout Button
        Rectangle {
            width: parent.width; height: 56; radius: 12; color: "#FEEBEE"; border.color: "#FFCDD2"; border.width: 1
            Row {
                anchors.fill: parent; anchors.leftMargin: 16; spacing: 16
                Text { text: "🚪"; font.pixelSize: 20; anchors.verticalCenter: parent.verticalCenter }
                Text { text: "Log Out"; color: "#D32F2F"; font.pixelSize: 16; font.bold: true; anchors.verticalCenter: parent.verticalCenter }
            }
            MouseArea { anchors.fill: parent
                        onClicked:{
                            accountPage.logoutClicked();
                            window.activeView = "logout";
                        }
            }
        }
    }
}
