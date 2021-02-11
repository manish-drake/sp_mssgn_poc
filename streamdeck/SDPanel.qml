import QtQuick 2.9

Grid{
    id: pnlTemplate
    property int size: 0
    property var mdl
    height: 4 * (pnlTemplate.size/5)
    width: size
    columns: 4
    rows: 3
    rowSpacing: size/(4 * 5)
    columnSpacing: size/(5 * 5)
    leftPadding: size/(5 * 5)
    topPadding: size/(4 * 5)
    Repeater{
        model: pnlTemplate.mdl
        delegate: SDButton {
            size: pnlTemplate.size/5
            lable: action
            defined: working

        }
    }
}
