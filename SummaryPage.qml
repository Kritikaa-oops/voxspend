import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
anchors.fill: parent
Rectangle {
anchors.fill: parent
color: "#F5FFF5"
Column {
anchors.fill: parent
spacing: 20
padding: 20
// top header section
Rectangle {
width: parent.width
height: 80
color: "#4CAF50"
//page title
Text {
text: "Summary"
color: "white"
font.pixelSize: 24
font.bold: true
anchors.centerIn: parent
}
Text {
text: "←"; color: "#4CAF50"
font.pixelSize: 18; font.bold: true
anchors.left:  parent
}
//navigation bar
MouseArea {
anchors.fill: parent
onClicked: stackView.pop()
}
}
Rectangle {
width: parent.width * 0.85
height: 110
radius: 16
color: "#66BB6A"
anchors.horizontalCenter: parent.horizontalCenter
Column {
anchors.centerIn: parent
spacing: 6
Text {
text: "Total Spent This Month"
color: "white"
font.pixelSize: 14
}
//amount display
Text {
text: "Rs0.00"
color: "white"
font.pixelSize: 32
font.bold: true
}
}
}
Text {
text: "By Category"
font.pixelSize: 18
font.bold: true
anchors.horizontalCenter: parent.horizontalCenter
}
Grid {
columns: 2
spacing: 20
anchors.horizontalCenter: parent.horizontalCenter
Rectangle {
width: 150
height: 80
radius: 12
property bool hovered: false
color: hovered ? "#2E7D32" : "#4CAF50"
Text {
text: "Food"
color: "white"
anchors.centerIn: parent
}
MouseArea {
anchors.fill: parent
hoverEnabled: true
onEntered: parent.hovered = true
onExited: parent.hovered = false
onClicked: console.log("Food clicked")
}
Behavior on color {
ColorAnimation { duration: 150 }
}
}
Rectangle {
width: 150
height: 80
radius: 12
property bool hovered: false
color: hovered ? "#2E7D32" : "#4CAF50"
Text {
text: "Transport"
color: "white"
anchors.centerIn: parent
}
MouseArea {
anchors.fill: parent
hoverEnabled: true
onEntered: parent.hovered = true
onExited: parent.hovered = false
onClicked: console.log("Transport clicked")
}
Behavior on color {
ColorAnimation { duration: 150 }
}
}
Rectangle {
width: 150
height: 80
radius: 12
property bool hovered: false
color: hovered ? "#2E7D32" : "#4CAF50"
Text {
text: "Shopping"
color: "white"
anchors.centerIn: parent
}
MouseArea {
anchors.fill: parent
hoverEnabled: true
onEntered: parent.hovered = true
onExited: parent.hovered = false
onClicked: console.log("Shopping clicked")
}
Behavior on color {
ColorAnimation { duration: 150 }
}
}
Rectangle {
width: 150
height: 80
radius: 12
property bool hovered: false
color: hovered ? "#2E7D32" : "#4CAF50"
Text {
text: "Bills"
color: "white"
anchors.centerIn: parent
}
MouseArea {
anchors.fill: parent
hoverEnabled: true
onEntered: parent.hovered = true
onExited: parent.hovered = false
onClicked: console.log("Bills clicked")
}
Behavior on color {
ColorAnimation { duration: 150 }
}
}
}
//empty stagr message
Text {
text: "No data yet. Add expenses to see summary!"
color: "gray"
font.pixelSize: 14
anchors.horizontalCenter: parent.horizontalCenter
}
}
}
}
