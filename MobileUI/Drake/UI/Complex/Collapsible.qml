import QtQuick 2.0

Rectangle {
    id:collapsibleRoot
    property bool isCollapsed: true
    property string title: ""
    default property alias innerObject : container.children
    onIsCollapsedChanged: {
        height = collapsibleRoot.isCollapsed? 70: 2*width/3
        container.visible = collapsibleRoot.isCollapsed? false: true
    }

    width: ui.width - 20
    height:  width/3
    color: "lightgray"
    Text {
        id: txtTitle
        text: collapsibleRoot.title
        font.pixelSize: ui.text.medium
    }
    Image {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 10
        anchors.topMargin: 10
        id: arrowIcon
        fillMode: Image.PreserveAspectFit
        source: "qrc:/images/down_button100.png"
        rotation: 180
        height: 30; width: 30

        MouseArea{
            width: parent.width*2
            height: parent.height*2
            anchors.centerIn: parent
            onClicked: {
                arrowIcon.rotation += 180
                collapsibleRoot.isCollapsed = !collapsibleRoot.isCollapsed
            }
        }

    }
    Item {
        id: container
        visible: false
        anchors.top: arrowIcon.bottom
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        width: parent.width
    }
}
