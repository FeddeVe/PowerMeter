#ifndef DATAITEM_H
#define DATAITEM_H

#include <QObject>

class DataItem : public QObject
{
    Q_OBJECT



public:
    explicit DataItem(int day, int month, int year, int hour, int weekday, int total, int gas, int totalreturned, int solarLifeTime, QObject *parent = nullptr);

    int m_day;
    int m_month;
    int m_year;
    int m_hour;
    int m_weekday;
    int m_total;
    int m_gas;
    int m_totalReturned;
    int m_solarLifeTime;
    int gasUsed;
    int powerDeliverd;
    int powerReturnd;
    int solarResult;
    int powerUsed;

signals:

};

#endif // DATAITEM_H
