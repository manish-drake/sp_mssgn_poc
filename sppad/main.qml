import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick 2.7
import QtQuick.Controls 2.0

Window {
    width: 1024
    height: 768
    visible: true
    title: qsTr("Sportspip")


    //    Settings{}
    //    Preview_download{}
    //    Metadata{}
    //    Preview_stream{}

    Rectangle{
        color: "white"
        border.color: "black"
        anchors.fill: parent
//        height: 400
//        width: 600
        Loader{
            id: ml
            anchors.fill: parent
            visible: status != Loader.Null
            source: "Medialist.qml"
        }

    }
    Component.onCompleted: _tr.start()
}
