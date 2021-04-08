import QtQuick 2.0

Item {
    id: imgRoot
    property string icon: ""
    property string caption: ""
    signal hit;
    Image {
        id: img
        fillMode: Image.PreserveAspectFit
        source: imgRoot.icon
        anchors.fill: parent
    }
    Text {
        id: txtCaption
        text: imgRoot.caption
        anchors.top: img.bottom
        anchors.topMargin: 5
        anchors.horizontalCenter: img.horizontalCenter
        font.pixelSize: ui.text.small
    }
    MouseArea{
        width: parent.width + 10
        height: parent.height + 10
        anchors.centerIn: parent
        onClicked: imgRoot.hit()
    }
}
