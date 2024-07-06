#ifndef WEEKMODEL_H
#define WEEKMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QMutex>
#include <QQmlEngine>

#include "modelitem.h"
#include "datacontainer.h"

class WeekModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged);
    Q_PROPERTY(int pwrMax READ pwrMax WRITE setPwrMax NOTIFY pwrMaxChanged);
    Q_PROPERTY(int pwrMin READ pwrMin WRITE setPwrMin NOTIFY pwrMinChanged);
    Q_PROPERTY(int gasMax READ gasMax WRITE setGasMax NOTIFY gasMaxChanged);
    Q_PROPERTY(int gasMin READ gasMin WRITE setGasMin NOTIFY gasMinChanged);
    Q_PROPERTY(int pwrMode READ pwrMode WRITE setPwrMode NOTIFY pwrModeChanged);
    Q_PROPERTY(QString pwrModeText READ pwrModeText WRITE setPwrModeText NOTIFY pwrModeTextChanged);

public:

    enum RoleNames {
        JobNoRole = Qt::UserRole,
        TitleRole = Qt::UserRole+2,
        ClientRole = Qt::UserRole+3,
        IDRole = Qt::UserRole + 4,
        DateRole = Qt::UserRole + 5,
        StartDateRole = Qt::UserRole + 6,
        PickDateRole = Qt::UserRole + 7,
        StatusColorRole = Qt::UserRole + 8,
    };

    explicit WeekModel(DataContainer *data, QObject *parent = nullptr);

    //Q_INVOKABLE void loadModel();
    Q_INVOKABLE modelItem *get(int row) const;

    int count() const;

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    int pwrMax() const;
    void setPwrMax(int newPwrMax);

    int pwrMin() const;
    void setPwrMin(int newPwrMin);

    int gasMax() const;
    void setGasMax(int newGasMax);

    int gasMin() const;
    void setGasMin(int newGasMin);

    int pwrMode() const;
    void setPwrMode(int newPwrMode);

    QString pwrModeText() const;
    void setPwrModeText(const QString &newPwrModeText);

    void setCount(int newCount);

protected:
    // return the roles mapping to be used by QML
    virtual QHash<int, QByteArray> roleNames() const override;
private:
    DataContainer *dataContainer;
    QMutex m;
    QVector<modelItem*>m_data;
    QVector<DataItem*>m_dataItems;
    QHash<int, QByteArray> m_roleNames;

    int m_pwrMax;

    int m_pwrMin;

    int m_gasMax;

    int m_gasMin;

    int m_pwrMode;

    void setMinMax();
    QString getDay(int dayOfWeek);

    QString m_pwrModeText;



    int m_count;

signals:
    void countChanged();

    void pwrMaxChanged();

    void pwrMinChanged();

    void gasMaxChanged();

    void gasMinChanged();

    void pwrModeChanged();

    void pwrModeTextChanged();

public slots:
    void loadModel();
};

#endif // WEEKMODEL_H
