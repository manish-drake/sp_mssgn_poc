import QtQuick 2.9
import QtQuick.Window 2.2


Window {
    visible: true
    width: 1440
    height: 900
    title: qsTr("Emulator - Stream Deck")
    ListModel{
        id: pnlModel
        ListElement{ working: true;  action: "Start"}
        ListElement{ working: true;  action: "Stop"}
        ListElement{ working: false;  action: "u/def"}
        ListElement{ working: false;  action: "u/def"}
        ListElement{ working: false;  action: "u/def"}
        ListElement{ working: false;  action: "u/def"}
        ListElement{ working: false;  action: "u/def"}
        ListElement{ working: false;  action: "u/def"}
        ListElement{ working: false;  action: "u/def"}
        ListElement{ working: false;  action: "u/def"}
        ListElement{ working: false;  action: "u/def"}
        ListElement{ working: false;  action: "u/def"}
    }
    Rectangle{
        border.color: "#4d4aad"
        color: "darkgray"
        anchors.centerIn: parent
        height: 800
        width: 800
        radius: 5
        Column{
            width: parent.width
            height: parent.height - 50
            anchors.bottom: parent.bottom
            Text {
                id: title
                color: "#ffffff"
                width: parent.width
                anchors.topMargin: 50
                text: qsTr("Stream Deck Emulator")
                font.family: "HoloLens MDL2 Assets"
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 50
            }
            SDPanel{
                size: 800
                mdl: pnlModel
            }
        }

    }


}

















