import QtQuick 2.6
import QtQuick.Window 2.2
import "Drake/UI/Complex" as DC
import "Drake/UI/Base" as DB

Window {
    visible: true
    width: ui.width
    height: ui.height
    title: qsTr("Hello World")
    DC.Collapsible {
        id: collapsCtrl
        anchors.centerIn: parent
        title: "Desktop RI-26U"
        innerObject: DB.Button{
            onHit: collapsCtrl.isCollapsed = true
        }
    }
}
