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
            width: 720
            height: 720
            Text {
                id: tmpText
                text: qsTr("text")
                font.pointSize: 14
                x: 20
                y: 20
                MouseArea {
                    anchors.fill: parent
                    drag.target: tmpText
                }
            }
        }
        Column {
            RadioButton {
                id: radioButton
                text: qsTr("1")
                activeFocusOnPress: false
                checked: false
                onCheckedChanged: {
                    if (checked === true) {
                        tmpText.visible = true
                    }
                    else {
                        tmpText.visible = false
                    }
                }
            }
        }
    }
}
