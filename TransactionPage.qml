import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
color: "#F5FFF5"
anchors.fill: parent
// stores all transaction data
ListModel { id: transactionModel }
Column {
anchors.fill: parent
spacing: 0
//header
Rectangle {
width: parent.width * 0.9
anchors.horizontalCenter: parent.horizontalCenter
height: 80
gradient: Gradient {
GradientStop { position: 0.0; color: "#4CAF50" }
GradientStop { position: 1.0; color: "#E9F9E5" }
}
Row {
anchors.verticalCenter: parent.verticalCenter
anchors.left: parent.left
anchors.leftMargin: 16
spacing: 12
Rectangle {
width: 36; height: 36; radius: 18
color: "white"; opacity: 0.85
Text {
text: "←"; color: "#4CAF50"
font.pixelSize: 18; font.bold: true
anchors.centerIn: parent
}
MouseArea {
anchors.fill: parent
onClicked: stackView.pop()
}
}
//app logo
Image {
source: "logo.png"
width: 60; height: 60
fillMode: Image.PreserveAspectFit
anchors.verticalCenter: parent.verticalCenter
}
//page title
Text {
text: "Transactions"
color: "white"; font.pixelSize: 18; font.bold: true
anchors.verticalCenter: parent.verticalCenter
}
}
}
Rectangle {
width: parent.width
height: 56
color: "#F5FFF5"
Rectangle {
width: parent.width * 0.85
height: 42
radius: 12
color: "white"
anchors.centerIn: parent
border.color: "#c8f0c8"; border.width: 1
Row {
anchors.verticalCenter: parent.verticalCenter
anchors.left: parent.left
anchors.leftMargin: 12
spacing: 8
Text { text: "🔍"; font.pixelSize: 14 }
TextField {
id: searchField
width: parent.parent.width - 60
height: 40
placeholderText: "Search transactions..."
placeholderTextColor: "#bbb"
color: "#333"
background: Rectangle { color: "transparent" }
}
}
}
}
//category bar
Rectangle {
width: parent.width
height: 44
color: "#F5FFF5"
ScrollView {
anchors.fill: parent
ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
ScrollBar.vertical.policy: ScrollBar.AlwaysOff
Row {
spacing: 8
leftPadding: 14
Repeater {
model: ["All", "Food", "Transport", "Shopping", "Bills", "Other"]
Rectangle {
height: 32
width: filterLabel.width + 24
radius: 16
color: index === 0 ? "#4CAF50" : "#E9F9E5"
border.color: "#a5d6a7"; border.width: 1
Text {
id: filterLabel
text: modelData
color: index === 0 ? "white" : "#4CAF50"
font.pixelSize: 12; font.bold: true
anchors.centerIn: parent
}
}
}
}
}
}
Column {
visible: transactionModel.count === 0
anchors.horizontalCenter: parent.horizontalCenter
topPadding: 60
spacing: 12
Text {
text: "💳"
font.pixelSize: 48
anchors.horizontalCenter: parent.horizontalCenter
}
Text {
text: "No transactions yet"
color: "#888"; font.pixelSize: 15; font.bold: true
anchors.horizontalCenter: parent.horizontalCenter
}
Text {
text: "Add one from the home screen!"
color: "#aaa"; font.pixelSize: 13
anchors.horizontalCenter: parent.horizontalCenter
}
}
ListView {
id: listView
width: parent.width
height: parent.height - 180
model: transactionModel
clip: true
visible: transactionModel.count > 0
leftMargin: 14
rightMargin: 14
spacing: 8
delegate: Rectangle {
width: listView.width - 28
height: 68
radius: 14
color: "white"
border.color: "#e8f5e9"; border.width: 1
Row {
anchors.verticalCenter: parent.verticalCenter
anchors.left: parent.left
anchors.leftMargin: 14
spacing: 12
Rectangle {
width: 40; height: 40; radius: 20
color: "#E9F9E5"
Text {
text: "💳"
font.pixelSize: 18
anchors.centerIn: parent
}
}
//transacton details
Column {
spacing: 3
anchors.verticalCenter: parent.verticalCenter
Text { text: model.title;    color: "#1a1a1a"; font.pixelSize: 14; font.bold: true }
Text { text: model.category; color: "#888";font.pixelSize: 11 }
Text { text: model.date; color: "#bbb";font.pixelSize: 10 }
}
}
//amount display
Text {
text: "-Rs" + model.amount
color: "#e53935"; font.pixelSize: 14; font.bold: true
anchors.right: parent.right
anchors.rightMargin: 14
anchors.verticalCenter: parent.verticalCenter
}
}
}
}
}