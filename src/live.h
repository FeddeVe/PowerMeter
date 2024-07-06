#ifndef LIVE_H
#define LIVE_H

#include <QObject>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMutex>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>

class Live : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString delivered READ delivered NOTIFY deliveredChanged);
    Q_PROPERTY(QString liveVal READ liveVal NOTIFY liveValChanged);
    Q_PROPERTY(QString returned READ returned NOTIFY returnedChanged);
    Q_PROPERTY(QString result READ result NOTIFY resultChanged);
    Q_PROPERTY(QString t1 READ t1 NOTIFY t1Changed);
    Q_PROPERTY(QString t2 READ t2 NOTIFY t2Changed);
    Q_PROPERTY(QString total READ total NOTIFY totalChanged);
    Q_PROPERTY(QString retT1 READ retT1 NOTIFY retT1Changed);
    Q_PROPERTY(QString retT2 READ retT2 NOTIFY retT2Changed);
    Q_PROPERTY(QString retTotal READ retTotal NOTIFY retTotalChanged);
    Q_PROPERTY(QString l1Volt READ l1Volt NOTIFY l1VoltChanged);
    Q_PROPERTY(QString l2Volt READ l2Volt NOTIFY l2VoltChanged);
    Q_PROPERTY(QString l3Volt READ l3Volt NOTIFY l3VoltChanged);
    Q_PROPERTY(QString l1Amp READ l1Amp NOTIFY l1AmpChanged);
    Q_PROPERTY(QString l2Amp READ l2Amp NOTIFY l2AmpChanged);
    Q_PROPERTY(QString l3Amp READ l3Amp NOTIFY l3AmpChanged);
    Q_PROPERTY(QString gas READ gas NOTIFY gasChanged);
    Q_PROPERTY(QString solar READ solar NOTIFY solarChanged);



public:
    explicit Live(QObject *parent = nullptr);

    QString delivered() const;
    void setDelivered(const int32_t &newDelivered);

    QString returned() const;
    void setReturned(const int32_t &newReturned);

    QString result() const;
    void setResult(const int &newResult);

    QString t1() const;
    void setT1(const uint32_t &newT1);

    QString t2() const;
    void setT2(const uint32_t &newT2);

    QString total() const;
    void setTotal(const uint32_t &newTotal);

    QString retT1() const;
    void setRetT1(const uint32_t &newRetT1);

    QString retT2() const;
    void setRetT2(const uint32_t &newRetT2);

    QString retTotal() const;
    void setRetTotal(const uint32_t &newRetTotal);

    QString l1Volt() const;
    void setL1Volt(const uint32_t &newL1Volt);

    QString l2Volt() const;
    void setL2Volt(const uint32_t &newL2Volt);

    QString l3Volt() const;
    void setL3Volt(const uint32_t &newL3Volt);

    QString l1Amp() const;
    void setL1Amp(const uint32_t &newL1Amp);

    QString l2Amp() const;
    void setL2Amp(const uint32_t &newL2Amp);

    QString l3Amp() const;
    void setL3Amp(const uint32_t &newL3Amp);

    QString gas() const;
    void setGas(const uint32_t &newGas);

    QString liveVal() const;
    void setLiveVal(const int &newLiveVal);

    QString solar() const;
    void setSolar(const uint32_t &newSolar);

signals:

    void deliveredChanged();
    void returnedChanged();

    void resultChanged();

    void t1Changed();

    void t2Changed();

    void totalChanged();

    void retT1Changed();

    void retT2Changed();

    void retTotalChanged();

    void l1VoltChanged();

    void l2VoltChanged();

    void l3VoltChanged();

    void l1AmpChanged();

    void l2AmpChanged();

    void l3AmpChanged();

    void gasChanged();

    void liveValChanged();

    void solarChanged();

private:
    int32_t m_delivered;
    int32_t flatten_delivered[10];
    int flatten_delivered_index;
    uint32_t m_returned;
    int m_result;
    uint32_t m_t1;
    uint32_t m_t2;
    uint32_t m_total;
    uint32_t m_retT1;
    uint32_t m_retT2;
    uint32_t m_retTotal;
    uint32_t m_l1Volt;
    uint32_t m_l2Volt;
    uint32_t m_l3Volt;
    uint32_t m_l1Amp;
    uint32_t m_l2Amp;
    uint32_t m_l3Amp;
    uint32_t m_gas;

    float raw_deliverd;
    float raw_returned;
    float raw_total;
    float des_deliverd;
    float des_returned;
    float des_total;
    float delta_delivered;
    float delta_returned;
    float delta_total;

    QTimer *loadTimer;
    QTimer *AnimTimer;

    QNetworkAccessManager *network;
    QMutex m;

    bool firstShot;

    int m_liveVal;

    uint32_t m_solar;

public slots:
    void loadTimerTick();
    void animTimerTick();
    void replyFinished(QNetworkReply *rep);



};

#endif // LIVE_H
