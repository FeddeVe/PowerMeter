import QtQuick 2.15
import QtQuick.Controls 2.15
import PowerMeter 1.0

Item {
    property int pwrmin : 0
    property int pwrmax : 100
    property int gasMin : -100
    property int gasMax : 100
    property int pwravg_val : 26
    property int pwrcur_val : 75
    property int pwrMode : 0
    property var item

    id:root
    width: Constants.width
    height: 400

    Rectangle{
        x:0
        y:0
        height: root.height
        width: root.width
        color:Style.gray
        gradient: Gradient {
            orientation: Gradient.Vertical
            GradientStop {
                position: 0.0
                color: Style.background
            }
            GradientStop {
                position: 1.0
                color: Style.gray
            }
        }

    PWRTableItem{
        id:pwr
        width: root.width
        height:  root.height - 50
        min: root.pwrmin
        max: root.pwrmax
        avg_val: root.pwrMode == 0 ? item.avgResult : root.pwrMode == 1 ?item.avgDelivered : root.pwrMode == 2 ? item.avgReturned : root.pwrMode == 3 ? item.avgGas : root.pwrMode == 4 ?item.avgSolar : item.avgUsed
        cur_val: root.pwrMode == 0 ? item.curResult : root.pwrMode == 1 ?item.curDelivered : root.pwrMode == 2 ? item.curReturned : root.pwrMode == 3 ? item.curGas : root.pwrMode == 4 ? item.curSolar : item.curUsed
        pwrMode: root.pwrMode
        isCurrent: item.isCurrent
    }

    Text{
        id:labelText
        x:root.width/2 - width /2
        y:root.height- width
        text: item.label
       // text:"88:88"
        color: Style.clrText
        font: Style.fStandard
        transform: Rotation { origin.x: labelText.width / 2; origin.y: labelText.height/2; angle: 90}

    }

    Canvas {
            width: root.width; height: root.height
            property color lineColor : Style.grey
            onLineColorChanged: requestPaint()
            onPaint: {
                var ctx = getContext("2d")
                ctx.lineWidth = 1
                ctx.strokeStyle = lineColor
                ctx.beginPath()
                ctx.moveTo(root.width-1, 0)
                ctx.lineTo(root.width-1, root.height);
                ctx.closePath()
                //ctx.fill()
                ctx.stroke()
            }
        }




    }

}
