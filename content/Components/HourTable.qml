import QtQuick 2.15
import QtQuick.Controls 2.15
import PowerMeter 1.0

Item {
    property var dataModel : hourManager
    property string tableName : "Table Name"
    id:root
    width: 500
    height: Constants.height

    MyContainer{
        x:0
        y:0
        height:root.height
        width:root.width

        Text{
            id:mode
            text: dataModel.pwrModeText
            font:Style.fHugeBold
            color:Style.clrText
            x:5
            y:5

        }

        Text{
            id:tableNameText
            text: tableName
            font:Style.fHugeBold
            color:Style.clrText
            x:root.width - width - 5
            y:5

        }

        Repeater {
            id: repeater
            x:0
            y:mode.y + mode.height


            property real startY : mode.y+mode.height
            property real startX : 5
            property real itemWidth: (root.width - startX *2) / dataModel.count
            model: dataModel
               TableRepeater{
                   x: repeater.startX + (repeater.itemWidth * index);
                   y: repeater.startY
                   width: repeater.itemWidth;
                   height: root.height - repeater.startY * 2
                   pwrmin: dataModel.pwrMin
                   pwrmax: dataModel.pwrMax
                   gasMin: dataModel.gasMin
                   gasMax: dataModel.gasMax
                   item: dataModel.get(index)
                   pwrMode: dataModel.pwrMode

               }


           }

        MouseArea{
            anchors.fill: parent
            onClicked: dataModel.pwrMode = 1
        }

    }


}
