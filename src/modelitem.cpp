#include "modelitem.h"

modelItem::modelItem(int CurCount, bool isCurrent, QObject *parent)
    : QObject{parent}
{
    m_curCount = CurCount;
    m_curCountSet = CurCount;
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
    rawGasUsed = 0;
    rawSolar = 0;
    rawResult = 0;
    rawUsed = 0;
    avgCount = 0;
    avgRetCount = 0;
    m_isCurrent = isCurrent;
    this->todayModel = false;

}


QString modelItem::label() const
{
    return m_label;
}

void modelItem::setLabel(const QString &newLabel)
{
    if (m_label == newLabel)
        return;
    m_label = newLabel;
    emit labelChanged();
}

int modelItem::avgDelivered() const
{
    return m_avgDelivered;
}

void modelItem::setAvgDelivered(int newAvgDelivered)
{
    if (m_avgDelivered == newAvgDelivered)
        return;
    m_avgDelivered = newAvgDelivered;
    emit avgDeliveredChanged();
}

int modelItem::curDelivered() const
{
    return m_curDelivered;
}

void modelItem::setCurDelivered(int newCurDelivered)
{
    if (m_curDelivered == newCurDelivered)
        return;
    m_curDelivered = newCurDelivered;
    emit curDeliveredChanged();
}

int modelItem::avgReturned() const
{
    return m_avgReturned;
}

void modelItem::setAvgReturned(int newAvgReturned)
{
    if (m_avgReturned == newAvgReturned)
        return;
    m_avgReturned = newAvgReturned;
    emit avgReturnedChanged();
}

int modelItem::curReturned() const
{
    return m_curReturned;
}

void modelItem::setCurReturned(int newCurReturned)
{
    if (m_curReturned == newCurReturned)
        return;
    m_curReturned = newCurReturned;
    emit curReturnedChanged();
}

int modelItem::avgGas() const
{
    return m_avgGas;
}

void modelItem::setAvgGas(int newAvgGas)
{
    if (m_avgGas == newAvgGas)
        return;
    m_avgGas = newAvgGas;
    emit avgGasChanged();
}

int modelItem::curGas() const
{
    return m_curGas;
}

void modelItem::setCurGas(int newCurGas)
{
    if (m_curGas == newCurGas)
        return;
    m_curGas = newCurGas;
    emit curGasChanged();
}

bool modelItem::setData(int delivered, int returned, int gas, int solar,int used, bool calcRet, bool isToday){

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

        this->setAvgReturned(this->rawAvgReturned / divider2);
        this->setAvgSolar(this->rawSolar / divider2);

    }else{

    }

    this->rawGasUsed = this->rawGasUsed + gas;
    this->rawResult = this->rawResult + (delivered - returned);
    this->rawUsed = this->rawUsed + used;

    this->setAvgResult((this->rawResult / divider));
    this->setAvgDelivered((this->RawAvgDelivered / divider));
    this->setAvgGas((this->rawGasUsed / divider));
    this->setAvgUsed((this->rawUsed / divider));


    if(this->todayModel){
        m_curCount = m_curCount-1;
        if((isToday) && (m_curCount >= 0)){
            this->setCurDelivered(m_avgDelivered);
            this->setCurGas(m_avgGas);
            this->setCurReturned(m_avgReturned);
            this->setCurResult(m_avgDelivered - m_avgReturned);
            this->setCurSolar(m_avgSolar);
            this->setCurUsed(m_avgUsed);
            this->currentSet = true;
            ret = true;
        }
    }else{

    m_curCount = m_curCount-1;

    if((m_curCount <= 0) && (this->currentSet == false)){
        this->setCurDelivered(m_avgDelivered);
        this->setCurGas(m_avgGas);
        this->setCurReturned(m_avgReturned);
        this->setCurResult(m_avgDelivered - m_avgReturned);
        this->setCurSolar(m_avgSolar);
        this->setCurUsed(m_avgUsed);
        this->currentSet = true;
        ret = true;
    }
    }

    if(m_curCount > 0){
        ret = true;
    }

    return ret;

}

int modelItem::curResult() const
{
    return m_curResult;
}

void modelItem::setCurResult(int newCurResult)
{
    if (m_curResult == newCurResult)
        return;
    m_curResult = newCurResult;
    emit curResultChanged();
}

int modelItem::avgResult() const
{
    return m_avgResult;
}

void modelItem::setAvgResult(int newAvgResult)
{
    if (m_avgResult == newAvgResult)
        return;
    m_avgResult = newAvgResult;
    emit avgResultChanged();
}

int modelItem::avgSolar() const
{
    return m_avgSolar;
}

void modelItem::setAvgSolar(int newAvgSolar)
{
    if (m_avgSolar == newAvgSolar)
        return;
    m_avgSolar = newAvgSolar;
    emit avgSolarChanged();
}

int modelItem::curSolar() const
{
    return m_curSolar;
}

void modelItem::setCurSolar(int newCurSolar)
{
    if (m_curSolar == newCurSolar)
        return;
    m_curSolar = newCurSolar;
    emit curSolarChanged();
}

int modelItem::avgUsed() const
{
    return m_avgUsed;
}

void modelItem::setAvgUsed(int newAvgUsed)
{
    if (m_avgUsed == newAvgUsed)
        return;
    m_avgUsed = newAvgUsed;
    emit avgUsedChanged();
}

int modelItem::curUsed() const
{
    return m_curUsed;
}

void modelItem::setCurUsed(int newCurUsed)
{
    if (m_curUsed == newCurUsed)
        return;
    m_curUsed = newCurUsed;
    emit curUsedChanged();
}

bool modelItem::isCurrent() const
{
    return m_isCurrent;
}

void modelItem::setIsCurrent(bool newIsCurrent)
{
    if (m_isCurrent == newIsCurrent)
        return;
    m_isCurrent = newIsCurrent;
    emit isCurrentChanged();
}
