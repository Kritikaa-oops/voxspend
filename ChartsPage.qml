import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
color: "#F5FFF5"
anchors.fill: parent
Column {
anchors.fill: parent
spacing: 0
//header
Rectangle {
width: parent.width
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
Image {
source: "logo.png"
width: 38; height: 38
fillMode: Image.PreserveAspectFit
anchors.verticalCenter: parent.verticalCenter
}
Text {
text: "Charts & Statistics"
color: "white"; font.pixelSize: 18; font.bold: true
anchors.verticalCenter: parent.verticalCenter
}
}
}
ScrollView {
width: parent.width
height: parent.height - 80
clip: true
Column {
width: parent.width * 0.9
anchors.horizontalCenter: parent.horizontalCenter
spacing: 14
topPadding: 16
bottomPadding: 16
Rectangle {
width: parent.width * 0.9
height: 290
radius: 16
color: "white"
anchors.horizontalCenter: parent.horizontalCenter
border.color: "#c8f0c8"; border.width: 1
Column {
anchors.fill: parent
spacing: 12
padding: 16
//header row for chart
Row {
width: parent.width - 32
Text {
text: "Spending by Category"
color: "#1a1a1a"
font.pixelSize: 14
font.bold: true
}
Item { width: parent.width - 210; height: 1 }
Rectangle {
width: 70; height: 24; radius: 12
color: "#E9F9E5"
Text {
text: "Monthly"
color: "#4CAF50"; font.pixelSize: 11
anchors.centerIn: parent
}
}
}
Text {
text: "Updates with your expense data"
color: "#bbb"; font.pixelSize: 11
}
//category bar
Repeater {
model: ListModel {
ListElement { label: "Food";clr: "#4CAF50"; pct: 0.0 }
ListElement { label: "Transport"; clr: "#81C784"; pct: 0.0 }
ListElement { label: "Shopping";  clr: "#A5D6A7"; pct: 0.0 }
ListElement { label: "Bills";     clr: "#C8E6C9"; pct: 0.0 }
ListElement { label: "Other";     clr: "#E8F5E9"; pct: 0.0 }
}
Column {
width: parent.width - 32
spacing: 3
Row {
width: parent.width
Text {
text: model.label
color: "#555"; font.pixelSize: 11
}
Item { width: parent.width - 60; height: 1 }
Text {
text: "$0"
color: "#888"; font.pixelSize: 11
}
}
Rectangle {
width: parent.width
height: 18; radius: 9
color: "#F5FFF5"
Rectangle {
width: parent.width * model.pct
height: 18; radius: 9
color: model.clr
}
}
}
}
}
}
//statistic section
Rectangle {
width: parent.width - 28
height: 140
radius: 16; color: "white"
anchors.horizontalCenter: parent.horizontalCenter
border.color: "#c8f0c8"; border.width: 1
Column {
anchors.fill: parent
spacing: 12; padding: 16
Text {
text: "Expense Distribution"
color: "#1a1a1a"; font.pixelSize: 14; font.bold: true
}
Rectangle {
width: parent.width - 32
height: 24; radius: 12
color: "#E9F9E5"
clip: true
Row {
width: parent.width
height: 24
Rectangle {
width: parent.width * 0.25
height: 24; color: "#4CAF50"
}
Rectangle {
width: parent.width * 0.25
height: 24; color: "#81C784"
}
Rectangle {
width: parent.width * 0.25
height: 24; color: "#A5D6A7"
}
Rectangle {
width: parent.width * 0.25
height: 24; color: "#C8E6C9"
}
}
}
Flow {
width: parent.width - 32
spacing: 12
Repeater {
model: ListModel {
ListElement { label: "Food";dot: "#4CAF50" }
ListElement { label: "Transport"; dot: "#81C784" }
ListElement { label: "Shopping";  dot: "#A5D6A7" }
ListElement { label: "Bills";     dot: "#C8E6C9" }
}
Row {
spacing: 5
Rectangle {
width: 10; height: 10; radius: 5
color: model.dot
anchors.verticalCenter: parent.verticalCenter
}
Text {
text: model.label
color: "#555"; font.pixelSize: 11
anchors.verticalCenter: parent.verticalCenter
}
}
}
}
}
}
Rectangle {
width: parent.width - 28
height: 130
radius: 16; color: "white"
anchors.horizontalCenter: parent.horizontalCenter
border.color: "#c8f0c8"; border.width: 1
Column {
anchors.fill: parent
spacing: 10; padding: 16
Text {
text: "Statistics"
color: "#1a1a1a"; font.pixelSize: 14; font.bold: true
}
Row {
width: parent.width - 32
spacing: 10
Rectangle {
width: (parent.width - 10) / 2
height: 65; radius: 12
color: "#E9F9E5"
Column {
anchors.centerIn: parent
spacing: 3
Text {
text: "Highest Expense"
color: "#888"; font.pixelSize: 10
anchors.horizontalCenter: parent.horizontalCenter
}
Text {
text: "$0"
color: "#4CAF50"
font.pixelSize: 20; font.bold: true
anchors.horizontalCenter: parent.horizontalCenter
}
Text {
text: "No data yet"
color: "#bbb"; font.pixelSize: 9
anchors.horizontalCenter: parent.horizontalCenter
}
}
}
Rectangle {
width: (parent.width - 10) / 2
height: 65; radius: 12
color: "#E9F9E5"
Column {
anchors.centerIn: parent
spacing: 3
Text {
text: "Average Expense"
color: "#888"; font.pixelSize: 10
anchors.horizontalCenter: parent.horizontalCenter
}
Text {
text: "$0"
color: "#4CAF50"
font.pixelSize: 20; font.bold: true
anchors.horizontalCenter: parent.horizontalCenter
}
Text {
text: "No data yet"
color: "#bbb"; font.pixelSize: 9
anchors.horizontalCenter: parent.horizontalCenter
}
}
}
}
}
}
//footer note
Text {
text: "All charts auto-update\nonce you add expenses!"
color: "#aaa"; font.pixelSize: 12
horizontalAlignment: Text.AlignHCenter
anchors.horizontalCenter: parent.horizontalCenter
}
}
}
}
}