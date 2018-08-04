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

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: {
            if (mouse.button === Qt.RightButton) {
                Qt.quit()
            }
            else if (mouse.button === Qt.LeftButton) {
                color = Qt.rgba((mouse.x % 255) / 255.0, (mouse.y % 255) / 255.0, 0.6, 1.0)
            }
        }
        onDoubleClicked: {
            color = "gray"
        }
    }

    Text {
        id: text1
        x: 246
        y: 196
        text: qsTr("Text")
        font.pixelSize: 30
        MouseArea {
            anchors.fill: parent
            drag.target: text1
        }
    }
}
