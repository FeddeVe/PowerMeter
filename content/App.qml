// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 6.2
import QtQuick.Window 2.2
import PowerMeter

Window {
    id: window
    width: Screen.width
    height: Screen.height

    visible: true
    title: "PowerMeter"

    Screen01 {
        id: mainScreen
        width:window.width
        height:window.height
    }

}

