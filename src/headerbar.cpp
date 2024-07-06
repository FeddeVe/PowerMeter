#include "headerbar.h"

HeaderBar::HeaderBar(DataContainer *data, QObject *parent)
    : QObject{parent}
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    this->m_dataContainer = data;

    connect(this->m_dataContainer, SIGNAL(loadedChanged()), this, SLOT(loadModel()));

}

void HeaderBar::loadModel(){

    int cur_week_count = HOURS_WEEK;
    bool cur_week_set = false;
    int cur_month_count = HOURS_MONTH;
    bool cur_month_set = false;
    int cur_year_count = HOURS_YEAR;
    bool cur_year_set = false;

    qint64 week_deliverd = 0;
    qint64 week_returned = 0;
    qint64 week_gas = 0;
    qint64 week_solar = 0;
    qint64 week_used = 0;

    qint64 month_deliverd = 0;
    qint64 month_returned = 0;
    qint64 month_gas = 0;
    qint64 month_solar = 0;
    qint64 month_used = 0;

    qint64 year_deliverd = 0;
    qint64 year_returned = 0;
    qint64 year_gas = 0;
    qint64 year_solar = 0;
    qint64 year_used = 0;

    qint64 week_delivered_avg = 0;
    qint64 week_returned_avg = 0;
    qint64 week_gas_avg = 0;
    qint64 week_solar_avg = 0;
    qint64 week_used_avg = 0;
    int week_avg_count = 0;

    qint64 month_delivered_avg = 0;
    qint64 month_returned_avg = 0;
    qint64 month_gas_avg = 0;
    qint64 month_solar_avg = 0;
    qint64 month_used_avg = 0;
    int month_avg_count = 0;

    qint64 year_delivered_avg = 0;
    qint64 year_returned_avg = 0;
    qint64 year_gas_avg = 0;
    qint64 year_solar_avg = 0;
    qint64 year_used_avg = 0;
    int year_avg_count = 0;


    for(int i = 1; i < m_dataContainer->items.size(); i++){
        DataItem *item = m_dataContainer->items[i];
        week_deliverd = week_deliverd + (item->powerDeliverd);
        week_returned = week_returned + item->powerReturnd;
        week_gas = week_gas + item->gasUsed;
        week_solar = week_solar + item->solarResult;
        week_used = week_used + item->powerUsed;

        month_deliverd = month_deliverd + (item->powerDeliverd);
        month_returned = month_returned + item->powerReturnd;
        month_gas = month_gas + item->gasUsed;
        month_solar = month_solar + item->solarResult;
        month_used = month_used + item->powerUsed;


        year_deliverd = year_deliverd + (item->powerDeliverd);
        year_returned = year_returned + item->powerReturnd;
        year_gas = year_gas + item->gasUsed;
        year_solar = year_solar + item->solarResult;
        year_used = year_used + item->powerUsed;

        if(cur_week_count == 0){
            cur_week_count = HOURS_WEEK;
            if(cur_week_set == false){
                this->setWeekDelivered(week_deliverd);
                this->setWeekReturned(week_returned);
                this->setWeekResult(week_deliverd - week_returned);
                this->setWeekGas(week_gas);
                this->setWeeksolar(week_solar);
                this->setWeekUsed(week_used);
                cur_week_set = true;
            }
            week_delivered_avg = week_delivered_avg + week_deliverd;
            week_returned_avg = week_returned_avg + week_returned;
            week_gas_avg = week_gas_avg + week_gas;
            week_solar_avg = week_solar_avg + week_solar;
            week_used_avg = week_used_avg + week_used;

            week_avg_count++;
            week_deliverd = 0;
            week_returned = 0;
            week_gas = 0;
            week_solar = 0;
            week_used = 0;

        }


        if(cur_month_count == 0){
            cur_month_count = HOURS_MONTH;
            if(cur_month_set == false){
                this->setmonthDelivered(month_deliverd);
                this->setmonthReturned(month_returned);
                this->setmonthResult(month_deliverd - month_returned);
                this->setmonthGas(month_gas);
                this->setmonthsolar(month_solar);
                this->setmonthUsed(month_used);
                cur_month_set = true;
            }
            month_delivered_avg = month_delivered_avg + month_deliverd;
            month_returned_avg = month_returned_avg + month_returned;
            month_gas_avg = month_gas_avg + month_gas;
            month_solar_avg = month_solar_avg + month_solar;
            month_used_avg = month_used_avg + month_used;
            month_avg_count++;
            month_deliverd = 0;
            month_returned = 0;
            month_gas = 0;
            month_solar = 0;
            month_used = 0;
        }

        if(cur_year_count == 0){
            cur_year_count = HOURS_YEAR;
            if(cur_year_set == false){
                this->setyearDelivered(year_deliverd);
                this->setyearReturned(year_returned);
                this->setyearResult(year_deliverd - year_returned);
                this->setyearGas(year_gas);
                this->setyearsolar(year_solar);
                this->setyearUsed(year_used);
                cur_year_set = true;
            }
            year_delivered_avg = year_delivered_avg + year_deliverd;
            year_returned_avg = year_returned_avg + year_returned;
            year_gas_avg = year_gas_avg + year_gas;
            year_solar_avg = year_solar_avg + year_solar;
            year_used_avg = year_used_avg + year_used;
            year_avg_count++;
            year_deliverd = 0;
            year_returned = 0;
            year_gas = 0;
            year_solar = 0;
            year_used = 0;
        }

         cur_week_count = cur_week_count - 1;
         cur_month_count = cur_month_count - 1;
         cur_year_count = cur_year_count - 1;
    }

    if(week_avg_count > 0){
        this->setWeekAVGDelivered(week_delivered_avg / week_avg_count);
        this->setWeekAVGReturned(week_returned_avg / week_avg_count);
        this->setWeekAVGResult((week_delivered_avg - week_returned_avg) / week_avg_count);
        this->setWeekAVGGas(week_gas_avg / week_avg_count);
        this->setWeekAVGsolar(week_solar_avg / week_avg_count);
        this->setWeekAVGUsed(week_used_avg / week_avg_count);


        this->setWeekDeliveredMin(m_weekAVGDelivered - (m_weekAVGDelivered *0.75));
        this->setWeekDeliveredMax(m_weekAVGDelivered + (m_weekAVGDelivered *0.75));
        float pct = float(m_weekDelivered - m_weekDeliveredMin) / float(m_weekDeliveredMax - m_weekDeliveredMin);
        this->setWeekDeliverdPCT(pct);
        this->setWeekReturnedMin(m_weekAVGReturned - (m_weekAVGReturned *0.75));
        this->setWeekReturnedMax(m_weekAVGReturned + (m_weekAVGReturned *0.75));
        pct = float(m_weekReturned - m_weekReturnedMin) / float(m_weekReturnedMax - m_weekReturnedMin);
        this->setWeekReturnedPCT(pct);
        this->setWeekResultMin(m_weekAVGResult - (m_weekAVGResult *0.75));
        this->setWeekResultMax(m_weekAVGResult + (m_weekAVGResult *0.75));
         pct = float(m_weekAVGResult - m_weekResultMin) / float(m_weekResultMax - m_weekResultMin);
        this->setWeekResultPCT(pct);
        this->setWeekGasMax(m_weekAVGGas + (m_weekAVGGas *0.75));
        this->setWeekGasMin(m_weekAVGGas - (m_weekAVGGas *0.75));
        pct = float(m_weekGas - m_weekGasMin) / float(m_weekAVGGas - m_weekGasMin);
        this->setWeekGasPCT(pct);
        this->setWeeksolarMax(m_weekAVGsolar + (m_weekAVGsolar * 0.75));
        this->setWeeksolarMin(m_weekAVGsolar - (m_weekAVGsolar * 0.75));
        this->setWeekUsedMax(m_weekAVGUsed + (m_weekAVGUsed * 0.75));
        this->setWeekUsedMin(m_weekAVGUsed - (m_weekAVGUsed * 0.75));


        int bp = 0;
        bp++;
    }

    if(month_avg_count > 0){
        this->setmonthAVGDelivered(month_delivered_avg / month_avg_count);
        this->setmonthAVGReturned(month_returned_avg / month_avg_count);
        this->setmonthAVGResult((month_delivered_avg - month_returned_avg) / month_avg_count);
        this->setmonthAVGGas(month_gas_avg / month_avg_count);
        this->setmonthAVGsolar(month_solar_avg / month_avg_count);
        this->setmonthAVGUsed(month_used_avg / month_avg_count);


        this->setmonthDeliveredMin(m_monthAVGDelivered - (m_monthAVGDelivered *0.75));
        this->setmonthDeliveredMax(m_monthAVGDelivered + (m_monthAVGDelivered *0.75));
          this->setmonthReturnedMin(m_monthAVGReturned - (m_monthAVGReturned *0.75));
        this->setmonthReturnedMax(m_monthAVGReturned + (m_monthAVGReturned *0.75));
         this->setmonthResultMin(m_monthAVGResult - (m_monthAVGResult *0.75));
        this->setmonthResultMax(m_monthAVGResult + (m_monthAVGResult *0.75));
          this->setmonthGasMax(m_monthAVGGas + (m_monthAVGGas *0.75));
        this->setmonthGasMin(m_monthAVGGas - (m_monthAVGGas *0.75));
          this->setmonthsolarMin(m_monthAVGsolar - (m_monthAVGsolar * 0.75));
        this->setmonthsolarMax(m_monthAVGsolar + (m_monthAVGsolar * 0*75));
          this->setmonthUsedMax(m_monthAVGUsed + (m_monthAVGUsed * 0.75));
        this->setmonthUsedMin(m_monthAVGUsed - (m_monthAVGUsed * 0.75));

        int bp = 0;
        bp++;
    }

    if(year_avg_count > 0){
        this->setyearAVGDelivered(year_delivered_avg / year_avg_count);
        this->setyearAVGReturned(year_returned_avg / year_avg_count);
        this->setyearAVGResult((year_delivered_avg - year_returned_avg) / year_avg_count);
        this->setyearAVGGas(year_gas_avg / year_avg_count);
        this->setyearAVGsolar(year_solar_avg / year_avg_count);
        this->setyearAVGUsed(year_used_avg / year_avg_count);

        this->setyearDeliveredMin(m_yearAVGDelivered - (m_yearAVGDelivered *0.75));
        this->setyearDeliveredMax(m_yearAVGDelivered + (m_yearAVGDelivered *0.75));
        this->setyearReturnedMin(m_yearAVGReturned - (m_yearAVGReturned *0.75));
        this->setyearReturnedMax(m_yearAVGReturned + (m_yearAVGReturned *0.75));
        this->setyearResultMin(m_yearAVGResult - (m_yearAVGResult *0.75));
        this->setyearResultMax(m_yearAVGResult + (m_yearAVGResult *0.75));
        this->setyearGasMax(m_yearAVGGas + (m_yearAVGGas *0.75));
        this->setyearGasMin(m_yearAVGGas - (m_yearAVGGas *0.75));
        this->setyearsolarMax(m_yearAVGsolar + (m_yearAVGsolar * 0.75));
        this->setyearsolarMin(m_yearAVGsolar - (m_yearAVGsolar * 0.75));
        this->setyearUsedMax(m_yearAVGUsed +(m_yearAVGUsed * 0.75));
        this->setyearUsedMin(m_yearAVGUsed - (m_yearAVGUsed * 0.75));

        int bp = 0;
        bp++;
    }


}
int HeaderBar::weekAVGDelivered() const
{
    return m_weekAVGDelivered;
}

void HeaderBar::setWeekAVGDelivered(int newWeekAVGDelivered)
{
    if (m_weekAVGDelivered == newWeekAVGDelivered)
        return;
    m_weekAVGDelivered = newWeekAVGDelivered;
    emit weekAVGDeliveredChanged();
}

int HeaderBar::weekDelivered() const
{
    return m_weekDelivered;
}

void HeaderBar::setWeekDelivered(int newWeekDelivered)
{
    if (m_weekDelivered == newWeekDelivered)
        return;
    m_weekDelivered = newWeekDelivered;
    emit weekDeliveredChanged();
}

int HeaderBar::weekAVGReturned() const
{
    return m_weekAVGReturned;
}

void HeaderBar::setWeekAVGReturned(int newWeekAVGReturned)
{
    if (m_weekAVGReturned == newWeekAVGReturned)
        return;
    m_weekAVGReturned = newWeekAVGReturned;
    emit weekAVGReturnedChanged();
}

int HeaderBar::weekReturned() const
{
    return m_weekReturned;
}

void HeaderBar::setWeekReturned(int newWeekReturned)
{
    if (m_weekReturned == newWeekReturned)
        return;
    m_weekReturned = newWeekReturned;
    emit weekReturnedChanged();
}

int HeaderBar::weekAVGResult() const
{
    return m_weekAVGResult;
}

void HeaderBar::setWeekAVGResult(int newWeekAVGResult)
{
    if (m_weekAVGResult == newWeekAVGResult)
        return;
    m_weekAVGResult = newWeekAVGResult;
    emit weekAVGResultChanged();
}

int HeaderBar::weekResult() const
{
    return m_weekResult;
}

void HeaderBar::setWeekResult(int newWeekResult)
{
    if (m_weekResult == newWeekResult)
        return;
    m_weekResult = newWeekResult;
    emit weekResultChanged();
}

int HeaderBar::weekAVGGas() const
{
    return m_weekAVGGas;
}

void HeaderBar::setWeekAVGGas(int newWeekAVGGas)
{
    if (m_weekAVGGas == newWeekAVGGas)
        return;
    m_weekAVGGas = newWeekAVGGas;
    emit weekAVGGasChanged();
}

int HeaderBar::weekGas() const
{
    return m_weekGas;
}

void HeaderBar::setWeekGas(int newWeekGas)
{
    if (m_weekGas == newWeekGas)
        return;
    m_weekGas = newWeekGas;
    emit weekGasChanged();
}

int HeaderBar::weekDeliveredMin() const
{
    return m_weekDeliveredMin;
}

void HeaderBar::setWeekDeliveredMin(int newWeekDeliveredMin)
{
    if (m_weekDeliveredMin == newWeekDeliveredMin)
        return;
    m_weekDeliveredMin = newWeekDeliveredMin;
    emit weekDeliveredMinChanged();
}

int HeaderBar::weekDeliveredMax() const
{
    return m_weekDeliveredMax;
}

void HeaderBar::setWeekDeliveredMax(int newWeekDeliveredMax)
{
    if (m_weekDeliveredMax == newWeekDeliveredMax)
        return;
    m_weekDeliveredMax = newWeekDeliveredMax;
    emit weekDeliveredMaxChanged();
}

int HeaderBar::weekReturnedMax() const
{
    return m_weekReturnedMax;
}

void HeaderBar::setWeekReturnedMax(int newWeekReturnedMax)
{
    if (m_weekReturnedMax == newWeekReturnedMax)
        return;
    m_weekReturnedMax = newWeekReturnedMax;
    emit weekReturnedMaxChanged();
}

int HeaderBar::weekReturnedMin() const
{
    return m_weekReturnedMin;
}

void HeaderBar::setWeekReturnedMin(int newWeekReturnedMin)
{
    if (m_weekReturnedMin == newWeekReturnedMin)
        return;
    m_weekReturnedMin = newWeekReturnedMin;
    emit weekReturnedMinChanged();
}

int HeaderBar::weekResultMax() const
{
    return m_weekResultMax;
}

void HeaderBar::setWeekResultMax(int newWeekResultMax)
{
    if (m_weekResultMax == newWeekResultMax)
        return;
    m_weekResultMax = newWeekResultMax;
    emit weekResultMaxChanged();
}

int HeaderBar::weekResultMin() const
{
    return m_weekResultMin;
}

void HeaderBar::setWeekResultMin(int newWeekResultMin)
{
    if (m_weekResultMin == newWeekResultMin)
        return;
    m_weekResultMin = newWeekResultMin;
    emit weekResultMinChanged();
}

int HeaderBar::weekGasMax() const
{
    return m_weekGasMax;
}

void HeaderBar::setWeekGasMax(int newWeekGasMax)
{
    if (m_weekGasMax == newWeekGasMax)
        return;
    m_weekGasMax = newWeekGasMax;
    emit weekGasMaxChanged();
}

int HeaderBar::weekGasMin() const
{
    return m_weekGasMin;
}

void HeaderBar::setWeekGasMin(int newWeekGasMin)
{
    if (m_weekGasMin == newWeekGasMin)
        return;
    m_weekGasMin = newWeekGasMin;
    emit weekGasMinChanged();
}

float HeaderBar::weekDeliverdPCT() const
{
    return m_weekDeliverdPCT;
}

void HeaderBar::setWeekDeliverdPCT(float newWeekDeliverdPCT)
{
    if (qFuzzyCompare(m_weekDeliverdPCT, newWeekDeliverdPCT))
        return;
    m_weekDeliverdPCT = newWeekDeliverdPCT;
    emit weekDeliverdPCTChanged();
}

float HeaderBar::weekReturnedPCT() const
{
    return m_weekReturnedPCT;
}

void HeaderBar::setWeekReturnedPCT(float newWeekReturnedPCT)
{
    if (qFuzzyCompare(m_weekReturnedPCT, newWeekReturnedPCT))
        return;
    m_weekReturnedPCT = newWeekReturnedPCT;
    emit weekReturnedPCTChanged();
}

float HeaderBar::weekResultPCT() const
{
    return m_weekResultPCT;
}

void HeaderBar::setWeekResultPCT(float newWeekResultPCT)
{
    if (qFuzzyCompare(m_weekResultPCT, newWeekResultPCT))
        return;
    m_weekResultPCT = newWeekResultPCT;
    emit weekResultPCTChanged();
}

float HeaderBar::weekGasPCT() const
{
    return m_weekGasPCT;
}

void HeaderBar::setWeekGasPCT(float newWeekGasPCT)
{
    if (qFuzzyCompare(m_weekGasPCT, newWeekGasPCT))
        return;
    m_weekGasPCT = newWeekGasPCT;
    emit weekGasPCTChanged();
}

int HeaderBar::monthAVGDelivered() const
{
    return m_monthAVGDelivered;
}

void HeaderBar::setmonthAVGDelivered(int newMonthAVGDelivered)
{
    if (m_monthAVGDelivered == newMonthAVGDelivered)
        return;
    m_monthAVGDelivered = newMonthAVGDelivered;
    emit monthAVGDeliveredChanged();
}

int HeaderBar::monthDelivered() const
{
    return m_monthDelivered;
}

void HeaderBar::setmonthDelivered(int newMonthDelivered)
{
    if (m_monthDelivered == newMonthDelivered)
        return;
    m_monthDelivered = newMonthDelivered;
    emit monthDeliveredChanged();
}

int HeaderBar::monthDeliveredMin() const
{
    return m_monthDeliveredMin;
}

void HeaderBar::setmonthDeliveredMin(int newMonthDeliveredMin)
{
    if (m_monthDeliveredMin == newMonthDeliveredMin)
        return;
    m_monthDeliveredMin = newMonthDeliveredMin;
    emit monthDeliveredMinChanged();
}

int HeaderBar::monthDeliveredMax() const
{
    return m_monthDeliveredMax;
}

void HeaderBar::setmonthDeliveredMax(int newMonthDeliveredMax)
{
    if (m_monthDeliveredMax == newMonthDeliveredMax)
        return;
    m_monthDeliveredMax = newMonthDeliveredMax;
    emit monthDeliveredMaxChanged();
}

int HeaderBar::monthAVGReturned() const
{
    return m_monthAVGReturned;
}

void HeaderBar::setmonthAVGReturned(int newMonthAVGReturned)
{
    if (m_monthAVGReturned == newMonthAVGReturned)
        return;
    m_monthAVGReturned = newMonthAVGReturned;
    emit monthAVGReturnedChanged();
}

int HeaderBar::monthReturnedMax() const
{
    return m_monthReturnedMax;
}

void HeaderBar::setmonthReturnedMax(int newMonthReturnedMax)
{
    if (m_monthReturnedMax == newMonthReturnedMax)
        return;
    m_monthReturnedMax = newMonthReturnedMax;
    emit monthReturnedMaxChanged();
}

int HeaderBar::monthReturnedMin() const
{
    return m_monthReturnedMin;
}

void HeaderBar::setmonthReturnedMin(int newMonthReturnedMin)
{
    if (m_monthReturnedMin == newMonthReturnedMin)
        return;
    m_monthReturnedMin = newMonthReturnedMin;
    emit monthReturnedMinChanged();
}

int HeaderBar::monthReturned() const
{
    return m_monthReturned;
}

void HeaderBar::setmonthReturned(int newMonthReturned)
{
    if (m_monthReturned == newMonthReturned)
        return;
    m_monthReturned = newMonthReturned;
    emit monthReturnedChanged();
}

int HeaderBar::monthAVGResult() const
{
    return m_monthAVGResult;
}

void HeaderBar::setmonthAVGResult(int newMonthAVGResult)
{
    if (m_monthAVGResult == newMonthAVGResult)
        return;
    m_monthAVGResult = newMonthAVGResult;
    emit monthAVGResultChanged();
}

int HeaderBar::monthResultMax() const
{
    return m_monthResultMax;
}

void HeaderBar::setmonthResultMax(int newMonthResultMax)
{
    if (m_monthResultMax == newMonthResultMax)
        return;
    m_monthResultMax = newMonthResultMax;
    emit monthResultMaxChanged();
}

int HeaderBar::monthResultMin() const
{
    return m_monthResultMin;
}

void HeaderBar::setmonthResultMin(int newMonthResultMin)
{
    if (m_monthResultMin == newMonthResultMin)
        return;
    m_monthResultMin = newMonthResultMin;
    emit monthResultMinChanged();
}

int HeaderBar::monthAVGGas() const
{
    return m_monthAVGGas;
}

void HeaderBar::setmonthAVGGas(int newMonthAVGGas)
{
    if (m_monthAVGGas == newMonthAVGGas)
        return;
    m_monthAVGGas = newMonthAVGGas;
    emit monthAVGGasChanged();
}

int HeaderBar::monthResult() const
{
    return m_monthResult;
}

void HeaderBar::setmonthResult(int newMonthResult)
{
    if (m_monthResult == newMonthResult)
        return;
    m_monthResult = newMonthResult;
    emit monthResultChanged();
}

int HeaderBar::monthGas() const
{
    return m_monthGas;
}

void HeaderBar::setmonthGas(int newMonthGas)
{
    if (m_monthGas == newMonthGas)
        return;
    m_monthGas = newMonthGas;
    emit monthGasChanged();
}

int HeaderBar::monthGasMax() const
{
    return m_monthGasMax;
}

void HeaderBar::setmonthGasMax(int newMonthGasMax)
{
    if (m_monthGasMax == newMonthGasMax)
        return;
    m_monthGasMax = newMonthGasMax;
    emit monthGasMaxChanged();
}

int HeaderBar::monthGasMin() const
{
    return m_monthGasMin;
}

void HeaderBar::setmonthGasMin(int newMonthGasMin)
{
    if (m_monthGasMin == newMonthGasMin)
        return;
    m_monthGasMin = newMonthGasMin;
    emit monthGasMinChanged();
}

int HeaderBar::yearAVGDelivered() const
{
    return m_yearAVGDelivered;
}

void HeaderBar::setyearAVGDelivered(int newYearAVGDelivered)
{
    if (m_yearAVGDelivered == newYearAVGDelivered)
        return;
    m_yearAVGDelivered = newYearAVGDelivered;
    emit yearAVGDeliveredChanged();
}

int HeaderBar::yearDelivered() const
{
    return m_yearDelivered;
}

void HeaderBar::setyearDelivered(int newYearDelivered)
{
    if (m_yearDelivered == newYearDelivered)
        return;
    m_yearDelivered = newYearDelivered;
    emit yearDeliveredChanged();
}

int HeaderBar::yearDeliveredMin() const
{
    return m_yearDeliveredMin;
}

void HeaderBar::setyearDeliveredMin(int newYearDeliveredMin)
{
    if (m_yearDeliveredMin == newYearDeliveredMin)
        return;
    m_yearDeliveredMin = newYearDeliveredMin;
    emit yearDeliveredMinChanged();
}

int HeaderBar::yearDeliveredMax() const
{
    return m_yearDeliveredMax;
}

void HeaderBar::setyearDeliveredMax(int newYearDeliveredMax)
{
    if (m_yearDeliveredMax == newYearDeliveredMax)
        return;
    m_yearDeliveredMax = newYearDeliveredMax;
    emit yearDeliveredMaxChanged();
}

int HeaderBar::yearAVGReturned() const
{
    return m_yearAVGReturned;
}

void HeaderBar::setyearAVGReturned(int newYearAVGReturned)
{
    if (m_yearAVGReturned == newYearAVGReturned)
        return;
    m_yearAVGReturned = newYearAVGReturned;
    emit yearAVGReturnedChanged();
}

int HeaderBar::yearReturnedMax() const
{
    return m_yearReturnedMax;
}

void HeaderBar::setyearReturnedMax(int newYearReturnedMax)
{
    if (m_yearReturnedMax == newYearReturnedMax)
        return;
    m_yearReturnedMax = newYearReturnedMax;
    emit yearReturnedMaxChanged();
}

int HeaderBar::yearReturnedMin() const
{
    return m_yearReturnedMin;
}

void HeaderBar::setyearReturnedMin(int newYearReturnedMin)
{
    if (m_yearReturnedMin == newYearReturnedMin)
        return;
    m_yearReturnedMin = newYearReturnedMin;
    emit yearReturnedMinChanged();
}

int HeaderBar::yearReturned() const
{
    return m_yearReturned;
}

void HeaderBar::setyearReturned(int newYearReturned)
{
    if (m_yearReturned == newYearReturned)
        return;
    m_yearReturned = newYearReturned;
    emit yearReturnedChanged();
}

int HeaderBar::yearAVGResult() const
{
    return m_yearAVGResult;
}

void HeaderBar::setyearAVGResult(int newYearAVGResult)
{
    if (m_yearAVGResult == newYearAVGResult)
        return;
    m_yearAVGResult = newYearAVGResult;
    emit yearAVGResultChanged();
}

int HeaderBar::yearResult() const
{
    return m_yearResult;
}

void HeaderBar::setyearResult(int newYearResult)
{
    if (m_yearResult == newYearResult)
        return;
    m_yearResult = newYearResult;
    emit yearResultChanged();
}

int HeaderBar::yearResultMax() const
{
    return m_yearResultMax;
}

void HeaderBar::setyearResultMax(int newYearResultMax)
{
    if (m_yearResultMax == newYearResultMax)
        return;
    m_yearResultMax = newYearResultMax;
    emit yearResultMaxChanged();
}

int HeaderBar::yearResultMin() const
{
    return m_yearResultMin;
}

void HeaderBar::setyearResultMin(int newYearResultMin)
{
    if (m_yearResultMin == newYearResultMin)
        return;
    m_yearResultMin = newYearResultMin;
    emit yearResultMinChanged();
}

int HeaderBar::yearAVGGas() const
{
    return m_yearAVGGas;
}

void HeaderBar::setyearAVGGas(int newYearAVGGas)
{
    if (m_yearAVGGas == newYearAVGGas)
        return;
    m_yearAVGGas = newYearAVGGas;
    emit yearAVGGasChanged();
}

int HeaderBar::yearGas() const
{
    return m_yearGas;
}

void HeaderBar::setyearGas(int newYearGas)
{
    if (m_yearGas == newYearGas)
        return;
    m_yearGas = newYearGas;
    emit yearGasChanged();
}

int HeaderBar::yearGasMax() const
{
    return m_yearGasMax;
}

void HeaderBar::setyearGasMax(int newYearGasMax)
{
    if (m_yearGasMax == newYearGasMax)
        return;
    m_yearGasMax = newYearGasMax;
    emit yearGasMaxChanged();
}

int HeaderBar::yearGasMin() const
{
    return m_yearGasMin;
}

void HeaderBar::setyearGasMin(int newYearGasMin)
{
    if (m_yearGasMin == newYearGasMin)
        return;
    m_yearGasMin = newYearGasMin;
    emit yearGasMinChanged();
}

int HeaderBar::weeksolar() const
{
    return m_weeksolar;
}

void HeaderBar::setWeeksolar(int newWeeksolar)
{
    if (m_weeksolar == newWeeksolar)
        return;
    m_weeksolar = newWeeksolar;
    emit weeksolarChanged();
}

int HeaderBar::weeksolarMax() const
{
    return m_weeksolarMax;
}

void HeaderBar::setWeeksolarMax(int newWeeksolarMax)
{
    if (m_weeksolarMax == newWeeksolarMax)
        return;
    m_weeksolarMax = newWeeksolarMax;
    emit weeksolarMaxChanged();
}

int HeaderBar::weeksolarMin() const
{
    return m_weeksolarMin;
}

void HeaderBar::setWeeksolarMin(int newWeeksolarMin)
{
    if (m_weeksolarMin == newWeeksolarMin)
        return;
    m_weeksolarMin = newWeeksolarMin;
    emit weeksolarMinChanged();
}

float HeaderBar::weeksolarPCT() const
{
    return m_weeksolarPCT;
}

void HeaderBar::setWeeksolarPCT(float newWeeksolarPCT)
{
    if (qFuzzyCompare(m_weeksolarPCT, newWeeksolarPCT))
        return;
    m_weeksolarPCT = newWeeksolarPCT;
    emit weeksolarPCTChanged();
}

int HeaderBar::weekAVGsolar() const
{
    return m_weekAVGsolar;
}

void HeaderBar::setWeekAVGsolar(int newWeekAVGsolar)
{
    if (m_weekAVGsolar == newWeekAVGsolar)
        return;
    m_weekAVGsolar = newWeekAVGsolar;
    emit weekAVGsolarChanged();
}

int HeaderBar::monthsolar() const
{
    return m_monthsolar;
}

void HeaderBar::setmonthsolar(int newMonthsolar)
{
    if (m_monthsolar == newMonthsolar)
        return;
    m_monthsolar = newMonthsolar;
    emit monthsolarChanged();
}

int HeaderBar::monthsolarMax() const
{
    return m_monthsolarMax;
}

void HeaderBar::setmonthsolarMax(int newMonthsolarMax)
{
    if (m_monthsolarMax == newMonthsolarMax)
        return;
    m_monthsolarMax = newMonthsolarMax;
    emit monthsolarMaxChanged();
}

int HeaderBar::monthsolarMin() const
{
    return m_monthsolarMin;
}

void HeaderBar::setmonthsolarMin(int newMonthsolarMin)
{
    if (m_monthsolarMin == newMonthsolarMin)
        return;
    m_monthsolarMin = newMonthsolarMin;
    emit monthsolarMinChanged();
}

int HeaderBar::monthAVGsolar() const
{
    return m_monthAVGsolar;
}

void HeaderBar::setmonthAVGsolar(int newMonthAVGsolar)
{
    if (m_monthAVGsolar == newMonthAVGsolar)
        return;
    m_monthAVGsolar = newMonthAVGsolar;
    emit monthAVGsolarChanged();
}

int HeaderBar::yearsolar() const
{
    return m_yearsolar;
}

void HeaderBar::setyearsolar(int newYearsolar)
{
    if (m_yearsolar == newYearsolar)
        return;
    m_yearsolar = newYearsolar;
    emit yearsolarChanged();
}

int HeaderBar::yearsolarMax() const
{
    return m_yearsolarMax;
}

void HeaderBar::setyearsolarMax(int newYearsolarMax)
{
    if (m_yearsolarMax == newYearsolarMax)
        return;
    m_yearsolarMax = newYearsolarMax;
    emit yearsolarMaxChanged();
}

int HeaderBar::yearsolarMin() const
{
    return m_yearsolarMin;
}

void HeaderBar::setyearsolarMin(int newYearsolarMin)
{
    if (m_yearsolarMin == newYearsolarMin)
        return;
    m_yearsolarMin = newYearsolarMin;
    emit yearsolarMinChanged();
}

int HeaderBar::yearAVGsolar() const
{
    return m_yearAVGsolar;
}

void HeaderBar::setyearAVGsolar(int newYearAVGsolar)
{
    if (m_yearAVGsolar == newYearAVGsolar)
        return;
    m_yearAVGsolar = newYearAVGsolar;
    emit yearAVGsolarChanged();
}

int HeaderBar::weekAVGUsed() const
{
    return m_weekAVGUsed;
}

void HeaderBar::setWeekAVGUsed(int newWeekAVGUsed)
{
    if (m_weekAVGUsed == newWeekAVGUsed)
        return;
    m_weekAVGUsed = newWeekAVGUsed;
    emit weekAVGUsedChanged();
}

int HeaderBar::weekUsed() const
{
    return m_weekUsed;
}

void HeaderBar::setWeekUsed(int newWeekUsed)
{
    if (m_weekUsed == newWeekUsed)
        return;
    m_weekUsed = newWeekUsed;
    emit weekUsedChanged();
}

int HeaderBar::weekUsedMin() const
{
    return m_weekUsedMin;
}

void HeaderBar::setWeekUsedMin(int newWeekUsedMin)
{
    if (m_weekUsedMin == newWeekUsedMin)
        return;
    m_weekUsedMin = newWeekUsedMin;
    emit weekUsedMinChanged();
}

int HeaderBar::weekUsedMax() const
{
    return m_weekUsedMax;
}

void HeaderBar::setWeekUsedMax(int newWeekUsedMax)
{
    if (m_weekUsedMax == newWeekUsedMax)
        return;
    m_weekUsedMax = newWeekUsedMax;
    emit weekUsedMaxChanged();
}

int HeaderBar::monthAVGUsed() const
{
    return m_monthAVGUsed;
}

void HeaderBar::setmonthAVGUsed(int newMonthAVGUsed)
{
    if (m_monthAVGUsed == newMonthAVGUsed)
        return;
    m_monthAVGUsed = newMonthAVGUsed;
    emit monthAVGUsedChanged();
}

int HeaderBar::monthUsed() const
{
    return m_monthUsed;
}

void HeaderBar::setmonthUsed(int newMonthUsed)
{
    if (m_monthUsed == newMonthUsed)
        return;
    m_monthUsed = newMonthUsed;
    emit monthUsedChanged();
}

int HeaderBar::monthUsedMin() const
{
    return m_monthUsedMin;
}

void HeaderBar::setmonthUsedMin(int newMonthUsedMin)
{
    if (m_monthUsedMin == newMonthUsedMin)
        return;
    m_monthUsedMin = newMonthUsedMin;
    emit monthUsedMinChanged();
}

int HeaderBar::monthUsedMax() const
{
    return m_monthUsedMax;
}

void HeaderBar::setmonthUsedMax(int newMonthUsedMax)
{
    if (m_monthUsedMax == newMonthUsedMax)
        return;
    m_monthUsedMax = newMonthUsedMax;
    emit monthUsedMaxChanged();
}

int HeaderBar::yearAVGUsed() const
{
    return m_yearAVGUsed;
}

void HeaderBar::setyearAVGUsed(int newYearAVGUsed)
{
    if (m_yearAVGUsed == newYearAVGUsed)
        return;
    m_yearAVGUsed = newYearAVGUsed;
    emit yearAVGUsedChanged();
}

int HeaderBar::yearUsed() const
{
    return m_yearUsed;
}

void HeaderBar::setyearUsed(int newYearUsed)
{
    if (m_yearUsed == newYearUsed)
        return;
    m_yearUsed = newYearUsed;
    emit yearUsedChanged();
}

int HeaderBar::yearUsedMin() const
{
    return m_yearUsedMin;
}

void HeaderBar::setyearUsedMin(int newYearUsedMin)
{
    if (m_yearUsedMin == newYearUsedMin)
        return;
    m_yearUsedMin = newYearUsedMin;
    emit yearUsedMinChanged();
}

int HeaderBar::yearUsedMax() const
{
    return m_yearUsedMax;
}

void HeaderBar::setyearUsedMax(int newYearUsedMax)
{
    if (m_yearUsedMax == newYearUsedMax)
        return;
    m_yearUsedMax = newYearUsedMax;
    emit yearUsedMaxChanged();
}
