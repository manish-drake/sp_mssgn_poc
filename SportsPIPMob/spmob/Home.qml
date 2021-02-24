import QtQuick 2.9

Item {
    id: home
    anchors.fill: parent
    property string header: ""
    property string body: ""
    property string footer: "awaiting request.."
    Column{
        anchors.fill: parent
        Text{
            id:title
            width: parent.width
            text: "SPORTS PIP"
            font.family: "DejaVu Sans"
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 16
            height: 50
        }
        Text {
            id: hdr
            anchors.topMargin: 0
            width: title.width
            color: "#5ac633"
            text: qsTr(home.header)
            font.italic: true
            font.pointSize: 12
            horizontalAlignment: Text.AlignHCenter
        }
        Text {
            id: bd
            width: title.width
            color: "#5ac633"
            text: qsTr(home.body)
            font.italic: true
            font.pointSize: 12
            horizontalAlignment: Text.AlignHCenter
            anchors.topMargin:  parent.height/2
        }
        Text {
            id: fdr
            width: title.width
            color: "#5ac633"
            text: qsTr(home.footer)
            font.italic: true
            font.pointSize: 12
            horizontalAlignment: Text.AlignHCenter
            anchors.bottomMargin: 0
        }
    }
}
