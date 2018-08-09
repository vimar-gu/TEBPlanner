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

    Row {
        Client.Field {
            id: map
            x: 10
            width: 720
            height: 720
            Image {
                id: obs1
                objectName: "obs1"
                x: 100
                y: 100
                width: 30
                height: 30
                source: "../../resource/1.png"
                MouseArea {
                    anchors.fill: parent
                    drag.target: obs1
                }
                function x() {
                    return obs1.x
                }
            }
        }
        Column {
            Label {
                id: enemyObs
                text: qsTr("Enemy Obstacles")
            }

            RadioButton {
                id: radioButton
                width: 30
                height: 30
                activeFocusOnPress: false
                checked: false
                onCheckedChanged: {
                    if (checked === true) {
                        obs1.visible = true
                    }
                    else {
                        obs1.visible = false
                    }
                }

                Image {
                    id: img1
                    width: 30
                    height: 30
                    source: "../../resource/1.png"
                }
            }


        }
    }
}
