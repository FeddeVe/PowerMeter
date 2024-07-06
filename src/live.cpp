#include "live.h"

Live::Live(QObject *parent)
    : QObject{parent}
{



    m_delivered = 0;
    m_returned = 0;
    m_result = 0;
    m_t1 = 0;
    m_t2 = 0;
    m_total = 0;
    m_retT1 = 0;
    m_retT2 = 0;
    m_retTotal = 0;
    m_l1Volt = 0;
    m_l2Volt = 0;
    m_l3Volt = 0;
    m_l1Amp = 0;
    m_l2Amp = 0;
    m_l3Amp = 0;
    m_gas = 0;

    for(int i = 0; i < 10; i++){
        this->flatten_delivered[i] = 0;
    }
    this->flatten_delivered_index = 0;

    raw_deliverd = 0;
    raw_returned = 0;
    raw_total = 0;
    des_deliverd = 0;
    des_returned = 0;
    des_total = 0;
    delta_delivered = 0;
    delta_returned = 0;
    delta_total = 0;

    this->firstShot = true;

    this->network = new QNetworkAccessManager(this);

    connect(this->network, &QNetworkAccessManager::finished,this, &Live::replyFinished);


    this->loadTimer = new QTimer(this);
    connect(this->loadTimer, SIGNAL(timeout()), this, SLOT(loadTimerTick()));
    this->loadTimerTick();
    this->loadTimer->start(5000);

    this->AnimTimer = new QTimer(this);
    connect(this->AnimTimer, SIGNAL(timeout()), this, SLOT(animTimerTick()));
    this->AnimTimer->start(100);
}

void Live::loadTimerTick(){
    QString pData = "item={\"item\":\"power\"}";
    QNetworkRequest request;
    request.setUrl(QUrl(QUrl("http://192.168.2.251/scr/tcp.php?"+ pData)));

    request.setRawHeader("Access-Control-Allow-Origin", "*");
    request.setRawHeader("Access-Control-Allow-Credentials", "false");
    request.setRawHeader("Access-Control-Allow-Methods", "GET,HEAD,OPTIONS,POST,PUT");
    request.setRawHeader("Access-Control-Allow-Headers", "Access-Control-Allow-Headers, Origin,Accept, X-Requested-With, Content-Type, Access-Control-Request-Method, Access-Control-Request-Headers");

    QNetworkReply* reply = this->network->get(request);
}

void Live::animTimerTick(){
    m.lock();
    int delivered = 0;
    int returned = 0;
    if(this->des_deliverd - this->raw_deliverd > this->delta_delivered){
        this->raw_deliverd = this->raw_deliverd + this->delta_delivered;
        delivered = this->raw_deliverd;
       // this->setDelivered(this->raw_deliverd);
    }else if(this->des_deliverd - this->raw_deliverd < -this->delta_delivered){
        this->raw_deliverd = this->raw_deliverd - this->delta_delivered;
       // this->setDelivered(this->raw_deliverd);
        delivered = this->raw_deliverd;
    }else{
        delivered = this->des_deliverd;
       // this->setDelivered(this->des_deliverd);
    }

    if(this->des_returned - this->raw_returned > this->delta_returned){
        this->raw_returned = this->raw_returned + this->delta_returned;
        returned = this->raw_returned;
       // this->setReturned(this->raw_returned);
    }else if(this->des_returned - this->raw_returned < -this->delta_returned){
        this->raw_returned = this->raw_returned - this->delta_returned;
        returned = this->raw_returned;
      //  this->setReturned(this->raw_returned);
    }else{
        returned = this->des_returned;
      //  this->setReturned(this->des_returned);
    }

    this->setLiveVal(delivered - returned);


    m.unlock();
}

void Live::replyFinished(QNetworkReply *reply){
    if (reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->errorString();
    }
    else
    {
        qDebug() << reply->header(QNetworkRequest::ContentTypeHeader).toString();
        qDebug() << reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString();
        qDebug() << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
        qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();


        auto data = reply->readAll();
        qDebug() << data;

        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject obj = doc.object();

        m.lock();
        //this->setDelivered(obj.value("current").toInt());

        if(this->firstShot){
            for(int i = 0; i < 10; i++){
                this->flatten_delivered[i] = obj.value("current").toInt();
            }
        }else{
            this->flatten_delivered[this->flatten_delivered_index] = obj.value("current").toInt();
            this->flatten_delivered_index++;
            if(this->flatten_delivered_index >= 10){
                this->flatten_delivered_index = 0;
            }
        }
        qint64 tmp = 0;
        for(int i = 0; i < 10; i++){
            tmp = tmp + this->flatten_delivered[i];
        }


      //  this->des_deliverd = tmp / 10;
        this->des_deliverd = obj.value("current").toInt();
        this->delta_delivered = (this->des_deliverd - this->raw_deliverd) / 50;
        if(this->delta_delivered < 0){
            this->delta_delivered = this->delta_delivered * -1;
        }
        this->des_returned = obj.value("currentReturned").toInt();
        this->delta_returned = (this->des_returned - this->raw_returned) / 50;
        if(this->delta_returned < 0){
            this->delta_returned = this->delta_returned * -1;
        }

        this->setDelivered(this->des_deliverd);
        this->setReturned(this->des_returned);

        this->setT1(obj.value("tarif_1").toInt());
        this->setT2(obj.value("tarif_2").toInt());
        this->setTotal(obj.value("tarif_total").toInt());
        this->setRetT1(obj.value("returned_1").toInt());
        this->setRetT2(obj.value("returend_2").toInt());
        this->setRetTotal(obj.value("returned_total").toInt());
        this->setL1Volt(obj.value("volt_l1").toInt());
        this->setL2Volt(obj.value("volt_l2").toInt());
        this->setL3Volt(obj.value("volt_l3").toInt());
        this->setL1Amp(obj.value("amp_l1").toInt());
        this->setL2Amp(obj.value("amp_l2").toInt());
        this->setL3Amp(obj.value("amp_l3").toInt());
        this->setGas(obj.value("gas").toInt());
        this->setSolar(obj.value("cur_solar").toInt());


        if(firstShot){
            firstShot = false;
            this->raw_deliverd = this->des_deliverd;
            this->setDelivered(this->raw_deliverd);
            this->raw_returned = this->des_returned;
            this->setReturned(this->raw_returned);
        }

        m.unlock();

        reply->deleteLater();
    }
}

QString Live::delivered() const
{
    float retVal = round(m_delivered * 100) / 100;
    return QString::number(retVal) + " w" ;
}

void Live::setDelivered(const int32_t &newDelivered)
{

    if (m_delivered == newDelivered)
        return;
    m_delivered = newDelivered;
    //m_result = m_delivered - m_returned;
    this->setResult(m_delivered - m_returned);
    emit deliveredChanged();

}

QString Live::returned() const
{
    float retVal = round(m_returned * 100) / 100;
    return QString::number(retVal) + " w" ;
}

void Live::setReturned(const int32_t &newReturned)
{

    if (m_returned == newReturned)
        return;
    m_returned = newReturned;
   // m_result = m_delivered - m_returned;
    this->setResult(m_delivered - m_returned);
    emit returnedChanged();

}

QString Live::result() const
{
    float retVal = round(m_result * 100) / 100;
    return QString::number(retVal) + " w" ;

}

void Live::setResult(const int &newResult)
{

    if (m_result == newResult)
        return;
    m_result = newResult;
    emit resultChanged();

}

QString Live::t1() const
{
    float retVal = round(m_t1) / 1000;
    return QString::number(retVal) + " kwh" ;
}

void Live::setT1(const uint32_t &newT1)
{
    if (m_t1 == newT1)
        return;
    m_t1 = newT1;
    emit t1Changed();
}

QString Live::t2() const
{
    float retVal = round(m_t2) / 1000;
    return QString::number(retVal) + " kwh" ;
}

void Live::setT2(const uint32_t &newT2)
{

    if (m_t2 == newT2)
        return;
    m_t2 = newT2;
    emit t2Changed();

}

QString Live::total() const
{
    float retVal = round(m_total) / 1000;
    return QString::number(retVal) + " kwh" ;
}

void Live::setTotal(const uint32_t &newTotal)
{

    if (m_total == newTotal)
        return;
    m_total = newTotal;
    emit totalChanged();

}

QString Live::retT1() const
{
    float retVal = round(m_retT1) / 1000;
    return QString::number(retVal) + " kwh" ;
}

void Live::setRetT1(const uint32_t &newRetT1)
{

    if (m_retT1 == newRetT1)
        return;
    m_retT1 = newRetT1;
    emit retT1Changed();

}

QString Live::retT2() const
{
    float retVal = round(m_retT2) / 1000;
    return QString::number(retVal) + " kwh" ;
}

void Live::setRetT2(const uint32_t &newRetT2)
{

    if (m_retT2 == newRetT2)
        return;
    m_retT2 = newRetT2;
    emit retT2Changed();

}

QString Live::retTotal() const
{
    float retVal = round(m_retTotal) / 1000;
    return QString::number(retVal) + " kwh" ;
}

void Live::setRetTotal(const uint32_t &newRetTotal)
{

    if (m_retTotal == newRetTotal)
        return;
    m_retTotal = newRetTotal;
    emit retTotalChanged();

}

QString Live::l1Volt() const
{
    float retVal = round(m_l1Volt) / 1000;
    return QString::number(retVal) + " v" ;
}

void Live::setL1Volt(const uint32_t &newL1Volt)
{

    if (m_l1Volt == newL1Volt)
        return;
    m_l1Volt = newL1Volt;
    emit l1VoltChanged();

}

QString Live::l2Volt() const
{
    float retVal = round(m_l2Volt) / 1000;
    return QString::number(retVal) + " v" ;
}

void Live::setL2Volt(const uint32_t &newL2Volt)
{

    if (m_l2Volt == newL2Volt)
        return;
    m_l2Volt = newL2Volt;
    emit l2VoltChanged();

}

QString Live::l3Volt() const
{
    float retVal = round(m_l3Volt) / 1000;
    return QString::number(retVal) + " v" ;
}

void Live::setL3Volt(const uint32_t &newL3Volt)
{

    if (m_l3Volt == newL3Volt)
        return;
    m_l3Volt = newL3Volt;
    emit l3VoltChanged();

}

QString Live::l1Amp() const
{
    float retVal = round(m_l1Amp) / 1000;
    return QString::number(retVal) + " A" ;
}

void Live::setL1Amp(const uint32_t &newL1Amp)
{

    if (m_l1Amp == newL1Amp)
        return;
    m_l1Amp = newL1Amp;
    emit l1AmpChanged();

}

QString Live::l2Amp() const
{
    float retVal = round(m_l2Amp) / 1000;
                         return QString::number(retVal) + " A" ;
}

void Live::setL2Amp(const uint32_t &newL2Amp)
{

    if (m_l2Amp == newL2Amp)
        return;
    m_l2Amp = newL2Amp;
    emit l2AmpChanged();

}

QString Live::l3Amp() const
{
                         float retVal = round(m_l3Amp) / 1000;
                         return QString::number(retVal) + " A" ;
}

void Live::setL3Amp(const uint32_t &newL3Amp)
{

    if (m_l3Amp == newL3Amp)
        return;
    m_l3Amp = newL3Amp;
    emit l3AmpChanged();

}

QString Live::gas() const
{
                         float retVal = round(m_gas) / 1000;
                         return QString::number(retVal) + " m3" ;
}

void Live::setGas(const uint32_t &newGas)
{

    if (m_gas == newGas)
        return;
    m_gas = newGas;
    emit gasChanged();

}

QString Live::liveVal() const
{
    return QString::number(m_liveVal) + " w";
}

void Live::setLiveVal(const int &newLiveVal)
{
    if (m_liveVal == newLiveVal)
        return;
    m_liveVal = newLiveVal;
    emit liveValChanged();
}

QString Live::solar() const
{
    return QString::number(m_solar) + " w";
}

void Live::setSolar(const uint32_t &newSolar)
{
    if (m_solar == newSolar)
        return;
    m_solar = newSolar;
    emit solarChanged();
}
