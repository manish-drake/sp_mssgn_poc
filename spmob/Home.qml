import QtQuick 2.9

Item {
    id: home
    anchors.fill: parent
    property string header: ""
    property string body: ""
    property string footer: "awaiting request.."
    property bool isRecording
    Column{
        id: homeContainer
        anchors.fill: parent
        visible: !home.isRecording
        Network{
            width: parent.width
        }

        Text{
            id:title
            width: parent.width
            text: "SPORTS PIP"
            font.family: "DejaVu Sans"
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 16
            height: 50
        }

        Rectangle{
            color: "#ffffff"
            height: 11*homeContainer.height/12
            width: homeContainer.width
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
    CamBox{
            anchors.fill: parent
            visible: home.isRecording
        }

}
