import QtQuick 2.15
import QtQuick.Controls 2.15
import PowerMeter 1.0

Item {
    property string label : "Week:"
    property int deliverdAVG : 200
    property int deliveredCurrent : 100
    property int deliverdMax : 300
    property int deliveredMin : 100
    property int returnedAVG : 200
    property int returnedCurrent : 100
    property int returnedMax : 300
    property int returnedMin : 100
    property int resultAVG : 200
    property int resultCurrent : 100
    property int resultMax : 300
    property int resultMin : 100
    property real gasAvg : 200
    property real gasCurrent : 100
    property real gasMax : 300
    property real gasMin : 100
    property real solarAvg : 200
    property real solarCurrent : 100
    property real solarMax : 300
    property real solarMin : 100
    property real usedAvg : 200
    property real usedCurrent: 100
    property real usedMax : 300
    property real usedMin : 300

    id: root
    width: 480
    height: container.height

    MyContainer{
        id: container
        x:0
        y:0
        height: bar4.height + bar4.y + 5
        width: root.width

        Text{
            id: lbl
            text: root.label
            horizontalAlignment: Text.AlignHCenter
            x:0
            y: 5
            width: root.width
            font: Style.fLarge
            color: Style.clrText
        }

        BarItem{
            id: bar0
            x: 10
            y: lbl.y + lbl.height
            height: 25
            width: root.width - x*2
            titleLabel: "Used"
            maxVal: usedMax
            minVal: usedMin
            avg: usedAvg
            current: usedCurrent
            after: " kwh"


        }

        BarItem{
            id: bar1
            x: 10
            y: bar0.y + bar0.height + 2
            height: 25
            width: root.width - x*2
            titleLabel: "Delivered"
            maxVal: deliverdMax
            minVal: deliveredMin
            avg: deliverdAVG
            current: deliveredCurrent
            after: " kwh"


        }



        BarItem{
            id: bar2
            x: 10
            y: bar1.y + bar1.height + 2
            height: 25
            width: root.width - x*2
            titleLabel: "Returned"
            maxVal: returnedMax
            minVal: returnedMin
            avg: returnedAVG
            current: returnedCurrent
            after: " kwh"
            clr2:"#AAC0FFC0"
            clr3:"#81FF81";
            clr4:"#42FF42";
            clr5:"#00FF00";

        }

        BarItem{
            id: bar3
            x: 10
            y: bar2.y + bar2.height + 2
            height: 25
            width: root.width - x*2
            titleLabel: "Result"
            maxVal: resultMax
            minVal: resultMin
            avg: resultAVG
            current: resultCurrent
            after: " kwh"
        }

        BarItem{
            id: bar5
            x: 10
            y: bar3.y + bar3.height + 2
            height: 25
            width: root.width - x*2
            titleLabel: "Solar"
            maxVal: solarMax
            minVal: solarMin
            avg: solarAvg
            current: solarCurrent
            after: " kwh"
            clr2: "#AAFFFF00";
            clr3: "#88FFFF00";
            clr4: "#FFFF00";
            clr5: "#FFFF00";
        }


        BarItem{
            id: bar4
            x: 10
            y: bar5.y + bar5.height + 2
            height: 25
            width: root.width - x*2
            titleLabel: "Gas"
            maxVal: gasMax
            minVal: gasMin
            avg: gasAvg
            current: gasCurrent
            after: " m3"
            clr2: "#AAC0FFFF";
            clr3: "#81FFFF";
            clr4: "#42FFFF";
            clr5: "#00FFFF";
        }





    }

}
