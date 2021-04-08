import QtQuick.Controls 2.2
import QtQuick 2.7

Rectangle{
    border.color: "black"
    border.width: 2
    color: "#556DB3"
    height: 30
    width: 110
    Switch {
        id: baseButton
        signal action
        anchors.fill: parent
        Text {
            id: buttonText
            text: baseButton.text
            anchors.centerIn: parent
            color: "White"
            font.pointSize: ui.text.medium
        }
    }
}
