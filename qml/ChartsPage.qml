import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    color: "#F5F7FB"
    anchors.fill: parent

    Column {
        anchors.fill: parent
        spacing: 0

        // Header
        Rectangle {
            width: parent.width
            height: 80
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#151C35" }
                GradientStop { position: 1.0; color: "#49337B" }
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
                        text: "←"; color: "#543D6F"
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
                    width: 60; height: 60
                    fillMode: Image.PreserveAspectFit
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text {
                    text: "Spending insights"
                    color: "white"; font.pixelSize: 18; font.bold: true
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }

        // Scrollable Content
        ScrollView {
            id: chartScrollView  // Added an ID to get the true width
            width: parent.width
            height: parent.height - 80
            clip: true
            ScrollBar.vertical.policy: ScrollBar.AlwaysOff

            // CRITICAL: Forces the scroll area to match the exact screen width
            contentWidth: availableWidth

            Column {
                width: chartScrollView.availableWidth // Takes up the whole screen width safely
                spacing: 16
                topPadding: 16
                bottomPadding: 32

                // Spending by Category Card
                Rectangle {
                    width: parent.width - 20 // 10 pixels margin on left and 10 on right
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: col1.implicitHeight + 32
                    radius: 16
                    color: "white"
                    border.color: "#c8f0c8"; border.width: 1

                    Column {
                        id: col1
                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.margins: 16
                        spacing: 16

                        // Header row for chart
                        Item {
                            width: parent.width
                            height: 24
                            Text {
                                text: "Spending by Category"
                                color: "#1a1a1a"
                                font.pixelSize: 14
                                font.bold: true
                                anchors.left: parent.left
                                anchors.verticalCenter: parent.verticalCenter
                            }
                            Rectangle {
                                width: 70; height: 24; radius: 12
                                color: "#E9F9E5"
                                anchors.right: parent.right
                                Text {
                                    text: "Monthly"
                                    color: "#543D6F"; font.pixelSize: 11
                                    anchors.centerIn: parent
                                }
                            }
                        }
                        Text {
                            text: "Updates with your expense data"
                            color : "#bbb"; font.pixelSize: 11
                        }

                        // Category bars
                        Repeater {
                            model: ListModel {
                                ListElement { label: "Food"; clr: "#543D6F"; pct: 0.6 }
                                ListElement { label: "Transport"; clr: "#81C784"; pct: 0.4 }
                                ListElement { label: "Shopping";  clr: "#A5D6A7"; pct: 0.3 }
                                ListElement { label: "Bills"; clr: "#C8E6C9"; pct: 0.5 }
                                ListElement { label: "Other"; clr: "#E8F5E9"; pct: 0.15 }
                            }
                            Column {
                                width: parent.width
                                spacing: 6
                                Item {
                                    width: parent.width
                                    height: 16
                                    Text {
                                        text: model.label
                                        color: "#555"; font.pixelSize: 12
                                        anchors.left: parent.left
                                        anchors.verticalCenter: parent.verticalCenter
                                    }
                                    Text {
                                        text: "Rs 0"
                                        color: "#888"; font.pixelSize: 12
                                        anchors.right: parent.right
                                        anchors.verticalCenter: parent.verticalCenter
                                    }
                                }
                                Rectangle {
                                    width: parent.width
                                    height: 14; radius: 7
                                    color: "#F5FFF5"
                                    Rectangle {
                                        width: parent.width * model.pct
                                        height: 14; radius: 7
                                        color: model.clr
                                    }
                                }
                            }
                        }
                    }
                }

                // Statistic Section
                Rectangle {
                    width: parent.width - 20 // 10 pixels margin on left and 10 on right
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: col2.implicitHeight + 32
                    radius: 16; color: "white"
                    border.color: "#c8f0c8"; border.width: 1

                    Column {
                        id: col2
                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.margins: 16
                        spacing: 16
                        Text {
                            text: "Expense Distribution"
                            color: "#1a1a1a"; font.pixelSize: 14; font.bold: true
                        }
                        Rectangle {
                            width: parent.width
                            height: 24; radius: 12
                            color: "#E9F9E5"
                            clip: true
                            Row {
                                width: parent.width
                                height: 24
                                Rectangle { width: parent.width * 0.25; height: 24; color: "#543D6F" }
                                Rectangle { width: parent.width * 0.25; height: 24; color: "#81C784" }
                                Rectangle { width: parent.width * 0.25; height: 24; color: "#A5D6A7" }
                                Rectangle { width: parent.width * 0.25; height: 24; color: "#C8E6C9" }
                            }
                        }
                        Flow {
                            width: parent.width
                            spacing: 12
                            Repeater {
                                model: ListModel {
                                    ListElement { label: "Food"; dot: "#543D6F" }
                                    ListElement { label: "Transport"; dot: "#81C784" }
                                    ListElement { label: "Shopping";  dot: "#A5D6A7" }
                                    ListElement { label: "Bills";     dot: "#C8E6C9" }
                                }
                                Row {
                                    spacing: 6
                                    Rectangle {
                                        width: 12; height: 12; radius: 6
                                        color: model.dot
                                        anchors.verticalCenter: parent.verticalCenter
                                    }
                                    Text {
                                        text: model.label
                                        color: "#555"; font.pixelSize: 12
                                        anchors.verticalCenter: parent.verticalCenter
                                    }
                                }
                            }
                        }
                    }
                }

                // Statistics summary
                Rectangle {
                    width: parent.width - 20 // 10 pixels margin on left and 10 on right
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: col3.implicitHeight + 32
                    radius: 16; color: "white"
                    border.color: "#c8f0c8"; border.width: 1

                    Column {
                        id: col3
                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.margins: 16
                        spacing: 16
                        Text {
                            text: "Statistics"
                            color: "#1a1a1a"; font.pixelSize: 14; font.bold: true
                        }

                        Row {
                            width: parent.width
                            spacing: 10

                            Rectangle {
                                width: (parent.width - 10) / 2
                                height: 75; radius: 12
                                color: "#E9F9E5"
                                Column {
                                    anchors.centerIn: parent
                                    spacing: 4
                                    Text { text: "Highest Expense"; color: "#888"; font.pixelSize: 11; anchors.horizontalCenter: parent.horizontalCenter }
                                    Text { text: "Rs 0"; color: "#543D6F"; font.pixelSize: 22; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter }
                                    Text { text: "No data yet"; color: "#bbb"; font.pixelSize: 10; anchors.horizontalCenter: parent.horizontalCenter }
                                }
                            }
                            Rectangle {
                                width: (parent.width - 10) / 2
                                height: 75; radius: 12
                                color: "#E9F9E5"
                                Column {
                                    anchors.centerIn: parent
                                    spacing: 4
                                    Text { text: "Average Expense"; color: "#888"; font.pixelSize: 11; anchors.horizontalCenter: parent.horizontalCenter }
                                    Text { text: "Rs 0"; color: "#543D6F"; font.pixelSize: 22; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter }
                                    Text { text: "No data yet"; color: "#bbb"; font.pixelSize: 10; anchors.horizontalCenter: parent.horizontalCenter }
                                }
                            }
                        }
                    }
                }

                // Footer note
                Text {
                    text: "All charts auto-update\nonce you add expenses!"
                    color: "#aaa"; font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    topPadding: 10
                }
            }
        }
    }
}
