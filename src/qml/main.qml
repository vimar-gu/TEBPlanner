import QtQuick 2.4
import QtQuick.Window 2.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
import QtQuick.Layouts 1.0
import Client.Component 2.0 as Client

Window {
    id: root
    visible: true
    width: 1080
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
        }
    Column {
        Button {
            id: startButton
            text: qsTr("start")
            onClicked: {
                interaction.setVision()
            }
        }

        Label {
            id: enemyObs
            text: qsTr("Enemy Obstacles")
        }
    }
}
