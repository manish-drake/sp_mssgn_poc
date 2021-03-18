import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 1440
    height: 900
    title: qsTr("Emulator - Stream Deck")
    ListModel{
        id: pnlModel
        ListElement{ working: true;  action: "Ident.\nSrcs."; activeState:0  ; arg: 0}
        ListElement{ working: true;  action: "Start"     ; activeState:1  ; arg: 1}
        ListElement{ working: true;  action: "Stop"      ; activeState:2  ; arg: 2}
        ListElement{ working: false;  action: "u/def"     ; activeState:5  ; arg: -1}
        ListElement{ working: false;  action: "u/def"     ; activeState:5  ; arg: -1}
        ListElement{ working: false;  action: "u/def"     ; activeState:5  ; arg: -1}
        ListElement{ working: false;  action: "u/def"     ; activeState:5  ; arg: -1}
        ListElement{ working: false;  action: "u/def"     ; activeState:5  ; arg: -1}
    }
    Item {
        id: cont
        anchors.fill: parent
        Rectangle{
            id:header
            color: "lightgray"
            width: 800
            height: 150
            radius: 5
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
            Network{
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 20
                width: parent.width
            }
        }
        Rectangle{
            id:deck
            border.color: "#4d4aad"
            color: "darkgray"
            anchors.top: header.bottom
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
            height: 550
            width: 800
            radius: 5
            Column{
                width: parent.width
                height: parent.height - 50
                anchors.bottom: parent.bottom


                Text {
                    id: title
                    color: "#8380cf"
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
        Rectangle{
            color: "white"
            width: 800
            height: 100
            radius: 5
            anchors.topMargin: 20
            anchors.top: deck.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            Column{
                spacing: 2
                anchors.fill: parent
                Rectangle{
                    color: "#958b8b"
                    border.color: "#000000"
                    width: parent.width
                    height: 50
                    Text {
                        id: ident
                        color: "#ffffff"
                        text: vm.ident
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 10
                    }
                }
                Rectangle{
                    color: "#eaecad"
                    border.color: "#000000"
                    width: parent.width
                    height: 50
                    Text {
                        id: sts
                        color: "#000000"
                        text: vm.status
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 10
                    }
                }
            }
        }
    }

    Component.onCompleted: vm.start()


}

















