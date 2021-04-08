import QtQuick 2.0


item{
    id: txtRoot
    property string str: ""
    Text {
        id: txt
        text: txtRoot.str
        font.pixelSize: ui.text.medium
        anchors.centerIn: parent
    }
}
