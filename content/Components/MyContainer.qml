import QtQuick 2.15
import QtQuick.Controls 2.15
import PowerMeter 1.0




    Rectangle{
        id: root
        width: Constants.width
        height: Constants.height
        x:0
        y:0

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
        radius: 10
        border.color: Style.grey
        border.width: 1
        clip:true
    }

