import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Item {
    id:mls
    anchors.fill: parent
    function setWidth(abso){
        return (mls.width * abso)/600
    }
    function setHeight(abso){
        return (mls.height * abso)/400
    }

    Column{
        Rectangle{
            color: "#1E90FF"
            height: ml.height/12
            width: ml.width
            Text{
                text:"Media List"
                font.family: "MS Shell Dlg 2"
                font.bold: true
                x:17
                y:10
                horizontalAlignment: Text.AlignHCenter
                color: "#ffffff"
                font.pointSize: setWidth(12)
            }

            Item {
                id: button
                width: setWidth(30)
                height: setHeight(100)
                signal clicked
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.rightMargin: setWidth(20)
                anchors.topMargin: setHeight(10)
                Image {
                    source:  "./image/icons8-settings-384.png"
                    width: setWidth(20); height: setHeight(20)
                    fillMode: Image.PreserveAspectCrop
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            ml.source = "Settings.qml"
                        }
                    }
                }
            }
        }
        Rectangle{
            color: "#ffffff"
            height: 11*ml.height/12
            width: ml.width
            GridLayout{
                id: grid
                anchors.fill: parent
                anchors.topMargin:setHeight(50)
                anchors.leftMargin:setWidth(60)
                Text {
                    id: text1
                    Layout.row:0
                    Layout.column: 0
                    text: qsTr("Name")
                    font.pixelSize: setWidth(14)
                    font.bold: true
                    height: setHeight(20)
                }
                Text {
                    id: text2
                    Layout.row:0
                    Layout.column: 1
                    text: qsTr("Time")
                    font.pixelSize: setWidth(14)
                    font.bold: true
                    height: setHeight(20)
                }
                Text {
                    id: text3
                    Layout.row:0
                    Layout.column: 2
                    text: qsTr("Duration")
                    font.pixelSize: setWidth(14)
                    font.bold: true
                    height: setHeight(20)
                }
                Text {
                    id: text4
                    Layout.row:0
                    Layout.column: 3
                    text: qsTr("Local")
                    font.pixelSize: setWidth(14)
                    font.bold: true
                    height: setHeight(20)
                }
                Text {
                    id: text5
                    Layout.row:1
                    Layout.column: 0
                    text: qsTr("Golf")
                    font.pixelSize: setWidth(14)
                    height: setHeight(20)
                }
                Text {
                    id: text6
                    Layout.row:1
                    Layout.column: 1
                    text: qsTr("11:00")
                    font.pixelSize: setWidth(14)
                    height: setHeight(20)
                }
                Text {
                    id: text7
                    Layout.row:1
                    Layout.column: 2
                    text: qsTr("02:00:00")
                    font.pixelSize: setWidth(14)
                    height: setHeight(20)
                }
                Text {
                    id: text8
                    Layout.row:1
                    Layout.column: 3
                    text: qsTr("Yes")
                    font.pixelSize: setWidth(14)
                    height: setHeight(20)
                }
                Text {
                    id: text9
                    Layout.row:2
                    Layout.column: 0
                    text: qsTr("Baseball")
                    font.pixelSize: setWidth(14)
                    height: setHeight(20)
                }
                Text {
                    id: text10
                    Layout.row:2
                    Layout.column: 1
                    text: qsTr("15:00")
                    font.pixelSize: setWidth(14)
                    height: setHeight(20)
                }
                Text {
                    id: text11
                    Layout.row:2
                    Layout.column: 2
                    text: qsTr("00:50:00")
                    font.pixelSize: setWidth(14)
                    height: setHeight(20)
                }
                Text {
                    id: text12
                    text: '<html><style type="text/css"></style><a href="No">No*</a></html>'
                    font.bold: true
                    font.pointSize: setWidth(10)
                    onLinkActivated: ml.source = "Metadata.qml"
                    Layout.row:2
                    Layout.column: 3
                    height: setHeight(20)

                }
            }


        }
    }
}

