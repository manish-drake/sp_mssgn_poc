import QtQuick 2.6
import QtQuick.Window 2.2
import Drake.UI.Complex 1.0 as DC
import Drake.UI.Base 1.0 as DB

Item {
    Rectangle{
        anchors.fill: parent
        DB.IconAction{
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            icon: "qrc:/images/icon.png"
            height: 30; width: 30
            onAction: {
                root.push("qrc:/Setup.qml")
            }
        }

        DB.Title{
            anchors.top: parent.top
            anchors.topMargin: 10
            text: "MATRIX"
        }


        DB.IconAction{
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            icon: "qrc:/images/icon.png"
            height: 30; width: 30
            onAction: {
                root.push("qrc:/Connection.qml")
            }
        }

        Text {
            id: txtDefault
            text: qsTr("There are no PIPs on the phone to list. \nPlease click on the add button below to start \nediting a new matrix.")
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 0
            anchors.centerIn: parent
        }

        Rectangle{
            id: footerDefault
            visible: true
            width: parent.width
            height: 90
            color: "#5B74B7"
            anchors.bottom: parent.bottom

            DB.IconAction{
                id: imgMatrix
                anchors.centerIn: parent
                icon: "qrc:/images/icon.png"
                height: 60; width: 60
                onAction: {
                    root.push("qrc:/Matrix.qml")
                }
            }
            DB.IconAction{
                anchors.top: parent.top
                anchors.topMargin: 5
                anchors.right: parent.right
                anchors.rightMargin: 10
                icon: "qrc:/images/icon.png"
                height: 30; width: 30
                onAction: {
                    footerExpanded.visible=true
                    footerDefault.visible=false
                }
            }
        }
        Rectangle{
            id: footerExpanded
            visible: false
            width: parent.width
            height: 120
            color: "#5B74B7"
            anchors.bottom: parent.bottom

            DB.IconAction{
                id: imgMatrixEx
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter
                icon: "qrc:/images/icon.png"
                caption: "New Matrix"
                height: 60; width: 60
                onAction: {
                    root.push("qrc:/Matrix.qml")
                }
            }
            DB.IconAction{
                anchors.top: parent.top
                anchors.topMargin: 5
                anchors.right: parent.right
                anchors.rightMargin: 10
                icon: "qrc:/images/icon.png"
                height: 30; width: 30
                onAction: {
                    footerExpanded.visible=false
                    footerDefault.visible=true
                }
            }
            DB.TextAction {
                id: txtBottomLabel
                text: qsTr("Samsung Cam Test")
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                onAction:{
                    console.log("Samsung Cam Text: action()")
                }
            }
        }
    }
}
