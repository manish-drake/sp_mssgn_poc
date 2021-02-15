import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick 2.9


Item {
    id:ps
    anchors.fill: parent
    Column{
        Rectangle{
            color: "#1E90FF"
            height: ps.height/12
            width: ps.width
            Text{
                text:"Preview (Stream)"
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
            height: 11*ps.height/12
            width: ps.width
            GridLayout{
                id: grid
                anchors.fill: parent
                anchors.topMargin: 10
                anchors.leftMargin: 60
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
                    Layout.row: 1
                    Layout.column: 0
                    font.pixelSize: 14
                    text: "Start:"
                    font.bold: true
                }
                Text {
                    Layout.row: 1
                    Layout.column: 1
                    text: "00:10:25"
                    font.pixelSize: 14
                }
                Text {
                    Layout.row: 2
                    Layout.column: 0
                    font.pixelSize: 14
                    text: "Duration"
                    font.bold: true
                }
                Text {
                    Layout.row: 2
                    Layout.column: 1
                    text: "00:50:00"
                    font.pixelSize: 14
                }
                Rectangle {
                    Layout.row: 3
                    Layout.column: 1
                    width: 350
                    height: 200
                    color:"black"
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            video.play()
                        }
                    }

                }
            }
        }
    }
}
