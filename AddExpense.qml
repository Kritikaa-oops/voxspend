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
color: "white"
opacity: 0.85
Text {
text: "←"
color: "#4CAF50"
font.pixelSize: 18
font.bold: true
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
width: 38; height: 38
fillMode: Image.PreserveAspectFit
anchors.verticalCenter: parent.verticalCenter
}
Text {
text: "Add Expense"
color: "white"
font.pixelSize: 18
font.bold: true
anchors.verticalCenter: parent.verticalCenter
}
}
}
ScrollView {
width: parent.width
height: parent.height - 80
clip: true
Column {
width: parent.width * 0.88
anchors.horizontalCenter: parent.horizontalCenter
spacing: 14
topPadding: 22
bottomPadding: 22
Text { text: "Expense Title"; color: "#555"; font.pixelSize: 12 }
Rectangle {
width: parent.width;
anchors.horizontalCenter: parent.horizontalCenter
height: 48
radius: 12; color: "white"
border.color: "#c8f0c8"; border.width: 1
TextField {
id: titleField
anchors.fill: parent
anchors.margins: 2
placeholderText: "e.g. Groceries"
placeholderTextColor: "#bbb"
color: "#222"
background: Rectangle { color: "transparent" }
leftPadding: 14
}
}
Text { text: "Amount"; color: "#555"; font.pixelSize: 12 }
Rectangle {
width: parent.width;
anchors.horizontalCenter: parent.horizontalCenter
height: 48
radius: 12; color: "white"
border.color: "#c8f0c8"; border.width: 1
Row {
anchors.verticalCenter: parent.verticalCenter
anchors.left: parent.left
anchors.leftMargin: 14
spacing: 4
Text { text: "Rs"; color: "#4CAF50"; font.pixelSize: 16; font.bold: true }
TextField {
id: amountField
width: parent.parent.width - 50
height: 44
placeholderText: "0.00"
placeholderTextColor: "#bbb"
color: "#222"
inputMethodHints: Qt.ImhFormattedNumbersOnly
validator: DoubleValidator { bottom: 0 }
background: Rectangle { color: "transparent" }
}
}
}
Text { text: "Category"; color: "#555"; font.pixelSize: 12 }
Rectangle {
width: parent.width;
anchors.horizontalCenter: parent.horizontalCenter
height: 48
radius: 12; color: "white"
border.color: "#c8f0c8"; border.width: 1
// category field
ComboBox {
id: categoryBox
anchors.fill: parent
model: ["Select Category", "Food", "Transport","Shopping", "Bills", "Other"]
background: Rectangle { color: "transparent" }
contentItem: Text {
text: categoryBox.displayText
color: categoryBox.currentIndex === 0 ? "#bbb" : "#222"
font.pixelSize: 14
leftPadding: 14
verticalAlignment: Text.AlignVCenter
}
}
}
Text { text: "Date"; color: "#555"; font.pixelSize: 12 }
Rectangle {
width: parent.width;
anchors.horizontalCenter: parent.horizontalCenter
height: 48
radius: 12; color: "white"
border.color: "#c8f0c8"; border.width: 1
Row {
anchors.verticalCenter: parent.verticalCenter
anchors.left: parent.left
anchors.leftMargin: 14
spacing: 10
Text { text: "📅"; font.pixelSize: 16 }
// date field
Text {
id: dateDisplay
text: Qt.formatDate(new Date(), "yyyy-MM-dd")
color: "#222"; font.pixelSize: 14
}
}
MouseArea {
anchors.fill: parent
onClicked: datePicker.open()
}
}
Dialog {
id: datePicker
title: "Select Date"
width: parent.width
modal: true
background: Rectangle {
color: "white"; radius: 14
border.color: "#c8f0c8"; border.width: 1
}
contentItem: Column {
spacing: 12
padding: 16
Text {
text: "Pick a date"
color: "#333"; font.pixelSize: 14; font.bold: true
}
Row {
spacing: 8
ComboBox {
id: yearBox
width: 88
model: ["2024","2025","2026","2027"]
currentIndex: 2
background: Rectangle {
color: "#E9F9E5"; radius: 8
}
contentItem: Text {
text: yearBox.displayText
color: "#333"; font.pixelSize: 13
horizontalAlignment: Text.AlignHCenter
verticalAlignment: Text.AlignVCenter
}
}
ComboBox {
id: monthBox
width: 105
model: ["Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"]
currentIndex: new Date().getMonth()
background: Rectangle {
color: "#E9F9E5"; radius: 8
}
contentItem: Text {
text: monthBox.displayText
color: "#333"; font.pixelSize: 13
horizontalAlignment: Text.AlignHCenter
verticalAlignment: Text.AlignVCenter
}
}
ComboBox {
id: dayBox
width: 68
model: Array.from({length:31},
(_,i) => String(i+1).padStart(2,'0'))
currentIndex: new Date().getDate() - 1
background: Rectangle {
color: "#E9F9E5"; radius: 8
}
contentItem: Text {
text: dayBox.displayText
color: "#333"; font.pixelSize: 13
horizontalAlignment: Text.AlignHCenter
verticalAlignment: Text.AlignVCenter
}
}
}
Button {
text: "Confirm"
width: parent.width - 32
background: Rectangle {
color: "#4CAF50"; radius: 10
}
contentItem: Text {
text: "Confirm"
color: "white"; font.pixelSize: 14; font.bold: true
horizontalAlignment: Text.AlignHCenter
verticalAlignment: Text.AlignVCenter
}
onClicked: {
var m = ["01","02","03","04","05","06", "07","08","09","10","11","12"]
dateDisplay.text = yearBox.currentText + "-" +m[monthBox.currentIndex] + "-" + dayBox.currentText
datePicker.close()
}
}
}
}
Text { text: "Note (optional)"; color: "#555"; font.pixelSize: 12 }
Rectangle {
width: parent.width;
anchors.horizontalCenter: parent.horizontalCenter
height: 48
radius: 12; color: "white"
border.color: "#c8f0c8"; border.width: 1
TextField {
id: noteField
anchors.fill: parent
anchors.margins: 2
placeholderText: "Add a note..."
placeholderTextColor: "#bbb"
color: "#222"
background: Rectangle { color: "transparent" }
leftPadding: 14
}
}
Text {
id: errorText
text: ""; color: "#e53935"
font.pixelSize: 12
visible: text !== ""
}
Rectangle {
width: parent.width;
anchors.horizontalCenter: parent.horizontalCenter
height: 50
radius: 14
color: "#4CAF50"
Text {
text: "Save Expense"
color: "white"; font.pixelSize: 15; font.bold: true
anchors.centerIn: parent
}
MouseArea {
anchors.fill: parent
onClicked: {
if (titleField.text === "")
errorText.text = "Please enter a title"
else if (amountField.text === "")
errorText.text = "Please enter an amount"
else if (categoryBox.currentIndex === 0)
errorText.text = "Please select a category"
else {
errorText.text = ""
console.log("Saved:", titleField.text,
amountField.text, categoryBox.currentText,
dateDisplay.text, noteField.text)
titleField.text = ""
amountField.text = ""
categoryBox.currentIndex = 0
dateDisplay.text = Qt.formatDate(new Date(), "yyyy-MM-dd")
noteField.text = ""
}
}
}
}
Rectangle {
width: parent.width;
anchors.horizontalCenter: parent.horizontalCenter
height: 48
radius: 14
color: "#E9F9E5"
border.color: "#4CAF50"; border.width: 1
Text {
text: "Clear"
color: "#4CAF50"; font.pixelSize: 14; font.bold: true
anchors.centerIn: parent
}
// resets all input fields
MouseArea {
anchors.fill: parent
onClicked: {
titleField.text = ""
amountField.text = ""
categoryBox.currentIndex = 0
dateDisplay.text = Qt.formatDate(
new Date(), "yyyy-MM-dd")
noteField.text = ""
errorText.text = ""
}
}
}
}
}
}
}