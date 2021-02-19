import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
Item {
    id:md
    anchors.fill: parent
    Column{
        Rectangle{
            color: "#1E90FF"
            height: md.height/12
            width: md.width
            Text{
                text:"Metadata"
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
            height: 11*md.height/12
            width: md.width
            GridLayout{
                id: grid
                anchors.fill: parent
                anchors.topMargin: 50
                anchors.leftMargin: 60
                anchors.bottomMargin: 100
                Text {
                    Layout.row:0
                    Layout.column: 0
                    id: text
                    text: qsTr("Info:")
                    font.pixelSize: 14
                    color: "#1E90FF"
                    font.bold: true
                }
                Text {
                    Layout.row:1
                    Layout.column: 0
                    id: text1
                    text: qsTr("Name:")
                    font.pixelSize: 14
                    font.bold: true
                }
                Text {
                    Layout.row:1
                    Layout.column: 1
                    id: text2
                    text: qsTr("Baseball")
                    font.pixelSize: 14
                }
                Text {
                    Layout.row:2
                    Layout.column:0
                    id: text3
                    text: qsTr("Title:")
                    font.pixelSize: 14
                    font.bold: true
                }
                Text {
                    Layout.row:2
                    Layout.column: 1
                    id: text4
                    text: qsTr("Baseball Game")
                    font.pixelSize: 14
                }
                Text {
                    Layout.row:2
                    Layout.column: 2
                    id: text5
                    text: qsTr("Duration")
                    font.pixelSize: 14
                    font.bold: true
                }
                Text {
                    Layout.row:2
                    Layout.column: 3
                    id: text6
                    text: qsTr("00:00:00")
                    font.pixelSize: 14
                }
                Text {
                    Layout.row:3
                    Layout.column:0
                    id: text7
                    text: qsTr("Tags:")
                    font.pixelSize: 14
                    color: "#1E90FF"
                    font.bold: true
                }
                Text {
                    Layout.row:4
                    Layout.column:0
                    id: text8
                    text: qsTr("Start Time:")
                    font.pixelSize: 14
                    font.bold: true
                }
                Text {
                    Layout.row:4
                    Layout.column:1
                    id: text9
                    text: qsTr("00:50:00")
                    font.pixelSize: 14
                }
                Text {
                    Layout.row:4
                    Layout.column:2
                    id: text10
                    text: qsTr("Event:")
                    font.pixelSize: 14
                    font.bold: true
                }
                Text {
                    Layout.row:4
                    Layout.column:3
                    id: text11
                    text: qsTr("Baseball Game")
                    font.pixelSize: 14
                }
                Button {
                    anchors.topMargin: 50
                    Layout.row:5
                    Layout.column:3
                    id: button
                    text: qsTr("Preview")
                    onClicked: {
                        if(vm.val == 0)
                        {
                            ml.source = "Preview_stream.qml"
                        }
                        else if(vm.val == 1)
                        {
                            ml.source = "Preview_download.qml"
                        }
                        else
                        {
                            console.log("Select the mode of preview in settings")
                        }

                   }
               }
           }
        }
    }
}
