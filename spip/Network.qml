import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Window 2.2

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
    Button {
        text: "Manage Logs"
        onClicked: {
            log.refresh();
            popup.open()
        }
    }
    Popup {
        id: popup
        x: 50
        y: 50
        width: 200
        height: 400
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
        contentItem: Rectangle{
            border.width: 2
            border.color: "Gray"
            anchors.fill: parent

            Column{
                anchors.fill: parent
                spacing: 3
                ListView{
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: 2
                    anchors.rightMargin: 2

                    height: (5 * parent.height)/6
                    model: log.interfaces
                    delegate: Text {
                        text: display
                    }
                }
                Button{
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: 2
                    anchors.rightMargin: 2
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 2
                    height: (1 * parent.height)/6
                    text: "FTP & Clean"
                    onClicked: log.ftp()
                }
            }
        }
    }
}
