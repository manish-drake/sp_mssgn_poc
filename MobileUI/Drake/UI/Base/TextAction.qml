import QtQuick 2.0

Item {
    id: textButtonRoot
    signal action
    property string text: "TEXT"
    height: ui.text.big +5
    Text{
        text: textButtonRoot.text
        font.pixelSize: ui.text.big
    }
    MouseArea{
        anchors.fill: parent
        onClicked: textButtonRoot.action()
    }
}
