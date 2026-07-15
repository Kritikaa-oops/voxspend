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
color: "#543D6F"
gradient: Gradient {
GradientStop { position: 0.0; color: "#543D6F" }
GradientStop { position: 1.0; color: "#E9F9E5" }
}
//page title
Text {
text: "Summary"
color: "white"
font.pixelSize: 24
font.bold: true
anchors.centerIn: parent
}
Rectangle {
width: 36; height: 36; radius: 18
color: "white"; opacity: 0.85
anchors.left: parent.left
anchors.leftMargin: 16
anchors.verticalCenter: parent.verticalCenter
Text {
text: "←"
color: "#543D6F"
font.pixelSize: 18; font.bold: true
anchors.centerIn: parent
}
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
color: "#7B5EA1"
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
topPadding: 20
anchors.horizontalCenter: parent.horizontalCenter
}
Grid {
columns: 2
spacing: 30
anchors.horizontalCenter: parent.horizontalCenter
Rectangle {
width: 200
height: 100
radius: 12
property bool hovered: false
color: hovered ? "#3D2B54" : "#543D6F"
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
width: 200
height: 100
radius: 12
property bool hovered: false
color: hovered ? "#3D2B54" : "#543D6F"
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
width: 200
height: 100
radius: 12
property bool hovered: false
color: hovered ? "#3D2B54" : "#543D6F"
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
width: 200
height: 100
radius: 12
property bool hovered: false
color: hovered ? "#3D2B54" : "#543D6F"
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
//empty stage message
Text {
text: "No data yet. Add expenses to see summary!"
color: "gray"
font.pixelSize: 14
anchors.horizontalCenter: parent.horizontalCenter
}
}
}
}