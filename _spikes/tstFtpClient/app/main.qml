import QtQuick 2.6
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    MouseArea {
        anchors.fill: parent
        onClicked: {
            console.log(qsTr('Clicked on background. Text: "' + textEdit.text + '"'))
        }
    }

    TextEdit {
        id: textEdit
        text: qsTr("Enter some text...")
        verticalAlignment: Text.AlignVCenter
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        Rectangle {
            anchors.fill: parent
            anchors.margins: -10
            color: "transparent"
            border.width: 1
        }
    }
    Rectangle{
        height: 100
        gradient: Gradient {
            GradientStop {
                position: 0.00;
                color: "#e67777";
            }
            GradientStop {
                position: 1.00;
                color: "#95d368";
            }
        }
        width: 200
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        MouseArea{
            anchors.fill: parent
            onClicked: vm.run()
        }
    }

}
