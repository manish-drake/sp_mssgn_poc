import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Item {
    id:mls
    anchors.fill: parent
    function setWidth(abso){
        return (mls.width * abso)/600
    }
    function setHeight(abso){
        return (mls.height * abso)/400
    }

    Column{
        Network{
            width: parent.width
        }
        Rectangle{
            color: "#1E90FF"
            height: ml.height/12
            width: ml.width
            Text{
                text:"Media List"
                font.family: "MS Shell Dlg 2"
                font.bold: true
                x:17
                y:10
                horizontalAlignment: Text.AlignHCenter
                color: "#ffffff"
                font.pointSize: setWidth(12)
            }

            Item {
                id: button
                width: setWidth(30)
                height: setHeight(100)
                signal clicked
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.rightMargin: setWidth(20)
                anchors.topMargin: setHeight(10)
                Image {
                    source:  "./image/icons8-settings-384.png"
                    width: setWidth(20); height: setHeight(20)
                    fillMode: Image.PreserveAspectCrop
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            ml.source = "Settings.qml"
                        }
                    }
                }
            }
        }
        Rectangle{
            color: "#ffffff"
            height: 11*ml.height/12
            width: ml.width
            id: rectContainer
            Component {
                      id: contactsDelegate
                      Rectangle {
                          id: wrapper
                          width: rectContainer.width
                          height: contactInfo.height
                          color: ListView.isCurrentItem ? "gray" : "white"
                          Text {
                              id: contactInfo
                              text: index + ": " + display
                              color: wrapper.ListView.isCurrentItem ? "white" : "black"
                          }
                      }
                  }

                  ListView {
                      anchors.fill: parent
                      model: vm.mediaFiles
                      delegate: contactsDelegate
                      highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
                      focus: true
                      add: Transition {
                                NumberAnimation { properties: "x,y"; from: 100; duration: 1000 }
                            }
                  }

        }
    }
}

