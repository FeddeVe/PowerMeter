import QtQuick 2.15
import QtQuick.Controls 2.15
import PowerMeter 1.0

Item {
    id:root
    property bool expanded : true
    property var live : liveManager
    width: Constants.width
    height: main.height

    MyContainer{
        id:main
        x:0
        y:0
        height: root.expanded ? gasVal.y + gasVal.height + 5 : liveVal.y + liveVal.height + 5
        width: root.width

        ExpandButton{
            id:expButton
            x:5
            y:5
            expanded:  root.expanded
            onExpandedChanged: root.expanded = expanded
        }

        Text{
            id:liveHeader
            x:expButton.x + expButton.width + 20
            y:5
            text: "LIVE:"
            horizontalAlignment: Text.AlignRight
            font: Style.fHugeBold
            color: Style.clrText
            width: root.width / 2 - x - 5
        }

        Text{
            id:liveVal
            x:liveHeader.x + liveHeader.width + 5
            y:5
            text: live.liveVal
            horizontalAlignment: Text.AlignLeft
            font: Style.fHugeBold
            color: Style.clrText
            width: root.width / 2 - 5
        }

        SplitterHorizontal{
            id:split3
            x: split1.x
            y: liveHeader.y + liveHeader.height + 6
            width: root.width - x * 2
        }

        Text{
            id:delText
            x:expButton.x + expButton.width + 20
            y:split3.y + split3.height
            text: "Deliverd:"
            horizontalAlignment: Text.AlignRight
            font: Style.fLarge
            color: Style.clrText
            width: root.width / 2 - x - 5
        }

        Text{
            id:delVal
            x:delText.x + delText.width + 5
            y:delText.y
            text: live.delivered
            horizontalAlignment: Text.AlignLeft
            font: Style.fLargeBold
            color: Style.clrText
            width: root.width - x - 5
        }


        Text{
            id:retText
            x:expButton.x + expButton.width + 20
            y:delVal.y + delVal.height
            text: "Returned:"
            horizontalAlignment: Text.AlignRight
            font: Style.fLarge
            color: Style.clrText
            width: root.width / 2 - x - 5
        }

        Text{
            id:retVal
            x:retText.x + retText.width + 5
            y:retText.y
            text: live.returned;
            horizontalAlignment: Text.AlignLeft
            font: Style.fLargeBold
            color: Style.clrText
            width: root.width - x - 5
        }

        Text{
            id:solarText
            x:expButton.x + expButton.width + 20
            y:retVal.y + retVal.height
            text: "Solar Panels:"
            horizontalAlignment: Text.AlignRight
            font: Style.fLarge
            color: Style.clrText
            width: root.width / 2 - x - 5
        }

        Text{
            id:solarVal
            x:retText.x + retText.width + 5
            y:solarText.y
            text: live.solar;
            horizontalAlignment: Text.AlignLeft
            font: Style.fLargeBold
            color: Style.clrText
            width: root.width - x - 5
        }

        SplitterHorizontal{
            id:split1
            x: expButton.x + expButton.width
            y:solarVal.y + solarVal.height + 6
            width: root.width - x*2
        }

        Text{
            id:t1Text
            x:expButton.x + expButton.width + 20
            y:split1.y + split1.height + 5
            text: "Delivered Tarif 1:"
            horizontalAlignment: Text.AlignRight
            font: Style.fMedium
            color: Style.clrText
            width: root.width / 2 - x - 5
        }

        Text{
            id:t1Val
            x:retVal.x
            y:t1Text.y
            text: live.t1
            horizontalAlignment: Text.AlignLeft
            font: Style.fMediumBold
            color: Style.clrText
            width: root.width - x - 5
        }

        Text{
            id:t2Text
            x:expButton.x + expButton.width + 20
            y:t1Text.y + t1Text.height
            text: "Delivered Tarif 2:"
            horizontalAlignment: Text.AlignRight
            font: Style.fMedium
            color: Style.clrText
            width: root.width / 2 - x - 5
        }

        Text{
            id:t2Val
            x:retVal.x
            y:t2Text.y
            text: live.t2
            horizontalAlignment: Text.AlignLeft
            font: Style.fMediumBold
            color: Style.clrText
            width: root.width - x - 5
        }

        Text{
            id:totalText
            x:expButton.x + expButton.width + 20
            y:t2Text.y + t2Text.height
            text: "Delivered Total:"
            horizontalAlignment: Text.AlignRight
            font: Style.fMedium
            color: Style.clrText
            width: root.width / 2 - x - 5
        }

        Text{
            id:totalVal
            x:retVal.x
            y:totalText.y
            text: live.total
            horizontalAlignment: Text.AlignLeft
            font: Style.fMediumBold
            color: Style.clrText
            width: root.width - x - 5
        }

        Text{
            id:retT1Text
            x:expButton.x + expButton.width + 20
            y:totalText.y + totalText.height
            text: "Returned Tarif 1:"
            horizontalAlignment: Text.AlignRight
            font: Style.fMedium
            color: Style.clrText
            width: root.width / 2 - x - 5
        }

        Text{
            id:rett1Val
            x:retVal.x
            y: retT1Text.y
            text: live.retT1
            horizontalAlignment: Text.AlignLeft
            font: Style.fMediumBold
            color: Style.clrText
            width: root.width - x - 5
        }

        Text{
            id:rett2Text
            x:expButton.x + expButton.width + 20
            y:retT1Text.y + retT1Text.height
            text: "Returned Tarif 2:"
            horizontalAlignment: Text.AlignRight
            font: Style.fMedium
            color: Style.clrText
            width: root.width / 2 - x - 5
        }

        Text{
            id:rett2Val
            x:retVal.x
            y:rett2Text.y
            text: live.retT2
            horizontalAlignment: Text.AlignLeft
            font: Style.fMediumBold
            color: Style.clrText
            width: root.width - x - 5
        }

        Text{
            id:rettotalText
            x:expButton.x + expButton.width + 20
            y:rett2Text.y + rett2Text.height
            text: "Returned Total:"
            horizontalAlignment: Text.AlignRight
            font: Style.fMedium
            color: Style.clrText
            width: root.width / 2 - x - 5
        }

        Text{
            id:rettotalVal
            x:retVal.x
            y:rettotalText.y
            text: live.retTotal
            horizontalAlignment: Text.AlignLeft
            font: Style.fMediumBold
            color: Style.clrText
            width: root.width - x - 5
        }

        Text{
            id:l1VoltText
            x:expButton.x + expButton.width + 20
            y:rettotalText.y + rettotalText.height
            text: "L1:"
            horizontalAlignment: Text.AlignRight
            font: Style.fMedium
            color: Style.clrText
            width: root.width / 2 - x - 5
        }

        Text{
            id:l1VoltVal
            x:retVal.x
            y: l1VoltText.y
            text: live.l1Volt
            horizontalAlignment: Text.AlignLeft
            font: Style.fMediumBold
            color: Style.clrText
            width: root.width - x - 5
        }

        Text{
            id:l2VoltText
            x:expButton.x + expButton.width + 20
            y:l1VoltText.y + l1VoltText.height
            text: "L2:"
            horizontalAlignment: Text.AlignRight
            font: Style.fMedium
            color: Style.clrText
            width: root.width / 2 - x - 5
        }

        Text{
            id:l2VoltVal
            x:retVal.x
            y:l2VoltText.y
            text: live.l2Volt
            horizontalAlignment: Text.AlignLeft
            font: Style.fMediumBold
            color: Style.clrText
            width: root.width - x - 5
        }

        Text{
            id:l3VoltText
            x:expButton.x + expButton.width + 20
            y:l2VoltText.y + l2VoltText.height
            text: "L3:"
            horizontalAlignment: Text.AlignRight
            font: Style.fMedium
            color: Style.clrText
            width: root.width / 2 - x - 5
        }

        Text{
            id:l3VoltVal
            x:retVal.x
            y:l3VoltText.y
            text: live.l3Volt
            horizontalAlignment: Text.AlignLeft
            font: Style.fMediumBold
            color: Style.clrText
            width: root.width - x - 5
        }

        Text{
            id:l1AmpText
            x:expButton.x + expButton.width + 20
            y:l3VoltText.y + l3VoltText.height
            text: "L1:"
            horizontalAlignment: Text.AlignRight
            font: Style.fMedium
            color: Style.clrText
            width: root.width / 2 - x - 5
        }

        Text{
            id:l1AmpVal
            x:retVal.x
            y: l1AmpText.y
            text: live.l1Amp
            horizontalAlignment: Text.AlignLeft
            font: Style.fMediumBold
            color: Style.clrText
            width: root.width - x - 5
        }

        Text{
            id:l2AmpText
            x:expButton.x + expButton.width + 20
            y:l1AmpText.y + l1AmpText.height
            text: "L2:"
            horizontalAlignment: Text.AlignRight
            font: Style.fMedium
            color: Style.clrText
            width: root.width / 2 - x - 5
        }

        Text{
            id:l2AmpVal
            x:retVal.x
            y:l2AmpText.y
            text: live.l2Amp
            horizontalAlignment: Text.AlignLeft
            font: Style.fMediumBold
            color: Style.clrText
            width: root.width - x - 5
        }

        Text{
            id:l3AmpText
            x:expButton.x + expButton.width + 20
            y:l2AmpText.y + l2AmpText.height
            text: "L3:"
            horizontalAlignment: Text.AlignRight
            font: Style.fMedium
            color: Style.clrText
            width: root.width / 2 - x - 5
        }

        Text{
            id:l3AmpVal
            x:retVal.x
            y:l3AmpText.y
            text: live.l3Amp
            horizontalAlignment: Text.AlignLeft
            font: Style.fMediumBold
            color: Style.clrText
            width: root.width - x - 5
        }

        Text{
            id:gasText
            x:expButton.x + expButton.width + 20
            y:l3AmpText.y + l3AmpText.height
            text: "Gas:"
            horizontalAlignment: Text.AlignRight
            font: Style.fMedium
            color: Style.clrText
            width: root.width / 2 - x - 5
        }

        Text{
            id:gasVal
            x:retVal.x
            y:gasText.y
            text: live.gas
            horizontalAlignment: Text.AlignLeft
            font: Style.fMediumBold
            color: Style.clrText
            width: root.width - x - 5
        }









    }
}
