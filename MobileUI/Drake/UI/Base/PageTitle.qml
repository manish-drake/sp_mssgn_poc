import QtQuick 2.0

Item {
    id: titleRoot
    property string text: "Title"
    width: parent.width
    Text {
        id: txt
        text: titleRoot.text
        font.pixelSize: ui.text.big
        anchors.centerIn: parent
    }
}
