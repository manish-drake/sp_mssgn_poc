import QtQuick 2.0
import Drake.UI.Base 1.0 as DB

Rectangle {
    id:collapsibleRoot
    property string iconCollapseButton: "qrc:/images/icon.png"
    property bool isCollapsed: true
    property string title: ""
    property real collapsedHeight: 70
    default property alias innerObject : container.children

    onIsCollapsedChanged: {
        height = collapsibleRoot.isCollapsed? collapsibleRoot.collapsedHeight: (ui.height/5)
        container.visible = collapsibleRoot.isCollapsed? false: true
    }

    width: ui.width - 20
    height:  collapsibleRoot.collapsedHeight
    color: "lightgray"
    Text {
        id: txtTitle
        text: collapsibleRoot.title
        font.pixelSize: ui.text.medium
    }
    DB.IconAction {
        id: arrowIcon
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 10
        anchors.topMargin: 10
        icon: collapsibleRoot.iconCollapseButton
        rotation: 180
        height: 30; width: 30

        onAction: {
            arrowIcon.rotation += 180
            collapsibleRoot.isCollapsed = !collapsibleRoot.isCollapsed
        }

    }
    Item {
        id: container
        visible: false
        anchors.fill: parent
        anchors.margins: 40
    }
}
