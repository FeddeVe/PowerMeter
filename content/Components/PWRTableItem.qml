import QtQuick 2.15
import QtQuick.Controls 2.15
import PowerMeter 1.0

Item {
    property int min : -100
    property int max : 100
    property int avg_val : 26
    property int cur_val : 75
    property int nullY : 0
    property int pwrMode : 0
    property bool isCurrent : true;

    id:root
    width: 100
    height: 400

    onMinChanged: {
        avgRect.y = recY(avg_val);
        avgRect.height = recHeight(avg_val, y);
        curRect.y = recY(cur_val);
        curRect.height = recHeight(cur_val, y);
    }

    onMaxChanged: {
        avgRect.y = recY(avg_val);
        avgRect.height = recHeight(avg_val, y);
        curRect.y = recY(cur_val);
        curRect.height = recHeight(cur_val, y);
    }

    onCur_valChanged: {
        curRect.y = recY(cur_val);
        curRect.height = recHeight(cur_val, y);
    }

    onAvg_valChanged: {
        avgRect.y = recY(avg_val);
        avgRect.height = recHeight(avg_val, y);
    }


    function recY(value){
      //  if(root.min == root.max){
      //      root.min = root.max - 1;
      //  }
      //  if(root.min > 0){
      //      root.min = 0;
      //  }
        var dbgMin = root.min;
        var totalVal = root.max - root.min;
        var totalHeight = root.height
        var heigthPerVal = totalHeight/totalVal
        var nullY = root.height - ((root.min * -1) * heigthPerVal);
        console.log(totalVal);
        console.log(totalHeight);
        console.log(heigthPerVal);
        console.log(nullY);

        if(value < 0){
           return nullY;
        }else{
            var tmp = (max - value) * heigthPerVal;
            return tmp;
        }
    }

    function recHeight(value, y){
       // if(min == max){
       //     min = max - 1;
       // }
       // if(min > 0){
       //     min = 0;
       // }
        var totalVal = max - min;
        var totalHeight = root.height
        var heigthPerVal = totalHeight/totalVal;

        if(root.isCurrent){
            return 0;
        }

        if(value > 0){
           return (value * heigthPerVal);
        }else{
            var tmp = (value * -1) * heigthPerVal;
            return tmp;
        }
    }




    Rectangle{
        id:avgRect
        x: root.width *0.02;
        y: recY(avg_val);
        width: root.width - x*2;
        height: recHeight(avg_val, y);
        color: Style.gray;
        clip:true

        Text{
            id:avgText
            text: Math.round(root.avg_val / 10) / 100
            horizontalAlignment: Text.AlignHCenter
            width: avgRect.width;
            y: root.avg_val < 0 ? avgRect.height - height - 15 : 15
            transform: Rotation { origin.x: avgText.width / 2; origin.y: avgText.height/2; angle: 90}
            color: Style.clrText
        }
    }

    Rectangle{
        id:curRect
        x: root.width * 0.1;
        y: recY(cur_val);
        width: root.width- x*2
        height: recHeight(cur_val, y);
        color: root.pwrMode == 2 ? Style.halfCyan : root.pwrMode == 3 ? Style.halfLight : root.pwrMode == 4 ? Style.halfYellow :  Style.halfOrange;
         clip:true

        Text{
            id:curText
            text: Math.round(root.cur_val / 10) / 100
            horizontalAlignment: Text.AlignHCenter
            width: curRect.width;
            y: root.cur_val < 0 ? curRect.height - height - 15 : 15
            transform: Rotation { origin.x: curText.width / 2; origin.y: curText.height/2; angle: 90}

        }
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


