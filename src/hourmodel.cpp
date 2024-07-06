#include "hourmodel.h"

hourModel::hourModel(DataContainer *data, QObject *parent)
    : QAbstractListModel{parent}
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    this->dataContainer = data;
    m_pwrMax = -9999;
    m_pwrMin = 9999;
    m_gasMax = -9999;
    m_gasMin = 9999;
    this->m_pwrMode = 1;
    connect(this->dataContainer, SIGNAL(loadedChanged()), this, SLOT(loadModel()));
}

int hourModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}

int hourModel::count() const{
    return m_data.count();
}

QVariant hourModel::data(const QModelIndex &index, int role) const
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

QHash<int, QByteArray> hourModel::roleNames() const
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

void hourModel::loadModel(){
    // m.lock();
    m.lock();


    beginResetModel();
    for(int i = 0; i < m_data.size(); i++){
        this->m_data[i]->deleteLater();
    }
    this->m_data.clear();
    this->m_data.shrink_to_fit();

    int nu = QTime::currentTime().hour();

    for(int i = 0; i < 24; i++){

        modelItem *item = new modelItem(7, false);
        item->setLabel(QString::number(i) +":00");
        this->m_data.push_back(item);
    }

    for(int i = 1; i < dataContainer->items.size(); i++){
        DataItem *item = dataContainer->items[i];
        bool calcRet = true;
        if(item->m_totalReturned == 0){
            calcRet = false;
        }
        this->m_data[item->m_hour]->setData(item->powerDeliverd, item->powerReturnd, item->gasUsed,item->solarResult,item->powerUsed, calcRet);
    }

    this->setMinMax();


    /*
    int index = 0;
    Job *j = jobs->getJob(index);
    while(j!=NULL){
        try{
            if((j->no().toUpper().contains(sval)) || (j->title().toUpper().contains(sval)) || (j->client().toUpper().contains(sval))){
                this->m_data.push_back(j);
            }
        }catch(...){
            int bp = 0;
            bp++;
        }
        index++;
        j = jobs->getJob(index);
        // emit this->dataChanged(index(0),index(0);
    }
    //this->m_data.push_back(jobs->editJob);
    this->SortList();
*/
    this->setCount(m_data.size());
    endResetModel();
    m.unlock();
}

void hourModel::setMinMax(){
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

modelItem *hourModel::get(int row) const{
    //QMutexLocker lock( &m);
    if((row < 0) || (row >= m_data.count())){
        return NULL;
    }
    return m_data[row];
}





int hourModel::pwrMax() const
{
    return m_pwrMax;
}

void hourModel::setPwrMax(int newPwrMax)
{
    if (m_pwrMax == newPwrMax)
        return;
    if(m_pwrMax > newPwrMax){
        return;
    }
    m_pwrMax = newPwrMax;
    emit pwrMaxChanged();
}

int hourModel::pwrMin() const
{
    return m_pwrMin;
}

void hourModel::setPwrMin(int newPwrMin)
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

int hourModel::gasMax() const
{
    return m_gasMax;
}

void hourModel::setGasMax(int newGasMax)
{
    if (m_gasMax == newGasMax)
        return;
    if(m_gasMax > newGasMax){
        return;
    }
    m_gasMax = newGasMax;
    emit gasMaxChanged();
}

int hourModel::gasMin() const
{
    return m_gasMin;
}

void hourModel::setGasMin(int newGasMin)
{
    if (m_gasMin == newGasMin)
        return;
    if(m_gasMax < newGasMin){
        return;
    }
    m_gasMin = newGasMin;
    emit gasMinChanged();
}

int hourModel::pwrMode() const
{
    return m_pwrMode;
}

void hourModel::setPwrMode(int newPwrMode)
{
    m_pwrMode++;
    if(m_pwrMode == 6){
        m_pwrMode = 0;
    }
    this->setMinMax();
    emit this->pwrModeChanged();
    emit this->pwrModeTextChanged();

}

QString hourModel::pwrModeText() const
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

void hourModel::setPwrModeText(const QString &newPwrModeText)
{
    if (m_pwrModeText == newPwrModeText)
        return;
    m_pwrModeText = newPwrModeText;
    emit pwrModeTextChanged();
}

void hourModel::setCount(int newCount)
{
    if (m_count == newCount)
        return;
    m_count = newCount;
    emit countChanged();
}
