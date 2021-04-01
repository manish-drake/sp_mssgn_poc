import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Stack")

    Home{
        anchors.fill: parent
        header: vm.header
        body: vm.body
        footer: vm.footer
        isRecording: vm.isRecording
    }


}
