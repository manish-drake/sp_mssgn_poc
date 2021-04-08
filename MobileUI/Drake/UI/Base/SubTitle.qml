import QtQuick 2.0

Rectangle {
    id: subTitleRoot
    property string sideIcon: ""
    property string text: "Title"
    property var stackRoot: null

    width: parent.width
    color: "#e2d9d9"
    IconAction{
        id: sideImage
        icon: subTitleRoot.sideIcon
        anchors.left: parent.left
        height: 30; width: 30
        onAction: stackRoot.pop()
    }
    Text {
        id: txt
        text: subTitleRoot.text
        font.pixelSize: ui.text.big
        anchors.left: sideImage.right
        anchors.leftMargin: 10

    }
}
