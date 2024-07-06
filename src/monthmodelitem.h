#ifndef MONTHMODELITEM_H
#define MONTHMODELITEM_H

#include <QObject>
#include <QDate>

class monthModelItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged);
    Q_PROPERTY(int avgDelivered READ avgDelivered WRITE setAvgDelivered NOTIFY avgDeliveredChanged);
    Q_PROPERTY(int curDelivered READ curDelivered WRITE setCurDelivered NOTIFY curDeliveredChanged);
    Q_PROPERTY(int avgReturned READ avgReturned WRITE setAvgReturned NOTIFY avgReturnedChanged);
    Q_PROPERTY(int curReturned READ curReturned WRITE setCurReturned NOTIFY curReturnedChanged);
    Q_PROPERTY(int curResult READ curResult WRITE setCurResult NOTIFY curResultChanged);
    Q_PROPERTY(int avgResult READ avgResult WRITE setAvgResult NOTIFY avgResultChanged);
    Q_PROPERTY(int avgGas READ avgGas WRITE setAvgGas NOTIFY avgGasChanged);
    Q_PROPERTY(int curGas READ curGas WRITE setCurGas NOTIFY curGasChanged);
    Q_PROPERTY(int avgSolar READ avgSolar WRITE setAvgSolar NOTIFY avgSolarChanged);
    Q_PROPERTY(int curSolar READ curSolar WRITE setCurSolar NOTIFY curSolarChanged);
      Q_PROPERTY(int avgUsed READ avgUsed WRITE setAvgUsed NOTIFY avgUsedChanged);
    Q_PROPERTY(int curUsed READ curUsed WRITE setCurUsed NOTIFY curUsedChanged);
     Q_PROPERTY(bool isCurrent READ isCurrent WRITE setIsCurrent NOTIFY isCurrentChanged);

public:
    explicit monthModelItem(int year, int month, QObject *parent = nullptr);

    int month;
    int year;

    QString label() const;
    void setLabel(const QString &newLabel);

    int avgDelivered() const;
    void setAvgDelivered(int newAvgDelivered);

    int curDelivered() const;
    void setCurDelivered(int newCurDelivered);

    int avgReturned() const;
    void setAvgReturned(int newAvgReturned);

    int curReturned() const;
    void setCurReturned(int newCurReturned);

    int avgGas() const;
    void setAvgGas(int newAvgGas);

    int curGas() const;
    void setCurGas(int newCurGas);

    bool setData(int delivered, int returned, int gas, bool calc_returned,int solar,int used, bool isCurrent);

    int curResult() const;
    void setCurResult(int newCurResult);

    int avgResult() const;
    void setAvgResult(int newAvgResult);

    int avgSolar() const;
    void setAvgSolar(int newAvgSolar);

    int curSolar() const;
    void setCurSolar(int newCurSolar);

    int curUsed() const;
    void setCurUsed(int newCurUsed);

    int avgUsed() const;
    void setAvgUsed(int newAvgUsed);

    bool isCurrent() const;
    void setIsCurrent(bool newIsCurrent);

signals:

    void labelChanged();
    void avgDeliveredChanged();
    void curDeliveredChanged();

    void avgReturnedChanged();

    void curReturnedChanged();

    void avgGasChanged();

    void curGasChanged();

    void curResultChanged();

    void avgResultChanged();

    void avgSolarChanged();

    void curSolarChanged();

    void curUsedChanged();

    void avgUsedChanged();

    void isCurrentChanged();

private:

    QString m_label;
    int m_avgDelivered;
    int m_curDelivered;
    int m_avgReturned;
    int m_curReturned;
    int m_avgGas;
    int m_curGas;

    int m_curCount;
    int m_curCountSet;
    bool currentSet;
    int avgCount;
    int avgRetCount;
    qint64 RawAvgDelivered;
    qint64 rawAvgReturned;
    qint64 rawGasUsed;
    qint64 rawResult;
    qint64 rawSolar;
    qint64 rawUsed;
    int m_curResult;
    int m_avgResult;
    QDate m_date;

    QString getMonthName(int month);
    int m_avgSolar;
    int m_curSolar;
    int m_curUsed;
    int m_avgUsed;
    bool m_isCurrent;
};

#endif // MONTHMODELITEM_H
