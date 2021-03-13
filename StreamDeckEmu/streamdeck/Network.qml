import QtQuick 2.6
import QtQuick.Controls 2.2

Column {
    spacing: 10
    Text {
        width: parent.width
        wrapMode: Label.Wrap
        horizontalAlignment: Qt.AlignRight
        text: "Select the interface to be used:  "
        font.pointSize: 12
    }

    ComboBox {
        model: net.interfaces
        textRole: "display"
        anchors.right: parent.right
        width: parent.width / 3
        font.pointSize: 10
        onCurrentTextChanged: net.interfaceChanged(currentText)
    }
    Text {
        width: parent.width
        wrapMode: Label.Wrap
        horizontalAlignment: Qt.AlignRight
        text: "selected: " + net.selectedIP
        font.italic: true
        font.pointSize: 12
        anchors.rightMargin: 10
    }
}
