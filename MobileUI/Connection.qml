import QtQuick 2.0
import Drake.UI.Complex 1.0 as DC
import Drake.UI.Base 1.0 as DB

Item {
    DB.Sub{
        anchors.top: parent.top
        anchors.topMargin: 10
        text: "CONNECTIONS"
        sideIcon: "qrc:/images/icon.png"
        stackRoot: root
    }
}
