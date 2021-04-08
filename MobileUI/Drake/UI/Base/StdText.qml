import QtQuick 2.0


Item{
    id: txtRoot
    property string text: ""
    Text {
        id: txt
        text: txtRoot.text
        font.pixelSize: ui.text.medium
        height: ui.text.medium + 5
    }
}
