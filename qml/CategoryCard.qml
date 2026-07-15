import QtQuick 2.15
Rectangle {
width: 150
height: 75
radius: 14
color: "#E9F9E5"
border.color: "#a5d6a7"
border.width: 1
property string categoryName: ""
property string amount: ""
Column {
anchors.centerIn: parent
spacing: 5
// category name display
Text {
text: categoryName !== "" ? categoryName : "—"
color: "#543D6F"
font.pixelSize: 13
font.bold: true
anchors.horizontalCenter: parent.horizontalCenter
}
// Amount display with Rs prefix
Text {
text: amount !== "" ? "Rs" + amount : "Rs0"
color: "#543D6F"
font.pixelSize: 18
font.bold: true
anchors.horizontalCenter: parent.horizontalCenter
}
}
}