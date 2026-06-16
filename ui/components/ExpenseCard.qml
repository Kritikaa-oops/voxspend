import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: card
    property string expenseId: ""
    property string category: ""
    property string description: ""
    property string date: ""
    property real amount: 0
    property string currency: "NPR"
    signal removeRequested(string expenseId)

    color: "white"
    radius: 8
    border.color: "#e0e4ec"
    implicitHeight: 84

    RowLayout {
        anchors.fill: parent
        anchors.margins: 14
        spacing: 12

        Rectangle {
            Layout.preferredWidth: 42
            Layout.preferredHeight: 42
            radius: 8
            color: "#e3f2fd"

            Label {
                anchors.centerIn: parent
                text: card.category.length > 0 ? card.category.charAt(0).toUpperCase() : "?"
                color: "#1976d2"
                font.bold: true
                font.pixelSize: 18
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 4

            Label {
                text: card.description.length > 0 ? card.description : card.category
                color: "#1e2430"
                font.pixelSize: 16
                font.bold: true
                elide: Text.ElideRight
                Layout.fillWidth: true
            }

            Label {
                text: card.category + " - " + card.date
                color: "#6d7482"
                font.pixelSize: 13
                elide: Text.ElideRight
                Layout.fillWidth: true
            }
        }

        Label {
            text: card.currency + " " + card.amount.toFixed(2)
            color: "#1e2430"
            font.pixelSize: 15
            font.bold: true
        }

        Button {
            text: "Delete"
            onClicked: card.removeRequested(card.expenseId)
        }
    }
}
