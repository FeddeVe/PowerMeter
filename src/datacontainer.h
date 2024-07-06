#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#include <QObject>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMutex>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "dataitem.h"


class DataContainer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool loaded READ loaded WRITE setLoaded NOTIFY loadedChanged);
    Q_PROPERTY(bool isLoading READ isLoading WRITE setIsLoading NOTIFY isLoadingChanged);

public:
    explicit DataContainer(QObject *parent = nullptr);

    QVector<DataItem*>items;

    Q_INVOKABLE void load();

    bool loaded() const;
    void setLoaded(bool newLoaded);

    bool isLoading() const;
    void setIsLoading(bool newIsLoading);

signals:

    void loadedChanged();
    void isLoadingChanged();

private:
    QNetworkAccessManager *network;
    QTimer *tmr;

    void loadData();
    bool m_loaded;
    int lastHourSync;
    bool m_isLoading;

public slots:
    void replyFinished(QNetworkReply *rep);
    void tmrTick();
};

#endif // DATACONTAINER_H
