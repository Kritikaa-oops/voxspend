import QtQuick 2.15

Item {
    id: root
    property string name: "home"
    property color strokeColor: "#8B96AD"
    width: 24; height: 24
    Canvas {
        anchors.fill: parent
        onPaint: {
            var c = getContext("2d"); c.reset(); c.strokeStyle = root.strokeColor
            c.lineWidth = 1.9; c.lineCap = "round"; c.lineJoin = "round"
            if (root.name === "home") { c.beginPath(); c.moveTo(3,11); c.lineTo(12,3); c.lineTo(21,11); c.moveTo(5.5,10); c.lineTo(5.5,20); c.lineTo(18.5,20); c.lineTo(18.5,10); c.moveTo(10,20); c.lineTo(10,14); c.lineTo(14,14); c.lineTo(14,20); c.stroke() }
            else if (root.name === "activity") { c.beginPath(); c.rect(3,4,18,16); c.moveTo(7,15); c.lineTo(10,12); c.lineTo(13,14); c.lineTo(18,8); c.stroke() }
            else if (root.name === "chart") { c.beginPath(); c.moveTo(4,20); c.lineTo(4,4); c.moveTo(4,20); c.lineTo(21,20); c.moveTo(8,16); c.lineTo(11,12); c.lineTo(14,14); c.lineTo(19,7); c.stroke() }
            else if (root.name === "user") { c.beginPath(); c.arc(12,8,3.5,0,Math.PI*2); c.moveTo(5,21); c.bezierCurveTo(5,16,8,14,12,14); c.bezierCurveTo(16,14,19,16,19,21); c.stroke() }
            else if (root.name === "plus") { c.beginPath(); c.moveTo(12,5); c.lineTo(12,19); c.moveTo(5,12); c.lineTo(19,12); c.stroke() }
        }
    }
}
