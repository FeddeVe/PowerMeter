#include "dataitem.h"

DataItem::DataItem(int day, int month, int year, int hour, int weekday, int total, int gas, int totalreturned,int solarLifeTime, QObject *parent)
    : QObject{parent}
{
    this->m_day = day;
    this->m_month = month;
    this->m_year = year;
    this->m_hour = hour;
    this->m_weekday = weekday;
    this->m_total = total;
    this->m_gas = gas;
    this->m_totalReturned = totalreturned;
    this->m_solarLifeTime = solarLifeTime;
    this->gasUsed = 0;
    this->powerDeliverd = 0;
    this->powerReturnd = 0;
    this->solarResult = 0;
    this->powerUsed = 0;

}
