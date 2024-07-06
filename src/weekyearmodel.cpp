#include "weekyearmodel.h"

WeekYearModel::WeekYearModel(DataContainer *data, QObject *parent)
    : QAbstractListModel{parent}
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    this->dataContainer = data;
    m_pwrMax = -9999;
    m_pwrMin = 9999;
    m_gasMax = -9999;
    m_gasMin = 9999;
    this->m_pwrMode = 0;
    connect(this->dataContainer, SIGNAL(loadedChanged()), this, SLOT(loadModel()));
}

int WeekYearModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}

int WeekYearModel::count() const{
    return m_data.count();
}

QVariant WeekYearModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= m_data.count()) {
        return QVariant();
    }
    const modelItem  *item = m_data.at(row);
    /*
    switch(role) {
    case IDRole:
        return job->msid();
    case JobNoRole:
        return job->no();
    case TitleRole:
        return job->title();
    case ClientRole:
        return job->client();
    case DateRole:
        return job->jobDate();
    case StartDateRole:
        return job->jobStartDate();
    case PickDateRole:
        return job->jobPickDate();
    case StatusColorRole:
        return job->statusColor();
    }
*/
    return QVariant();
}

QHash<int, QByteArray> WeekYearModel::roleNames() const
{
    auto roles = QAbstractListModel::roleNames();
    roles[IDRole] = "ID";
    roles[JobNoRole] = "JobNo";
    roles[TitleRole] = "Title";
    roles[ClientRole] = "Client";
    roles[DateRole] = "Date";
    roles[StartDateRole] = "StartDate";
    roles[PickDateRole] = "PickDate";
    roles[StatusColorRole] = "StatusColor";
    return roles;
}

void WeekYearModel::loadModel(){
    // m.lock();
    m.lock();

    /*
    int curDay = 0;
    DataItem *item = NULL;
    if(this->dataContainer->items.size() > 0){
        curDay = this->dataContainer->items[0]->m_day;
        item = this->dataContainer->items[0];
    }

    for(int i = 1; i < this->dataContainer->items.size(); i++){
        if(this->dataContainer->items[i]->m_day != curDay){
            // nieuwe dag
            if(item != NULL){
                DataItem *dItem = new DataItem(item->m_day, item->m_month, item->m_year, item->m_hour, item->m_weekday, item->m_total, item->m_gas, item->m_totalReturned);
                this->m_dataItems.push_back(dItem);
            }
            item = this->dataContainer->items[i];
        }
    }

    int powerDeliverd = 0;
    int powerReturned = 0;
    int gasUsed = 0;

    if(this->m_dataItems.count() > 0){
        powerDeliverd = this->m_dataItems[0]->m_total;
        powerReturned = this->m_dataItems[0]->m_totalReturned;
        gasUsed = this->m_dataItems[0]->m_gas;
    }

    for(int i = 0; i < this->m_dataItems.count(); i++){
        this->m_dataItems[i]->powerDeliverd = powerDeliverd - this->m_dataItems[i]->m_total;
        this->m_dataItems[i]->powerReturnd = powerReturned - this->m_dataItems[i]->m_totalReturned;
        this->m_dataItems[i]->gasUsed = gasUsed - this->m_dataItems[i]->m_gas;
        powerDeliverd = this->m_dataItems[i]->m_total;
        powerReturned = this->m_dataItems[i]->m_totalReturned;
        gasUsed = this->m_dataItems[i]->m_gas;
    }
*/






    /*
    for(int i = 1; i < dataContainer->items.size(); i++){
        DataItem *item = dataContainer->items[i];
        bool calcRet = true;
        if(item->m_totalReturned == 0){
            calcRet = false;
        }
        this->m_data[item->m_hour]->setData(item->powerDeliverd, item->powerReturnd, item->gasUsed, calcRet);
    }
*/



    beginResetModel();
    for(int i = 0; i < m_data.size(); i++){
        this->m_data[i]->deleteLater();
    }
    this->m_data.clear();
    this->m_data.shrink_to_fit();

    /*
    for(int i = 0; i < 7; i++){
        modelItem *item = new modelItem(1);

        item->setLabel(day);
        this->m_data.push_back(item);
    }

    for(int i = 1; i < dataContainer->items.size(); i++){
        DataItem *item = dataContainer->items[i];
        bool calcRet = true;
        if(item->m_totalReturned == 0){
            calcRet = false;
        }
        this->m_data[item->m_weekday]->setData(item->powerDeliverd, item->powerReturnd, item->gasUsed, calcRet);
    }
*/


    /*
    for(int i = 0; i < 24; i++){
        modelItem *item = new modelItem(24);
        item->setLabel(this->getDay(startDay));
        item->WeekDay = startDay;
        this->m_data.push_back(item);
        startDay = startDay - 1;
        if(startDay < 0){
            startDay = 6;
        }
    }
    */

    int currentWeek = QDate::currentDate().weekNumber();
    int currentYear = QDate::currentDate().year();

    for(int i = 0; i < 53; i++){
        modelItem *newitem = new modelItem(24 * 7, false);
        newitem->setLabel(QString::number(i + 1));

        newitem->Week = i + 1;
        if(newitem->Week <= currentWeek){
            newitem->Year = currentYear;
        }else{
            newitem->Year = currentYear - 1;
        }
        //newitem->Year = item->m_year;
        //newitem->setLabel(QString::number(newitem->Year));
        // newitem->Year = item->m_year;
        newitem->todayModel = true;
        this->m_data.push_back(newitem);
    }

    for(int i = 1; i < dataContainer->items.size(); i++){
        DataItem *item = dataContainer->items[i];
        bool calcRet = true;
        if(item->m_totalReturned == 0){
            calcRet = false;
        }

        QDate datum = QDate(item->m_year, 1, 1).addDays(item->m_day);
        if(!datum.isValid()){
            int bp = 0;
            bp++;
        }else{
            int weekNo = datum.weekNumber();

            for(int y = 0; y < m_data.size(); y++){
                if(m_data[y]->Week == weekNo){
                    bool isToday = false;
                    if((m_data[y]->Week == weekNo) && (m_data[y]->Year == item->m_year)){
                        isToday = true;
                    }
                    if(m_data[y]->setData(item->powerDeliverd, item->powerReturnd, item->gasUsed, item->solarResult,item->powerUsed, calcRet, isToday)){
                        break;
                    }
                }
            }
        }

    }

    this->setMinMax();
    this->setCount(m_data.size());
    endResetModel();
    m.unlock();
}

QString WeekYearModel::getDay(int dayOfWeek){
    QString day = "Sun";
    if(dayOfWeek == 1){
        day = "Mon";
    }else if(dayOfWeek == 2){
        day = "Tue";
    }else if(dayOfWeek == 3){
        day = "Wed";
    }else if(dayOfWeek == 4){
        day = "Thu";
    }else if(dayOfWeek == 5){
        day = "Fri";
    }else if(dayOfWeek == 6){
        day = "Sat";
    }
    return day;
}

void WeekYearModel::setMinMax(){
    m_pwrMax = -999999;
    m_pwrMin = 999999;
    m_gasMax = -999999;
    m_gasMin = 999999;

    for(int i = 0; i < m_data.size(); i++){


        if(this->m_pwrMode == 0){
            //result
            this->setPwrMax(m_data[i]->curResult());
            this->setPwrMax(m_data[i]->avgResult());
            this->setPwrMin(m_data[i]->curResult());
            this->setPwrMin(m_data[i]->avgResult());
        }else if(m_pwrMode == 1){
            //used
            this->setPwrMax(m_data[i]->avgDelivered());
            this->setPwrMax(m_data[i]->curDelivered());
            this->setPwrMin(m_data[i]->avgDelivered());
            this->setPwrMin(m_data[i]->curDelivered());
        }else if(m_pwrMode == 2){
            this->setPwrMax(m_data[i]->avgReturned());
            this->setPwrMax(m_data[i]->curReturned());
            this->setPwrMin(m_data[i]->avgReturned());
            this->setPwrMin(m_data[i]->curReturned());
        }else if(m_pwrMode == 3){
            this->setGasMax(m_data[i]->curGas());
            this->setGasMax(m_data[i]->avgGas());
            this->setGasMin(m_data[i]->curGas());
            this->setGasMin(m_data[i]->avgGas());
            this->setPwrMax(m_data[i]->curGas());
            this->setPwrMax(m_data[i]->avgGas());
            this->setPwrMin(m_data[i]->curGas());
            this->setPwrMin(m_data[i]->avgGas());
        }else if(m_pwrMode == 4){
            this->setPwrMax(m_data[i]->curSolar());
            this->setPwrMax(m_data[i]->avgSolar());
            this->setPwrMin(m_data[i]->curSolar());
            this->setPwrMin(m_data[i]->avgSolar());
        }else if(m_pwrMode == 5){
            this->setPwrMax(m_data[i]->curUsed());
            this->setPwrMax(m_data[i]->avgUsed());
            this->setPwrMin(m_data[i]->curUsed());
            this->setPwrMin(m_data[i]->avgUsed());
        }
    }

}

modelItem *WeekYearModel::get(int row) const{
    //QMutexLocker lock( &m);
    if((row < 0) || (row >= m_data.count())){
        return NULL;
    }
    return m_data[row];
}





int WeekYearModel::pwrMax() const
{
    return m_pwrMax;
}

void WeekYearModel::setPwrMax(int newPwrMax)
{
    if (m_pwrMax == newPwrMax)
        return;
    if(m_pwrMax > newPwrMax){
        return;
    }
    m_pwrMax = newPwrMax;
    emit pwrMaxChanged();
}

int WeekYearModel::pwrMin() const
{
    return m_pwrMin;
}

void WeekYearModel::setPwrMin(int newPwrMin)
{
    if (m_pwrMin == newPwrMin)
        return;
    if(m_pwrMin < newPwrMin){
        return;
    }
    if(newPwrMin > 0){
        newPwrMin = 0;
    }
    m_pwrMin = newPwrMin;
    emit pwrMinChanged();
}

int WeekYearModel::gasMax() const
{
    return m_gasMax;
}

void WeekYearModel::setGasMax(int newGasMax)
{
    if (m_gasMax == newGasMax)
        return;
    if(m_gasMax > newGasMax){
        return;
    }
    m_gasMax = newGasMax;
    emit gasMaxChanged();
}

int WeekYearModel::gasMin() const
{
    return m_gasMin;
}

void WeekYearModel::setGasMin(int newGasMin)
{
    if (m_gasMin == newGasMin)
        return;
    if(m_gasMax < newGasMin){
        return;
    }
    m_gasMin = newGasMin;
    emit gasMinChanged();
}

int WeekYearModel::pwrMode() const
{
    return m_pwrMode;
}

void WeekYearModel::setPwrMode(int newPwrMode)
{
    m_pwrMode++;
    if(m_pwrMode == 6){
        m_pwrMode = 0;
    }
    this->setMinMax();
    emit this->pwrModeChanged();
    emit this->pwrModeTextChanged();

}

QString WeekYearModel::pwrModeText() const
{
    switch(m_pwrMode){
    case 0:
        return "Result";
    case 1:
        return "Delivered";
    case 2:
        return "Returned";
    case 3:
        return "Gas";
    case 4:
        return "Solar Panels";
    case 5:
        return "Used";
    }

    return m_pwrModeText;
}

void WeekYearModel::setPwrModeText(const QString &newPwrModeText)
{
    if (m_pwrModeText == newPwrModeText)
        return;
    m_pwrModeText = newPwrModeText;
    emit pwrModeTextChanged();
}

void WeekYearModel::setCount(int newCount)
{
    if (m_count == newCount)
        return;
    m_count = newCount;
    emit countChanged();
}
