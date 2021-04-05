import QtQuick 2.0

Rectangle {
    id: baseButton
    signal hit
    property string text: "Press"
    height: 30
    width: 110
    border.color: "black"
    border.width: 2
    color: "#556DB3"
    Text {
        id: buttonText
        text: baseButton.text
        anchors.centerIn: parent
        color: "White"
        font.pointSize: ui.text.medium
    }
    MouseArea{
        anchors.fill: parent
        onClicked: baseButton.hit()
    }
}
