

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Window 2.0
import PowerMeter
import "Components/"

Rectangle {
    id:root
    x:0
    y:0
    height: Constants.height
    width: Constants.width

    Main{
        x:0;
        y:0
        height: root.height
        width: root.width
    }

}
