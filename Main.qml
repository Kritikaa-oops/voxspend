import QtQuick 2.15
import QtQuick.Controls 2.15

Window {
    id: appWindow
    width: 1300
    height: 750
    visible: true
    title: "VoxSpend"

    StackView {
        id: stackView
        anchors.fill: parent
        // Application launches directly into the Login flow
        initialItem: loginPage
    }

    // --- VIEW LAYER DEFINITIONS ---

    Component {
        id: loginPage
        LoginPage {}
    }

    Component {
        id: signupPage
        SignupPage {}
    }

    Component {
        id: homePage
        Rectangle {
            color: "#F5FFF5"

            Column {
                anchors.fill: parent
                spacing: 0

                // Header Block
                Rectangle {
                    width: parent.width
                    height: 250
                    gradient: Gradient {
                        GradientStop { position: 0.0; color: "#543D6F" }
                        GradientStop { position: 1.0; color: "#E9F9E5" }
                    }

                    Column {
                        anchors.centerIn: parent
                        spacing: 10

                        Image {
                            source: "logo.png"
                            width: 140
                            height: 140
                            fillMode: Image.PreserveAspectFit
                            anchors.horizontalCenter: parent.horizontalCenter
                        }

                        Text {
                            text: "Welcome to VoxSpend"
                            color: "white"
                            font.pixelSize: 18
                            font.bold: true
                            anchors.horizontalCenter: parent.horizontalCenter
                        }

                        Rectangle {
                            width: 250
                            height: 60
                            radius: 14
                            color: "#ffffff"
                            anchors.horizontalCenter: parent.horizontalCenter
                            opacity: 0.92

                            Column {
                                anchors.centerIn: parent
                                spacing: 2

                                Text {
                                    text: "This Month Spend"
                                    color: "#888"
                                    font.pixelSize: 11
                                    anchors.horizontalCenter: parent.horizontalCenter
                                }
                                Text {
                                    text: "Rs0.00"
                                    color: "#543D6F"
                                    font.pixelSize: 22
                                    font.bold: true
                                    anchors.horizontalCenter: parent.horizontalCenter
                                }
                            }
                        }
                    }
                }

                // Middle Content Block
                Rectangle {
                    width: parent.width
                    height: parent.height - 250 - 70
                    color: "#F5FFF5"

                    Column {
                        anchors.fill: parent
                        spacing: 0
                        topPadding: 16

                        Row {
                            width: parent.width - 32
                            anchors.horizontalCenter: parent.horizontalCenter

                            Text {
                                text: "Recent Transactions"
                                color: "#1a1a1a"
                                font.pixelSize: 15
                                font.bold: true
                            }

                            Item { width: parent.width - 200; height: 1 }

                            Text {
                                text: "See All"
                                color: "#543D6F"
                                font.pixelSize: 13
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: stackView.push("TransactionPage.qml")
                                }
                            }
                        }

                        Item { width: 1; height: 12 }

                        Text {
                            text: "No recent transactions"
                            color: "#aaa"
                            font.pixelSize: 13
                            anchors.horizontalCenter: parent.horizontalCenter
                            topPadding: 20
                        }
                    }
                }

                // Bottom Tab bar Setup
                Rectangle {
                    width: parent.width
                    height: 70
                    color: "white"
                    radius: 25

                    Row {
                        anchors.centerIn: parent
                        spacing: 0
                        width: parent.width

                        Repeater {
                            model: ListModel {
                                ListElement { icon: "🏠"; label: "Home";        page: "" }
                                ListElement { icon: "💳"; label: "Transaction"; page: "TransactionPage.qml" }
                                ListElement { icon: "📊"; label: "Analytics";   page: "ChartsPage.qml" }
                                ListElement { icon: "👤"; label: "Account";     page: "LogoutPage.qml" }
                            }

                            Item {
                                width: parent.width / 4
                                height: 70

                                Column {
                                    anchors.centerIn: parent
                                    spacing: 4

                                    Text {
                                        text: model.icon
                                        font.pixelSize: 20
                                        anchors.horizontalCenter: parent.horizontalCenter
                                    }
                                    Text {
                                        text: model.label
                                        color: model.page === "" ? "#543D6F" : "#999"
                                        font.pixelSize: 10
                                        anchors.horizontalCenter: parent.horizontalCenter
                                    }
                                }

                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        if (model.page !== "")
                                            stackView.push(model.page)
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // Floating Add Action Item
            Rectangle {
                width: 52
                height: 52
                radius: 26
                color: "#543D6F"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10

                Text {
                    text: "+"
                    color: "white"
                    font.pixelSize: 28
                    font.bold: true
                    anchors.centerIn: parent
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: stackView.push("AddExpense.qml")
                }
            }
        }
    }
}