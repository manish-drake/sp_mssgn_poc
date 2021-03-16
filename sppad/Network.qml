import QtQuick 2.6
import QtQuick.Controls 2.2

Column {
    Label {
        width: parent.width
        wrapMode: Label.Wrap
        horizontalAlignment: Qt.AlignRight
        text: "Select the interface to be used:  "
    }

    ComboBox {
        model: net.interfaces
        textRole: "display"
        anchors.right: parent.right
        width: parent.width / 3
        onCurrentTextChanged: net.interfaceChanged(currentText)
    }
    Label {
        width: parent.width
        wrapMode: Label.Wrap
        horizontalAlignment: Qt.AlignRight
        text: "selected: " + net.selectedIP
        anchors.rightMargin: 10
    }
}
