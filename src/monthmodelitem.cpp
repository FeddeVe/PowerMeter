#include "monthmodelitem.h"

monthModelItem::monthModelItem(int year, int month,QObject *parent)
    : QObject{parent}
{

    this->m_date.setDate(year, month, 1);

    this->month = month;

    this->year = year;

    this->setLabel(this->getMonthName(month));
    m_curCount = m_date.daysInMonth() * 24;
    m_curCountSet = m_date.daysInMonth() * 24;
    m_avgDelivered = 0;
    m_curDelivered = 0;
    m_avgResult = 0;
    m_curResult = 0;
    m_avgGas = 0;
    m_curGas = 0;
    m_avgReturned = 0;
    m_curReturned = 0;
    m_avgSolar = 0;
    m_curSolar = 0;
    currentSet = false;
    rawAvgReturned = 0;
    RawAvgDelivered = 0;
     rawUsed = 0;
    rawGasUsed = 0;
    rawResult = 0;
    rawSolar = 0;
    avgCount = 0;
    avgRetCount = 0;
    m_avgUsed = 0;
    m_curUsed = 0;
    m_isCurrent = false;

}

QString monthModelItem::getMonthName(int month){
    switch(month){
    case 1:
        return "JAN";
    case 2:
        return "FEB";
    case 3:
        return "MAR";
    case 4:
        return "APR";
    case 5:
        return "MAY";
    case 6:
        return "JUN";
    case 7:
        return "JUL";
    case 8:
        return "AUG";
    case 9:
        return "SEP";
    case 10:
        return "OKT";
    case 11:
        return "NOV";
    case 12:
        return "DEC";
    }
    return "INVALID";
}

QString monthModelItem::label() const
{
    return m_label;
}

void monthModelItem::setLabel(const QString &newLabel)
{
    if (m_label == newLabel)
        return;
    m_label = newLabel;
    emit labelChanged();
}

int monthModelItem::avgDelivered() const
{
    return m_avgDelivered;
}

void monthModelItem::setAvgDelivered(int newAvgDelivered)
{
    if (m_avgDelivered == newAvgDelivered)
        return;
    m_avgDelivered = newAvgDelivered;
    emit avgDeliveredChanged();
}

int monthModelItem::curDelivered() const
{
    return m_curDelivered;
}

void monthModelItem::setCurDelivered(int newCurDelivered)
{
    if (m_curDelivered == newCurDelivered)
        return;
    m_curDelivered = newCurDelivered;
    emit curDeliveredChanged();
}

int monthModelItem::avgReturned() const
{
    return m_avgReturned;
}

void monthModelItem::setAvgReturned(int newAvgReturned)
{
    if (m_avgReturned == newAvgReturned)
        return;
    m_avgReturned = newAvgReturned;
    emit avgReturnedChanged();
}

int monthModelItem::curReturned() const
{
    return m_curReturned;
}

void monthModelItem::setCurReturned(int newCurReturned)
{
    if (m_curReturned == newCurReturned)
        return;
    m_curReturned = newCurReturned;
    emit curReturnedChanged();
}

int monthModelItem::avgGas() const
{
    return m_avgGas;
}

void monthModelItem::setAvgGas(int newAvgGas)
{
    if (m_avgGas == newAvgGas)
        return;
    m_avgGas = newAvgGas;
    emit avgGasChanged();
}

int monthModelItem::curGas() const
{
    return m_curGas;
}

void monthModelItem::setCurGas(int newCurGas)
{
    if (m_curGas == newCurGas)
        return;
    m_curGas = newCurGas;
    emit curGasChanged();
}

bool monthModelItem::setData(int delivered, int returned, int gas, bool calcRet,int solar,int used, bool isCurrent){

    bool ret = false;

    this->avgCount++;
    float divider = (float) avgCount / (float) m_curCountSet;
    if(m_curCountSet == 7){
        divider = avgCount;
    }

    this->RawAvgDelivered = this->RawAvgDelivered + delivered;
    if(calcRet){
        this->rawAvgReturned = this->rawAvgReturned + returned;
        this->rawSolar = this->rawSolar + solar;
        this->avgRetCount++;
        float divider2 = (float) avgRetCount / (float) m_curCountSet;
        if(m_curCountSet == 7){
            divider2 = avgCount;
        }
        this->setAvgReturned(((this->rawAvgReturned / divider2)/ m_curCountSet) * (30 * 24));
        this->setAvgSolar(((this->rawSolar / divider2) / m_curCountSet) * (30*24));

    }else{

    }
    this->rawGasUsed = this->rawGasUsed + gas;
    this->rawResult = this->rawResult + (delivered - returned);
    this->rawUsed = this->rawUsed + used;

    this->setAvgResult(((this->rawResult / divider)/ m_curCountSet) * (30 * 24));
    this->setAvgDelivered(((this->RawAvgDelivered / divider)/ m_curCountSet) * (30 * 24));
    this->setAvgGas(((this->rawGasUsed / divider)/ m_curCountSet) * (30 * 24));
    this->setAvgUsed(((this->rawUsed / divider)/ m_curCountSet) * (30 * 24));



    m_curCount = m_curCount-1;

  //  if(isCurrent){
    if((m_curCount <= 0) && (this->currentSet == false)){
        this->setCurDelivered(m_avgDelivered);
        this->setCurGas(m_avgGas);
        this->setCurReturned(m_avgReturned);
        this->setCurResult(m_avgDelivered - m_avgReturned);
        this->setCurSolar(m_avgSolar);
        this->setCurUsed(m_avgUsed);
        this->currentSet = true;
        ret = true;
   // }
    }

    if(m_curCount > 0){
        ret = true;
    }
    return ret;

}

int monthModelItem::curResult() const
{
    return m_curResult;
}

void monthModelItem::setCurResult(int newCurResult)
{
    if (m_curResult == newCurResult)
        return;
    m_curResult = newCurResult;
    emit curResultChanged();
}

int monthModelItem::avgResult() const
{
    return m_avgResult;
}

void monthModelItem::setAvgResult(int newAvgResult)
{
    if (m_avgResult == newAvgResult)
        return;
    m_avgResult = newAvgResult;
    emit avgResultChanged();
}


int monthModelItem::avgSolar() const
{
    return m_avgSolar;
}

void monthModelItem::setAvgSolar(int newAvgSolar)
{
    if (m_avgSolar == newAvgSolar)
        return;
    m_avgSolar = newAvgSolar;
    emit avgSolarChanged();
}

int monthModelItem::curSolar() const
{
    return m_curSolar;
}

void monthModelItem::setCurSolar(int newCurSolar)
{
    if (m_curSolar == newCurSolar)
        return;
    m_curSolar = newCurSolar;
    emit curSolarChanged();
}

int monthModelItem::curUsed() const
{
    return m_curUsed;
}

void monthModelItem::setCurUsed(int newCurUsed)
{
    if (m_curUsed == newCurUsed)
        return;
    m_curUsed = newCurUsed;
    emit curUsedChanged();
}

int monthModelItem::avgUsed() const
{
    return m_avgUsed;
}

void monthModelItem::setAvgUsed(int newAvgUsed)
{
    if (m_avgUsed == newAvgUsed)
        return;
    m_avgUsed = newAvgUsed;
    emit avgUsedChanged();
}

bool monthModelItem::isCurrent() const
{
    return m_isCurrent;
}

void monthModelItem::setIsCurrent(bool newIsCurrent)
{
    if (m_isCurrent == newIsCurrent)
        return;
    m_isCurrent = newIsCurrent;
    emit isCurrentChanged();
}
