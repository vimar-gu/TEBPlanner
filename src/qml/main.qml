import QtQuick 2.4
import QtQuick.Window 2.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
import QtQuick.Layouts 1.0
import Client.Component 2.0 as Client

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Row {
        Client.Field {
            id: map
        }
    }
}
