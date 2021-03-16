import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Item {
    id:pd
    anchors.fill: parent
    Column{
        Rectangle{
            color: "#1E90FF"
            height: pd.height/12
            width: pd.width
            Text{
                text:"Preview (Download)"
                font.family: "MS Shell Dlg 2"
                font.bold: true
                x:30
                y:10
                horizontalAlignment: Text.AlignHCenter
                color: "#ffffff"
                font.pointSize: 12
            }
            Image {
                source:  "./image/left-arrow.png"
                x:7
                y:10
                height: 15
                width: 15
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        ml.source = "Medialist.qml"
                    }
                }
            }

        }
        Rectangle{
            color: "#ffffff"
            height: 11*pd.height/12
            width: pd.width

            GridLayout{
                id: grid
                anchors.fill: parent
                anchors.topMargin: 50
                anchors.leftMargin: 80
                anchors.bottomMargin: 100
                Text {
                    Layout.row:0
                    Layout.column: 0
                    font.pixelSize: 14
                    text: "Media File:"
                    font.bold: true
                }
                Text {
                    Layout.row: 0
                    Layout.column: 1
                    text: "Baseball"
                    font.pixelSize: 14
                }
                Text {
                    Layout.row:1
                    Layout.column: 0
                    font.pixelSize: 14
                    text: "Duration"
                    font.bold: true
                }
                Text {
                    Layout.row:1
                    Layout.column: 1
                    text: "00:50:00"
                    font.pixelSize: 14
                }
                Button {
                    id: downloadButton
                    Layout.row: 2
                    Layout.column: 1
                    Layout.preferredWidth: 100
                    Layout.alignment: Qt.AlignHCenter
                    text: qsTr("Download")
                }
            }
        }
    }
}
