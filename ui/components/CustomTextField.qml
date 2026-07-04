import QtQuick
import QtQuick.Controls

TextField {
    id: field
    property bool numeric: false

    selectByMouse: true
    font.pixelSize: 15
    padding: 12
    validator: numeric ? numberValidator : null

    background: Rectangle {
        color: "white"
        border.color: field.activeFocus ? "#1976d2" : "#d7dce5"
        radius: 6
    }

    DoubleValidator {
        id: numberValidator
        bottom: 0
        decimals: 2
        notation: DoubleValidator.StandardNotation
    }
}
