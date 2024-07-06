#ifndef HEADERBAR_H
#define HEADERBAR_H

#include <QObject>
#include <QQmlEngine>

#include "datacontainer.h"

#define HOURS_WEEK 24*7
#define HOURS_MONTH 24*30
#define HOURS_YEAR 24*365


class HeaderBar : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int weekAVGUsed READ weekAVGUsed WRITE setWeekAVGUsed NOTIFY weekAVGUsedChanged);
    Q_PROPERTY(int weekUsed READ weekUsed WRITE setWeekUsed NOTIFY weekUsedChanged);
    Q_PROPERTY(int weekUsedMin READ weekUsedMin WRITE setWeekUsedMin NOTIFY weekUsedMinChanged);
    Q_PROPERTY(int weekUsedMax READ weekUsedMax WRITE setWeekUsedMax NOTIFY weekUsedMaxChanged);
    Q_PROPERTY(int weekAVGDelivered READ weekAVGDelivered WRITE setWeekAVGDelivered NOTIFY weekAVGDeliveredChanged);
    Q_PROPERTY(int weekDelivered READ weekDelivered WRITE setWeekDelivered NOTIFY weekDeliveredChanged);
    Q_PROPERTY(int weekDeliveredMin READ weekDeliveredMin WRITE setWeekDeliveredMin NOTIFY weekDeliveredMinChanged);
    Q_PROPERTY(int weekDeliveredMax READ weekDeliveredMax WRITE setWeekDeliveredMax NOTIFY weekDeliveredMaxChanged);
    Q_PROPERTY(float weekDeliverdPCT READ weekDeliverdPCT WRITE setWeekDeliverdPCT NOTIFY weekDeliverdPCTChanged);
    Q_PROPERTY(int weekAVGReturned READ weekAVGReturned WRITE setWeekAVGReturned NOTIFY weekAVGReturnedChanged);
    Q_PROPERTY(int weekReturnedMax READ weekReturnedMax WRITE setWeekReturnedMax NOTIFY weekReturnedMaxChanged);
    Q_PROPERTY(int weekReturnedMin READ weekReturnedMin WRITE setWeekReturnedMin NOTIFY weekReturnedMinChanged);
    Q_PROPERTY(int weekReturned READ weekReturned WRITE setWeekReturned NOTIFY weekReturnedChanged);
    Q_PROPERTY(float weekReturnedPCT READ weekReturnedPCT WRITE setWeekReturnedPCT NOTIFY weekReturnedPCTChanged);
    Q_PROPERTY(int weekAVGResult READ weekAVGResult WRITE setWeekAVGResult NOTIFY weekAVGResultChanged);
    Q_PROPERTY(int weekResult READ weekResult WRITE setWeekResult NOTIFY weekResultChanged);
    Q_PROPERTY(int weekResultMax READ weekResultMax WRITE setWeekResultMax NOTIFY weekResultMaxChanged);
    Q_PROPERTY(int weekResultMin READ weekResultMin WRITE setWeekResultMin NOTIFY weekResultMinChanged);
    Q_PROPERTY(float weekResultPCT READ weekResultPCT WRITE setWeekResultPCT NOTIFY weekResultPCTChanged);
    Q_PROPERTY(int weekAVGGas READ weekAVGGas WRITE setWeekAVGGas NOTIFY weekAVGGasChanged);
    Q_PROPERTY(int weekGas READ weekGas WRITE setWeekGas NOTIFY weekGasChanged);
    Q_PROPERTY(int weekGasMax READ weekGasMax WRITE setWeekGasMax NOTIFY weekGasMaxChanged);
    Q_PROPERTY(int weekGasMin READ weekGasMin WRITE setWeekGasMin NOTIFY weekGasMinChanged);
    Q_PROPERTY(float weekGasPCT READ weekGasPCT WRITE setWeekGasPCT NOTIFY weekGasPCTChanged);
    Q_PROPERTY(int weeksolar READ weeksolar WRITE setWeeksolar NOTIFY weeksolarChanged);
    Q_PROPERTY(int weeksolarMax READ weeksolarMax WRITE setWeeksolarMax NOTIFY weeksolarMaxChanged);
    Q_PROPERTY(int weeksolarMin READ weeksolarMin WRITE setWeeksolarMin NOTIFY weeksolarMinChanged);
    Q_PROPERTY(float weeksolarPCT READ weeksolarPCT WRITE setWeeksolarPCT NOTIFY weeksolarPCTChanged);
     Q_PROPERTY(int weekAVGsolar READ weekAVGsolar WRITE setWeekAVGsolar NOTIFY weekAVGsolarChanged);

    Q_PROPERTY(int monthAVGUsed READ monthAVGUsed WRITE setmonthAVGUsed NOTIFY monthAVGUsedChanged);
    Q_PROPERTY(int monthUsed READ monthUsed WRITE setmonthUsed NOTIFY monthUsedChanged);
    Q_PROPERTY(int monthUsedMin READ monthUsedMin WRITE setmonthUsedMin NOTIFY monthUsedMinChanged);
    Q_PROPERTY(int monthUsedMax READ monthUsedMax WRITE setmonthUsedMax NOTIFY monthUsedMaxChanged);
    Q_PROPERTY(int monthAVGDelivered READ monthAVGDelivered WRITE setmonthAVGDelivered NOTIFY monthAVGDeliveredChanged);
    Q_PROPERTY(int monthDelivered READ monthDelivered WRITE setmonthDelivered NOTIFY monthDeliveredChanged);
    Q_PROPERTY(int monthDeliveredMin READ monthDeliveredMin WRITE setmonthDeliveredMin NOTIFY monthDeliveredMinChanged);
    Q_PROPERTY(int monthDeliveredMax READ monthDeliveredMax WRITE setmonthDeliveredMax NOTIFY monthDeliveredMaxChanged);
    Q_PROPERTY(int monthAVGReturned READ monthAVGReturned WRITE setmonthAVGReturned NOTIFY monthAVGReturnedChanged);
    Q_PROPERTY(int monthReturnedMax READ monthReturnedMax WRITE setmonthReturnedMax NOTIFY monthReturnedMaxChanged);
    Q_PROPERTY(int monthReturnedMin READ monthReturnedMin WRITE setmonthReturnedMin NOTIFY monthReturnedMinChanged);
    Q_PROPERTY(int monthReturned READ monthReturned WRITE setmonthReturned NOTIFY monthReturnedChanged);
     Q_PROPERTY(int monthAVGResult READ monthAVGResult WRITE setmonthAVGResult NOTIFY monthAVGResultChanged);
    Q_PROPERTY(int monthResult READ monthResult WRITE setmonthResult NOTIFY monthResultChanged);
    Q_PROPERTY(int monthResultMax READ monthResultMax WRITE setmonthResultMax NOTIFY monthResultMaxChanged);
    Q_PROPERTY(int monthResultMin READ monthResultMin WRITE setmonthResultMin NOTIFY monthResultMinChanged);
     Q_PROPERTY(int monthAVGGas READ monthAVGGas WRITE setmonthAVGGas NOTIFY monthAVGGasChanged);
    Q_PROPERTY(int monthGas READ monthGas WRITE setmonthGas NOTIFY monthGasChanged);
    Q_PROPERTY(int monthGasMax READ monthGasMax WRITE setmonthGasMax NOTIFY monthGasMaxChanged);
    Q_PROPERTY(int monthGasMin READ monthGasMin WRITE setmonthGasMin NOTIFY monthGasMinChanged);
    Q_PROPERTY(int monthsolar READ monthsolar WRITE setmonthsolar NOTIFY monthsolarChanged);
    Q_PROPERTY(int monthsolarMax READ monthsolarMax WRITE setmonthsolarMax NOTIFY monthsolarMaxChanged);
    Q_PROPERTY(int monthsolarMin READ monthsolarMin WRITE setmonthsolarMin NOTIFY monthsolarMinChanged);
    Q_PROPERTY(int monthAVGsolar READ monthAVGsolar WRITE setmonthAVGsolar NOTIFY monthAVGsolarChanged);

    Q_PROPERTY(int yearAVGUsed READ yearAVGUsed WRITE setyearAVGUsed NOTIFY yearAVGUsedChanged);
    Q_PROPERTY(int yearUsed READ yearUsed WRITE setyearUsed NOTIFY yearUsedChanged);
    Q_PROPERTY(int yearUsedMin READ yearUsedMin WRITE setyearUsedMin NOTIFY yearUsedMinChanged);
    Q_PROPERTY(int yearUsedMax READ yearUsedMax WRITE setyearUsedMax NOTIFY yearUsedMaxChanged);
    Q_PROPERTY(int yearAVGDelivered READ yearAVGDelivered WRITE setyearAVGDelivered NOTIFY yearAVGDeliveredChanged);
    Q_PROPERTY(int yearDelivered READ yearDelivered WRITE setyearDelivered NOTIFY yearDeliveredChanged);
    Q_PROPERTY(int yearDeliveredMin READ yearDeliveredMin WRITE setyearDeliveredMin NOTIFY yearDeliveredMinChanged);
    Q_PROPERTY(int yearDeliveredMax READ yearDeliveredMax WRITE setyearDeliveredMax NOTIFY yearDeliveredMaxChanged);
    Q_PROPERTY(int yearAVGReturned READ yearAVGReturned WRITE setyearAVGReturned NOTIFY yearAVGReturnedChanged);
    Q_PROPERTY(int yearReturnedMax READ yearReturnedMax WRITE setyearReturnedMax NOTIFY yearReturnedMaxChanged);
    Q_PROPERTY(int yearReturnedMin READ yearReturnedMin WRITE setyearReturnedMin NOTIFY yearReturnedMinChanged);
    Q_PROPERTY(int yearReturned READ yearReturned WRITE setyearReturned NOTIFY yearReturnedChanged);
    Q_PROPERTY(int yearAVGResult READ yearAVGResult WRITE setyearAVGResult NOTIFY yearAVGResultChanged);
    Q_PROPERTY(int yearResult READ yearResult WRITE setyearResult NOTIFY yearResultChanged);
    Q_PROPERTY(int yearResultMax READ yearResultMax WRITE setyearResultMax NOTIFY yearResultMaxChanged);
    Q_PROPERTY(int yearResultMin READ yearResultMin WRITE setyearResultMin NOTIFY yearResultMinChanged);
    Q_PROPERTY(int yearAVGGas READ yearAVGGas WRITE setyearAVGGas NOTIFY yearAVGGasChanged);
    Q_PROPERTY(int yearGas READ yearGas WRITE setyearGas NOTIFY yearGasChanged);
    Q_PROPERTY(int yearGasMax READ yearGasMax WRITE setyearGasMax NOTIFY yearGasMaxChanged);
    Q_PROPERTY(int yearGasMin READ yearGasMin WRITE setyearGasMin NOTIFY yearGasMinChanged);
    Q_PROPERTY(int yearsolar READ yearsolar WRITE setyearsolar NOTIFY yearsolarChanged);
    Q_PROPERTY(int yearsolarMax READ yearsolarMax WRITE setyearsolarMax NOTIFY yearsolarMaxChanged);
    Q_PROPERTY(int yearsolarMin READ yearsolarMin WRITE setyearsolarMin NOTIFY yearsolarMinChanged);
    Q_PROPERTY(int yearAVGsolar READ yearAVGsolar WRITE setyearAVGsolar NOTIFY yearAVGsolarChanged);


public:
    explicit HeaderBar(DataContainer *data, QObject *parent = nullptr);


    int weekAVGDelivered() const;
    void setWeekAVGDelivered(int newWeekAVGDelivered);

    int weekDelivered() const;
    void setWeekDelivered(int newWeekDelivered);

    int weekAVGReturned() const;
    void setWeekAVGReturned(int newWeekAVGReturned);

    int weekReturned() const;
    void setWeekReturned(int newWeekReturned);

    int weekAVGResult() const;
    void setWeekAVGResult(int newWeekAVGResult);

    int weekResult() const;
    void setWeekResult(int newWeekResult);

    int weekAVGGas() const;
    void setWeekAVGGas(int newWeekAVGGas);

    int weekGas() const;
    void setWeekGas(int newWeekGas);

    int weekDeliveredMin() const;
    void setWeekDeliveredMin(int newWeekDeliveredMin);

    int weekDeliveredMax() const;
    void setWeekDeliveredMax(int newWeekDeliveredMax);

    int weekReturnedMax() const;
    void setWeekReturnedMax(int newWeekReturnedMax);

    int weekReturnedMin() const;
    void setWeekReturnedMin(int newWeekReturnedMin);

    int weekResultMax() const;
    void setWeekResultMax(int newWeekResultMax);

    int weekResultMin() const;
    void setWeekResultMin(int newWeekResultMin);

    int weekGasMax() const;
    void setWeekGasMax(int newWeekGasMax);

    int weekGasMin() const;
    void setWeekGasMin(int newWeekGasMin);

    float weekDeliverdPCT() const;
    void setWeekDeliverdPCT(float newWeekDeliverdPCT);

    float weekReturnedPCT() const;
    void setWeekReturnedPCT(float newWeekReturnedPCT);

    float weekResultPCT() const;
    void setWeekResultPCT(float newWeekResultPCT);

    float weekGasPCT() const;
    void setWeekGasPCT(float newWeekGasPCT);

    int monthAVGDelivered() const;
    void setmonthAVGDelivered(int newMonthAVGDelivered);

    int monthDelivered() const;
    void setmonthDelivered(int newMonthDelivered);

    int monthDeliveredMin() const;
    void setmonthDeliveredMin(int newMonthDeliveredMin);

    int monthDeliveredMax() const;
    void setmonthDeliveredMax(int newMonthDeliveredMax);

    int monthAVGReturned() const;
    void setmonthAVGReturned(int newMonthAVGReturned);

    int monthReturnedMax() const;
    void setmonthReturnedMax(int newMonthReturnedMax);

    int monthReturnedMin() const;
    void setmonthReturnedMin(int newMonthReturnedMin);

    int monthReturned() const;
    void setmonthReturned(int newMonthReturned);

    int monthAVGResult() const;
    void setmonthAVGResult(int newMonthAVGResult);

    int monthResultMax() const;
    void setmonthResultMax(int newMonthResultMax);

    int monthResultMin() const;
    void setmonthResultMin(int newMonthResultMin);

    int monthAVGGas() const;
    void setmonthAVGGas(int newMonthAVGGas);

    int monthResult() const;
    void setmonthResult(int newMonthResult);

    int monthGas() const;
    void setmonthGas(int newMonthGas);

    int monthGasMax() const;
    void setmonthGasMax(int newMonthGasMax);

    int monthGasMin() const;
    void setmonthGasMin(int newMonthGasMin);

    int yearAVGDelivered() const;
    void setyearAVGDelivered(int newYearAVGDelivered);

    int yearDelivered() const;
    void setyearDelivered(int newYearDelivered);

    int yearDeliveredMin() const;
    void setyearDeliveredMin(int newYearDeliveredMin);

    int yearDeliveredMax() const;
    void setyearDeliveredMax(int newYearDeliveredMax);

    int yearAVGReturned() const;
    void setyearAVGReturned(int newYearAVGReturned);

    int yearReturnedMax() const;
    void setyearReturnedMax(int newYearReturnedMax);

    int yearReturnedMin() const;
    void setyearReturnedMin(int newYearReturnedMin);

    int yearReturned() const;
    void setyearReturned(int newYearReturned);

    int yearAVGResult() const;
    void setyearAVGResult(int newYearAVGResult);

    int yearResult() const;
    void setyearResult(int newYearResult);

    int yearResultMax() const;
    void setyearResultMax(int newYearResultMax);

    int yearResultMin() const;
    void setyearResultMin(int newYearResultMin);

    int yearAVGGas() const;
    void setyearAVGGas(int newYearAVGGas);

    int yearGas() const;
    void setyearGas(int newYearGas);

    int yearGasMax() const;
    void setyearGasMax(int newYearGasMax);

    int yearGasMin() const;
    void setyearGasMin(int newYearGasMin);

    int weeksolar() const;
    void setWeeksolar(int newWeeksolar);

    int weeksolarMax() const;
    void setWeeksolarMax(int newWeeksolarMax);

    int weeksolarMin() const;
    void setWeeksolarMin(int newWeeksolarMin);

    float weeksolarPCT() const;
    void setWeeksolarPCT(float newWeeksolarPCT);

    int weekAVGsolar() const;
    void setWeekAVGsolar(int newWeekAVGsolar);

    int monthsolar() const;
    void setmonthsolar(int newMonthsolar);

    int monthsolarMax() const;
    void setmonthsolarMax(int newMonthsolarMax);

    int monthsolarMin() const;
    void setmonthsolarMin(int newMonthsolarMin);

    int monthAVGsolar() const;
    void setmonthAVGsolar(int newMonthAVGsolar);

    int yearsolar() const;
    void setyearsolar(int newYearsolar);

    int yearsolarMax() const;
    void setyearsolarMax(int newYearsolarMax);

    int yearsolarMin() const;
    void setyearsolarMin(int newYearsolarMin);

    int yearAVGsolar() const;
    void setyearAVGsolar(int newYearAVGsolar);

    int weekAVGUsed() const;
    void setWeekAVGUsed(int newWeekAVGUsed);

    int weekUsed() const;
    void setWeekUsed(int newWeekUsed);

    int weekUsedMin() const;
    void setWeekUsedMin(int newWeekUsedMin);

    int weekUsedMax() const;
    void setWeekUsedMax(int newWeekUsedMax);

    int monthAVGUsed() const;
    void setmonthAVGUsed(int newMonthAVGUsed);

    int monthUsed() const;
    void setmonthUsed(int newMonthUsed);

    int monthUsedMin() const;
    void setmonthUsedMin(int newMonthUsedMin);

    int monthUsedMax() const;
    void setmonthUsedMax(int newMonthUsedMax);

    int yearAVGUsed() const;
    void setyearAVGUsed(int newYearAVGUsed);

    int yearUsed() const;
    void setyearUsed(int newYearUsed);

    int yearUsedMin() const;
    void setyearUsedMin(int newYearUsedMin);

    int yearUsedMax() const;
    void setyearUsedMax(int newYearUsedMax);

private:
    DataContainer *m_dataContainer;




    int m_weekAVGDelivered;

    int m_weekDelivered;

    int m_weekAVGReturned;

    int m_weekReturned;

    int m_weekAVGResult;

    int m_weekResult;

    int m_weekAVGGas;

    int m_weekGas;

    int m_weekDeliveredMin;

    int m_weekDeliveredMax;

    int m_weekReturnedMax;

    int m_weekReturnedMin;

    int m_weekResultMax;

    int m_weekResultMin;

    int m_weekGasMax;

    int m_weekGasMin;

    float m_weekDeliverdPCT;

    float m_weekReturnedPCT;

    float m_weekResultPCT;

    float m_weekGasPCT;

    int m_monthAVGDelivered;

    int m_monthDelivered;

    int m_monthDeliveredMin;

    int m_monthDeliveredMax;

    int m_monthAVGReturned;

    int m_monthReturnedMax;

    int m_monthReturnedMin;

    int m_monthReturned;

    int m_monthAVGResult;

    int m_monthResultMax;

    int m_monthResultMin;

    int m_monthAVGGas;

    int m_monthResult;

    int m_monthGas;

    int m_monthGasMax;

    int m_monthGasMin;

    int m_yearAVGDelivered;

    int m_yearDelivered;

    int m_yearDeliveredMin;

    int m_yearDeliveredMax;

    int m_yearAVGReturned;

    int m_yearReturnedMax;

    int m_yearReturnedMin;

    int m_yearReturned;

    int m_yearAVGResult;

    int m_yearResult;

    int m_yearResultMax;

    int m_yearResultMin;

    int m_yearAVGGas;

    int m_yearGas;

    int m_yearGasMax;

    int m_yearGasMin;

    int m_weeksolar;

    int m_weeksolarMax;

    int m_weeksolarMin;

    float m_weeksolarPCT;

    int m_weekAVGsolar;

    int m_monthsolar;

    int m_monthsolarMax;

    int m_monthsolarMin;

    int m_monthAVGsolar;

    int m_yearsolar;

    int m_yearsolarMax;

    int m_yearsolarMin;

    int m_yearAVGsolar;

    int m_weekAVGUsed;

    int m_weekUsed;

    int m_weekUsedMin;

    int m_weekUsedMax;

    int m_monthAVGUsed;

    int m_monthUsed;

    int m_monthUsedMin;

    int m_monthUsedMax;

    int m_yearAVGUsed;

    int m_yearUsed;

    int m_yearUsedMin;

    int m_yearUsedMax;

signals:

    void weekAVGDeliveredChanged();

    void weekDeliveredChanged();

    void weekAVGReturnedChanged();

    void weekReturnedChanged();

    void weekAVGResultChanged();

    void weekResultChanged();

    void weekAVGGasChanged();

    void weekGasChanged();

    void weekDeliveredMinChanged();

    void weekDeliveredMaxChanged();

    void weekReturnedMaxChanged();

    void weekReturnedMinChanged();

    void weekResultMaxChanged();

    void weekResultMinChanged();

    void weekGasMaxChanged();

    void weekGasMinChanged();

    void weekDeliverdPCTChanged();

    void weekReturnedPCTChanged();

    void weekResultPCTChanged();

    void weekGasPCTChanged();

    void monthAVGDeliveredChanged();

    void monthDeliveredChanged();

    void monthDeliveredMinChanged();

    void monthDeliveredMaxChanged();

    void monthAVGReturnedChanged();

    void monthReturnedMaxChanged();

    void monthReturnedMinChanged();

    void monthReturnedChanged();

    void monthAVGResultChanged();

    void monthResultMaxChanged();

    void monthResultMinChanged();

    void monthAVGGasChanged();

    void monthResultChanged();

    void monthGasChanged();

    void monthGasMaxChanged();

    void monthGasMinChanged();

    void yearAVGDeliveredChanged();

    void yearDeliveredChanged();

    void yearDeliveredMinChanged();

    void yearDeliveredMaxChanged();

    void yearAVGReturnedChanged();

    void yearReturnedMaxChanged();

    void yearReturnedMinChanged();

    void yearReturnedChanged();

    void yearAVGResultChanged();

    void yearResultChanged();

    void yearResultMaxChanged();

    void yearResultMinChanged();

    void yearAVGGasChanged();

    void yearGasChanged();

    void yearGasMaxChanged();

    void yearGasMinChanged();

    void weeksolarChanged();

    void weeksolarMaxChanged();

    void weeksolarMinChanged();

    void weeksolarPCTChanged();

    void weekAVGsolarChanged();

    void monthsolarChanged();

    void monthsolarMaxChanged();

    void monthsolarMinChanged();

    void monthAVGsolarChanged();

    void yearsolarChanged();

    void yearsolarMaxChanged();

    void yearsolarMinChanged();

    void yearAVGsolarChanged();

    void weekAVGUsedChanged();

    void weekUsedChanged();

    void weekUsedMinChanged();

    void weekUsedMaxChanged();

    void monthAVGUsedChanged();

    void monthUsedChanged();

    void monthUsedMinChanged();

    void monthUsedMaxChanged();

    void yearAVGUsedChanged();

    void yearUsedChanged();

    void yearUsedMinChanged();

    void yearUsedMaxChanged();

public slots:
    void loadModel();

};

#endif // HEADERBAR_H
