import QtQuick 2.6
import QtQuick.Window 2.2
import Drake.UI.Complex 1.0 as DC
import Drake.UI.Base 1.0 as DB

Window {
    visible: true
    width: ui.width
    height: ui.height
    title: qsTr("Hello World")
    DC.CollapsibleContainer {
        id: collapsCtrl
        anchors.centerIn: parent
        title: "Desktop RI-26U"
        innerObject: DB.Button{
            onHit: collapsCtrl.isCollapsed = true
        }
    }
}
