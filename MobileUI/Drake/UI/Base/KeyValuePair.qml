import QtQuick 2.0

Item{
    id:kvpRoot
    property string label: ""
    property string text: ""
    width: parent.width
    height: 30

    Text{
        text: kvpRoot.label
        anchors.top: parent.top
        anchors.left: parent.left
    }
    Text{
        text: kvpRoot.text
        horizontalAlignment: Text.AlignRight
        anchors.top: parent.top
        anchors.right: parent.right
    }
}
