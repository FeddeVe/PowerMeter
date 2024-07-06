import QtQuick 2.15
import QtQuick.Controls 2.15
import PowerMeter 1.0
import "Components/"

Rectangle {

    id: root
    width: 480
    height: Constants.height

    color: Style.gray

    ScrollView {
        id: scrView
        x: 0
        y: 0
        width: root.width
        height: root.height
        contentHeight: monthTable.y + monthTable.height

        Text {
            id: header
            text: "PowerMeter"
            horizontalAlignment: Text.AlignHCenter
            x: 5
            y: 5
            height: 32
            width: root.width
            font: Style.fHugeBold
            color: Style.clrText
        }

        Image{
            visible: !dataManager.isLoading
            id:refImage
            source: "images/refresh-page-option.png"
            fillMode: Image.PreserveAspectFit
            x: root.width - width - 10
            y: 10
            height: 24
            width: 24
            MouseArea{
                anchors.fill: parent;
                onClicked: dataManager.load()
            }
        }

        BusyIndicator{
            visible: dataManager.isLoading
            id: busy
            x: refImage.x - width/4
            y: refImage.y -height/4
            height: refImage.height * 1.5
            width: refImage.width * 1.5
        }




        Live {
            id: liveBox
            x: 10
            y: header.y + header.height + 10
            width: root.width - x * 2
            expanded: false
            onHeightChanged: {

             //   hourTable.y = liveBox.y + liveBox.height
              //  console.log(hourTable.y);
            }
        }

        HeaderBar{
            id: weekBar
            x:10
            y:liveBox.y + liveBox.height + 10
            width: root.width - x*2
            label: "Week"
            deliverdAVG: headerManager.weekAVGDelivered
            deliveredCurrent: headerManager.weekDelivered
            deliverdMax:headerManager.weekDeliveredMax
            deliveredMin: headerManager.weekDeliveredMin

            returnedAVG: headerManager.weekAVGReturned
            returnedCurrent: headerManager.weekReturned
            returnedMax:headerManager.weekReturnedMax
            returnedMin: headerManager.weekReturnedMin

            resultAVG:  headerManager.weekAVGResult
            resultCurrent: headerManager.weekResult
            resultMax:headerManager.weekResultMax
            resultMin: headerManager.weekResultMin

            gasAvg:  headerManager.weekAVGGas
            gasCurrent: headerManager.weekGas
            gasMax:headerManager.weekGasMax
            gasMin: headerManager.weekGasMin

            solarAvg:  headerManager.weekAVGsolar
            solarCurrent: headerManager.weeksolar
            solarMax:headerManager.weeksolarMax
            solarMin: headerManager.weeksolarMin

            usedAvg: headerManager.weekAVGUsed
            usedCurrent: headerManager.weekUsed
            usedMax : headerManager.weekUsedMax
            usedMin : headerManager.weekUsedMin

        }

        HeaderBar{
            id: monthBar
            x:10
            y:weekBar.y + weekBar.height + 10
            width: root.width - x*2
            label: "Month"
            deliverdAVG: headerManager.monthAVGDelivered
            deliveredCurrent: headerManager.monthDelivered
            deliverdMax:headerManager.monthDeliveredMax
            deliveredMin: headerManager.monthDeliveredMin

            returnedAVG: headerManager.monthAVGReturned
            returnedCurrent: headerManager.monthReturned
            returnedMax:headerManager.monthReturnedMax
            returnedMin: headerManager.monthReturnedMin

            resultAVG:  headerManager.monthAVGResult
            resultCurrent: headerManager.monthResult
            resultMax:headerManager.monthResultMax
            resultMin: headerManager.monthResultMin

            gasAvg:  headerManager.monthAVGGas
            gasCurrent: headerManager.monthGas
            gasMax:headerManager.monthGasMax
            gasMin: headerManager.monthGasMin

            solarAvg:  headerManager.monthAVGsolar
            solarCurrent: headerManager.monthsolar
            solarMax:headerManager.monthsolarMax
            solarMin: headerManager.monthsolarMin

            usedAvg: headerManager.monthAVGUsed
            usedCurrent: headerManager.monthUsed
            usedMax : headerManager.monthUsedMax
            usedMin : headerManager.monthUsedMin

        }


        HeaderBar{
            id: yearBar
            x:10
            y:monthBar.y + monthBar.height + 10
            width: root.width - x*2
            label: "Year"
            deliverdAVG: headerManager.yearAVGDelivered
            deliveredCurrent: headerManager.yearDelivered
            deliverdMax:headerManager.yearDeliveredMax
            deliveredMin: headerManager.yearDeliveredMin

            returnedAVG: headerManager.yearAVGReturned
            returnedCurrent: headerManager.yearReturned
            returnedMax:headerManager.yearReturnedMax
            returnedMin: headerManager.yearReturnedMin

            resultAVG:  headerManager.yearAVGResult
            resultCurrent: headerManager.yearResult
            resultMax:headerManager.yearResultMax
            resultMin: headerManager.yearResultMin

            gasAvg:  headerManager.yearAVGGas
            gasCurrent: headerManager.yearGas
            gasMax:headerManager.yearGasMax
            gasMin: headerManager.yearGasMin

            solarAvg:  headerManager.yearAVGsolar
            solarCurrent: headerManager.yearsolar
            solarMax:headerManager.yearsolarMax
            solarMin: headerManager.yearsolarMin

            usedAvg: headerManager.yearAVGUsed
            usedCurrent: headerManager.yearUsed
            usedMax : headerManager.yearUsedMax
            usedMin : headerManager.yearUsedMin

        }

        /*
        HeaderBar{
            id: monthBar
            x:10
            y:weekBar.y + weekBar.height + 10
            width: root.width - x*2
            label: "MONTH"
        }

        HeaderBar{
            id: yearBar
            x:10
            y:monthBar.y + monthBar.height + 10
            width: root.width - x*2
            label: "YEAR"
        }

        */

        HourTable {
            id: todayTable
            x: 10
            y: yearBar.y + yearBar.height + 10
            width: root.width - x * 2
            height: 400
            dataModel: todayManager
            tableName: "Today"
        }

        HourTable {
            id: hourTable
            x: 10
            y: todayTable.y + todayTable.height + 10
            width: root.width - x * 2
            height: 400
            dataModel: hourManager
            tableName: "7 days AVG"
        }

        HourTable {
            id: weekTable
            x: 10
            y: hourTable.y + hourTable.height + 10
            width: root.width - x * 2
            height: 400
            dataModel: weekManager
            tableName: "Days"

        }

        HourTable {
            id: weekYearTable
            x: 10
            y: weekTable.y + weekTable.height + 10
            width: root.width - x * 2
            height: 400
            dataModel: weekYearManager
            tableName: "Weeks"

        }

        HourTable {
            id: monthTable
            x: 10
            y: weekYearTable.y + weekYearTable.height + 10
            width: root.width - x * 2
            height: 400
            dataModel: monthManager
            tableName: "Month"

        }

        Rectangle{
            visible: dataManager.isLoading
            id:loadingRect
            x: 10
            y: liveBox.y + liveBox.height + 10
            height: scrView.contentHeight - y
            width: root.width - x*2
            color: Style.halfLight
        }
    }
}
