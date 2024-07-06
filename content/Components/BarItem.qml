import QtQuick 2.15
import QtQuick.Controls 2.15
import PowerMeter 1.0

Item {
    property color clr1 :  "#00FFFFFF"
    property color clr2 :  "#AA00FF00"
    property color clr3 : "#00FF00"
    property color clr4 : "#FF8800"
    property color clr5 : "#FF0000"

    property real maxVal : 200
    property real minVal : 0
    property real avg : 100
    property real current : 175

    property string after : " kwh"
    property string titleLabel : "title:";

    id: root
    width: 480
    height: 480

    /*
    onMaxValChanged:
    {
       // maskWidth()
    }
    onMinValChanged: {

       // maskWidth();
    }
    onCurrentChanged: maskWidth();
    onAvgChanged: maskWidth();
    */

    function maskWidth(){

        /*
        var nullOffset = root.minVal;
        var currenT = root.current;
        if(root.minVal < 0){
            nullOffset = root.min * -1;
           }
            nullOffset = root.minVal
           // root.minVal = root.min - nullOffset
          // root.max = root.max - nullOffset
            //root.avg = root.avg + nullOffset
            currenT = root.current - nullOffset


        var totalVal = root.maxVal - root.minVal;
        var totalWidth = bar1.width
        var widthPerVal = totalWidth/totalVal

        var retX = currenT * widthPerVal
       // retX = root.width - retX
        maskRect.width = retX;
        */
    }

    Text{
        id:lbl
        x: 5
        y: 5
        width: 75
        height: root.height - y*2
        color: Style.clrText
        text: root.titleLabel
        verticalAlignment: Text.AlignVCenter
    }



    Rectangle{
        visible: true
        id: bar1
        x: lbl.x + lbl.width
        y: 0
        width: root.width - x
        height: root.height
        clip:true
        gradient: Gradient {
            orientation: Gradient.Horizontal
            GradientStop {
                position: 0.0
                color: clr1
            }
            GradientStop {
                position: 0.25
                color: clr2
            }
            GradientStop {
                position: 0.5
                color: clr3
            }
            GradientStop {
                position: 0.75
                color: clr4
            }
            GradientStop {
                position: 1.0
                color:  clr5
            }
        }

        Rectangle{
            id:maskRect
            x: bar1.width - width
            y: 0
            height: bar1.height
            width: root.width * (1 - (root.current - root.minVal) / (root.maxVal - root.minVal));
            color: Style.clrMask
        }

        Text{
            x:5
            y:5
            text: "Current: "+ Math.round(root.current / 100) / 10 + after
            height: root.height - y*2
            width: root.width/4
            font: Style.fMediumBold
            color: Style.clrText
            verticalAlignment: Text.AlignVCenter
        }

        Text{
            x:bar1.width - width - 5
            y:5
            text: "AVG: "+ Math.round(root.avg / 100) / 10 + after
            horizontalAlignment: Text.AlignRight
            height: root.height - y*2
            width: root.width/4
            font: Style.fMediumBold
            color: Style.clrText
            verticalAlignment: Text.AlignVCenter
        }

    }

    ProgressBar{
        visible: false;
        height: root.height
        width:root.width
        from: root.minVal
        to:root.maxVal
        value: root.avg
        onFromChanged: console.log( titleLabel + "FROM = "+ from + " // "+ root.minVal)
        onToChanged: console.log(titleLabel + "TO = "+ to + " // "+ root.maxVal)
        onValueChanged: console.log(titleLabel + "Value = "+ value + " // "+ root.avg)
    }
}
