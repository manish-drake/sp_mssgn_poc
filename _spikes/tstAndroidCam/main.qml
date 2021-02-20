import QtQuick 2.9
import QtQuick.Window 2.2
import QtMultimedia 5.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    CamBox{
        anchors.fill: parent
    }
    Component.onCompleted: vm.start()
}
