import QtQuick 2.4
import QtQuick.Window 2.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
import QtQuick.Layouts 1.0
import Client.Component 2.0 as Client

Window {
    id: root
    visible: true
    width: 960
    height: 720
    title: qsTr("Hello World")

    Client.Interaction{ id : interaction }

    Row {
        Client.Field {
            id: map
            x: 10
            width: 720
            height: 720
        }
        Column {
            Button {
                id: startButton
                width: 240
                height: 80
                Text {
                    x: 90
                    y: 25
                    text: qsTr("start")
                    font.family: "Courier"
                    font.pointSize: 14
                }
                onClicked: {
                    interaction.setVision()
                }
            }

            Button {
                id: obstacles
                width: 240
                height: 80
                Text {
                    x: 32
                    y: 28
                    text: qsTr("add enemy obstacle")
                    font.family: "Courier"
                    font.pointSize: 12
                }
                onClicked: {
                    interaction.addObstacle()
                }
            }

            Row {
                Button {
                    id: useRRT
                    width: 120
                    height: 80
                    Text {
                        x: 25
                        y: 28
                        text: qsTr("use RRT")
                        font.family: "Courier"
                        font.pointSize: 12
                    }
                    onClicked: {
                        interaction.setTrajectoryMethod(0)
                    }
                }

                Button {
                    id: useTEB
                    width: 120
                    height: 80
                    Text {
                        x: 25
                        y: 28
                        text: qsTr("use TEB")
                        font.family: "Courier"
                        font.pointSize: 12
                    }
                    onClicked: {
                        interaction.setTrajectoryMethod(1)
                    }
                }
            }
        }
    }
}
