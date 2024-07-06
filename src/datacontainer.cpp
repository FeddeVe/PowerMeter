#include "datacontainer.h"

DataContainer::DataContainer(QObject *parent)
    : QObject{parent}
{
    this->m_loaded = false;
    this->m_isLoading = true;
    this->network = new QNetworkAccessManager(this);
    connect(this->network, &QNetworkAccessManager::finished,this, &DataContainer::replyFinished);

    this->tmr = new QTimer(this);
    connect(this->tmr, SIGNAL(timeout()), this, SLOT(tmrTick()));

    this->tmr->start(65000);

   this->loadData();
}

void DataContainer::tmrTick(){
   if(QTime::currentTime().hour() != this->lastHourSync){
       this->loadData();
   }
}

void DataContainer::loadData(){
   this->setIsLoading(true);
   this->lastHourSync = QTime::currentTime().hour();
    QNetworkRequest request;
    request.setUrl(QUrl(QUrl("http://192.168.2.251/scr/power_load.php")));

    request.setRawHeader("Access-Control-Allow-Origin", "*");
    request.setRawHeader("Access-Control-Allow-Credentials", "false");
    request.setRawHeader("Access-Control-Allow-Methods", "GET,HEAD,OPTIONS,POST,PUT");
    request.setRawHeader("Access-Control-Allow-Headers", "Access-Control-Allow-Headers, Origin,Accept, X-Requested-With, Content-Type, Access-Control-Request-Method, Access-Control-Request-Headers");

    QNetworkReply* reply = this->network->get(request);
}

void DataContainer::replyFinished(QNetworkReply *reply){
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


        for(int i = 0; i < this->items.size(); i++){
            this->items[i]->deleteLater();
        }
        this->items.clear();
        this->items.shrink_to_fit();

        auto data = reply->readAll();
      //  qDebug() << data;

        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonArray arr = doc.array();

        for(int i = 0; i < arr.size(); i++){
            QJsonObject x = arr[i].toObject();

            int day = x.value("day").toString().toInt();
            int gas = x.value("gas").toString().toInt();
            int hour = x.value("hour").toString().toInt();
            int id = x.value("id").toString().toInt();
            int month = x.value("month").toString().toInt() + 1;
            int total = x.value("total").toString().toInt();
            int totalReturned = x.value("totalReturned").toString().toInt();
            int weekday = x.value("weekday").toString().toInt();
            int year = x.value("year").toString().toInt() + 1900;
            int solarLife = x.value("Solar").toString().toInt();

            DataItem *item = new DataItem(day, month, year, hour, weekday, total, gas, totalReturned, solarLife);
            this->items.push_back(item);

            int bp = 0;
            bp++;
        }

        int powerDeliverd = 0;
        int powerReturned = 0;
        int gasUsed = 0;
        int solarRes = 0;
        int used = 0;

        if(this->items.count() > 0){
            powerDeliverd = this->items[this->items.count() - 1]->m_total;
            powerReturned = this->items[this->items.count() - 1]->m_totalReturned;
            gasUsed = this->items[this->items.count() - 1]->m_gas;
            solarRes = this->items[this->items.count() - 1]->m_solarLifeTime;
        }

        int index = this->items.count();
        while(index > 0){
            index = index - 1;
            this->items[index]->powerDeliverd =  this->items[index]->m_total - powerDeliverd;
            this->items[index]->powerReturnd = this->items[index]->m_totalReturned - powerReturned;
            this->items[index]->gasUsed = this->items[index]->m_gas - gasUsed;
            this->items[index]->solarResult =  this->items[index]->m_solarLifeTime - solarRes;
            this->items[index]->powerUsed = this->items[index]->solarResult + this->items[index]->powerDeliverd - this->items[index]->powerReturnd;
            powerDeliverd = this->items[index]->m_total;
            powerReturned = this->items[index]->m_totalReturned;
            gasUsed = this->items[index]->m_gas;
            solarRes = this->items[index]->m_solarLifeTime;
        }

        this->lastHourSync = QTime::currentTime().hour();

        emit this->loadedChanged();

    }

    this->setIsLoading(false);
}

void DataContainer::load(){
    this->setIsLoading(true);
    this->loadData();
}

bool DataContainer::loaded() const
{
    return m_loaded;
}

void DataContainer::setLoaded(bool newLoaded)
{
    if (m_loaded == newLoaded)
        return;
    m_loaded = newLoaded;
    emit loadedChanged();
}

bool DataContainer::isLoading() const
{
    return m_isLoading;
}

void DataContainer::setIsLoading(bool newIsLoading)
{
    if (m_isLoading == newIsLoading)
        return;
    m_isLoading = newIsLoading;
    emit isLoadingChanged();
}
