import QtQuick 2.9

Rectangle {
    property int size: 0
    property string lable
    property bool pressed: false
    property bool defined: false
    property int clickAction: -1
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
        font.bold: true
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
            lbl.color="#73f188"
        }
        onExited: {
            if(buttTemplate.pressed)
                lbl.color="#73f188"
            else
                lbl.color="#939994"
        }
        onClicked: {
            valid = vm.run(buttTemplate.clickAction)
            if(valid)
            {
                buttTemplate.pressed = !buttTemplate.pressed
                lbl.color="#73f188"
                if(buttTemplate.pressed)
                    buttTemplate.color="gray"
                else
                    buttTemplate.color="lightgray"

            }

        }
    }
}
