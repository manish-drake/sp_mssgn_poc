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
        }
        Text {
            id: hdr
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
            anchors.centerIn: parent
        }
        Text {
            id: fdr
            width: title.width
            color: "#5ac633"
            text: qsTr(home.footer)
            font.italic: true
            font.pointSize: 12
            horizontalAlignment: Text.AlignHCenter
            anchors.bottom: parent.bottom
        }
    }
}
