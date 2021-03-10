import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 1440
    height: 900
    title: qsTr("Emulator - Stream Deck")
    ListModel{
        id: pnlModel
        ListElement{ working: true;  action: "Req.\nSrcs."; activeState:0  ; arg: 100}
        ListElement{ working: false;  action: "Start"     ; activeState:1  ; arg: 0}
        ListElement{ working: false;  action: "Stop"      ; activeState:2  ; arg: 1}
        ListElement{ working: false;  action: "u/def"     ; activeState:5  ; arg: -1}
        ListElement{ working: false;  action: "u/def"     ; activeState:5  ; arg: -1}
        ListElement{ working: false;  action: "u/def"     ; activeState:5  ; arg: -1}
        ListElement{ working: false;  action: "u/def"     ; activeState:5  ; arg: -1}
        ListElement{ working: false;  action: "u/def"     ; activeState:5  ; arg: -1}
        ListElement{ working: false;  action: "u/def"     ; activeState:5  ; arg: -1}
        ListElement{ working: false;  action: "u/def"     ; activeState:5  ; arg: -1}
        ListElement{ working: false;  action: "u/def"     ; activeState:5  ; arg: -1}
        ListElement{ working: false;  action: "reset"     ; activeState:3  ; arg: 2}
    }
    Rectangle{
        border.color: "#4d4aad"
        color: "darkgray"
        anchors.centerIn: parent
        height: 850
        width: 800
        radius: 5
        Column{
            width: parent.width
            height: parent.height - 50
            anchors.bottom: parent.bottom

           Network{
               width: parent.width
           }

            Text {
                id: title
                color: "#ffffff"
                width: parent.width
                anchors.topMargin: 50
                text: qsTr("Stream Deck Emulator")
                font.family: "Arial"
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 40
            }
            SDPanel{
                size: 800
                mdl: pnlModel
            }
        }

    }
    Component.onCompleted: vm.start()


}

















