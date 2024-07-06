import QtQuick 2.15
import QtQuick.Controls 2.15
import PowerMeter 1.0

Item {
    property int min : -100
    property int max : 100
    property int avg_val : 100
    property int cur_val : 75
    property int nullY : 0

    id:root
    width: 100
    height: 400



    function recHeight(value){
        if(min == max){
            min = max - 1;
        }
        if(min > 0){
            min = 0;
        }
        var totalVal = max - min;
        var totalHeight = root.height
        var heigthPerVal = totalHeight/totalVal;

        return (value * heigthPerVal);

    }




    Rectangle{
        id:avgRect
        x: root.width *0.02;
        y: 0;
        width: root.width - x*2;
        height: recHeight(avg_val);
        color: Style.clrDark;
        clip:true

        Text{
            text: avg_val
            horizontalAlignment: Text.AlignHCenter
            width: avgRect.width;
            y: avgRect.height - height - 5
        }
    }

    Rectangle{
        id:curRect
        x: root.width * 0.05;
        y: 0;
        width: root.width- x*2
        height: recHeight(cur_val);
        color: Style.halfCyan;
        clip:true

        Text{
            text: cur_val
            horizontalAlignment: Text.AlignHCenter
            width: curRect.width;
            y:  curRect.height - height - 5
        }
    }






    }


