import QtQuick 2.9

Rectangle {
    property int size: 0
    property string lable
    property bool pressed: false
    property bool defined: false
    property int clickAction: -1
    property int modelState: vm.state
    property int actvState: 5

    id: buttTemplate
    height: size
    width: size
    color: "lightgray"
    border.color: "black"
    radius: size/10

    Text {
        id: lbl
        color: "#939994"
        anchors.centerIn: parent
        text: qsTr(buttTemplate.lable)
        font.family: "Arial"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        style: Text.Raised
        font.pointSize: 10 * size/50
    }
    MouseArea{
        id:maButtTemplate
        property bool valid: false
        enabled: buttTemplate.defined
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            lbl.color="#76db1d"
        }
        onExited: lbl.color="#939994"
        onReleased: buttTemplate.color="lightgray"
        onPressed: buttTemplate.color="gray"

        onClicked: {
            valid = vm.run(buttTemplate.clickAction)
        }
    }
}
