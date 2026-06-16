import QtQuick

Item {
    id: root
    property real value: 0
    property real maximum: 1
    property real ratio: maximum <= 0 ? 0 : Math.min(value / maximum, 1)

    implicitWidth: 320
    implicitHeight: 18

    Rectangle {
        anchors.fill: parent
        color: "#e6eaf0"
        radius: 6
    }

    Rectangle {
        width: parent.width * root.ratio
        height: parent.height
        radius: 6
        color: root.ratio >= 0.85 ? "#d32f2f" : root.ratio >= 0.5 ? "#f9a825" : "#2e7d32"
    }
}
