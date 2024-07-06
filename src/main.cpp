// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>

#include "app_environment.h"
#include "import_qml_components_plugins.h"
#include "import_qml_plugins.h"

#include "live.h"
#include "datacontainer.h"
#include "hourmodel.h"
#include "weekmodel.h"
#include "monthmodel.h"
#include "headerbar.h"
#include "todaymodel.h"
#include "weekyearmodel.h"

int main(int argc, char *argv[])
{
    set_qt_environment();

    QGuiApplication app(argc, argv);

    Live *live = new Live();
    DataContainer *data = new DataContainer();
    hourModel *hourmodel = new hourModel(data);
    WeekModel *weekmodel = new WeekModel(data);
    MonthModel *monthmodel = new MonthModel(data);
    HeaderBar *headerBar = new HeaderBar(data);
    todayModel *todaymodel = new todayModel(data);
    WeekYearModel *weekYearModel = new WeekYearModel(data);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:Main/main.qml"_qs);
 engine.rootContext()->setContextProperty("dataManager", data);
    engine.rootContext()->setContextProperty("liveManager", live);
    engine.rootContext()->setContextProperty("hourManager", hourmodel);
    engine.rootContext()->setContextProperty("weekManager", weekmodel);
    engine.rootContext()->setContextProperty("monthManager", monthmodel);
    engine.rootContext()->setContextProperty("headerManager", headerBar);
    engine.rootContext()->setContextProperty("todayManager", todaymodel);
    engine.rootContext()->setContextProperty("weekYearManager", weekYearModel);

    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");

    engine.load(url);

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
