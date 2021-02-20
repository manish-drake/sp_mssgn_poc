import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2


Item {
    id:s
    property string downloadbutton: value
    property string streambutton: value
    anchors.fill: parent
    Column{
        Rectangle{
            color: "#1E90FF"
            height: s.height/12
            width: s.width

            Text{
                text:"Preview Setting"
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
            onHeightChanged: console.log (height)
            color: "white"
            height: 11*s.height/12
            width: s.width
            GridLayout{
                id: grid
                anchors.fill: parent
                anchors.topMargin: 50
                anchors.leftMargin: 60
                anchors.bottomMargin: 100
                Label{
                    Layout.row:0
                    Layout.column: 0
                    text: "Preview"
                    font.pixelSize: 14
                    font.bold: true
                }
                RadioButton {
                    id:streambutton
                    Layout.row:0
                    Layout.column: 1
                    font.pixelSize: 14
                    text: "Stream"
                }
                RadioButton {
                    id:downloadbutton
                    Layout.row:1
                    Layout.column: 1
                    text: "Download"
                    font.pixelSize: 14
                }
                Button{
                    id: result
                    Layout.row: 2
                    Layout.column: 1
                    Layout.preferredWidth: 100
                    Layout.alignment: Qt.AlignHCenter
                    text: qsTr("Ok")
                    onClicked: {

                        if(streambutton.checked)
                        {
                            vm.val=0
                        }
                        if(downloadbutton.checked)
                        {
                            vm.val=1
                        }
                        ml.source = "Medialist.qml"
                    }

                }
            }
        }
    }
}
