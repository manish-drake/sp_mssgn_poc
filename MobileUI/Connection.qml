import QtQuick 2.0
import Drake.UI.Complex 1.0 as DC
import Drake.UI.Base 1.0 as DB

Item{
    Column{
        anchors.fill: parent
        Item {
            id: header
            height: 1*parent.height/10
            width: parent.width
            DB.Sub{
                anchors.top: parent.top
                anchors.topMargin: 10
                text: "CONNECTIONS"
                sideIcon: "qrc:/images/icon.png"
                stackRoot: root
            }
            DB.IconAction{
                icon: "qrc:/images/icon.png"
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 10
                height: 30; width: 30
                onAction: {
                    console.log("Connections icon pressed")
                }
            }
        }
        Item{
            id: upperBody
            height: 1*parent.height/10
            width: parent.width

            DB.StdText{
                text: "On"
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.left: parent.left
                anchors.leftMargin: 10
            }
            DB.StdSwitch{
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 10

            }
        }
        Item{
            id: lowerBody
            height: 8*parent.height/10
            width: parent.width
            DC.CollapsibleContainer{
                title: "DESKTOP-RI26D458"
                Column{
                    anchors.fill: parent

                    DB.StdRow{
                        label: "IP Address"
                        text: "192.168.10.21"
                    }
                    DB.StdRow{
                        label: "Description"
                        text: "Pro Matrix Server - DESKTOP-RI26D458"
                    }
                }
            }

        }

    }

}
