import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import Drake.UI.Complex 1.0 as DC
import Drake.UI.Base 1.0 as DB

Window {
    visible: true
    width: ui.width
    height: ui.height
    title: qsTr("Sports PIP - Capture")
    StackView{
        id: root
        anchors.fill: parent
        initialItem: "qrc:/Home.qml"
    }
}
